use itertools::Itertools;
use re_query_cache::{MaybeCachedComponentData, QueryError};
use re_types::{
    archetypes::TimeSeriesScalar,
    components::{Color, Radius, Scalar, ScalarScattering, Text},
    Archetype, Loggable,
};
use re_viewer_context::{
    AnnotationMap, DefaultColor, IdentifiedViewSystem, SpaceViewSystemExecutionError, ViewQuery,
    ViewerContext, VisualizerQueryInfo, VisualizerSystem,
};

use crate::{
    overrides::{initial_override_color, lookup_override},
    util::{determine_plot_bounds_and_time_per_pixel, determine_time_range, points_to_series},
    PlotPoint, PlotPointAttrs, PlotSeries, PlotSeriesKind, ScatterAttrs,
};

/// The legacy system for rendering [`TimeSeriesScalar`] archetypes.
#[derive(Default, Debug)]
pub struct LegacyTimeSeriesSystem {
    pub annotation_map: AnnotationMap,
    pub all_series: Vec<PlotSeries>,
}

impl IdentifiedViewSystem for LegacyTimeSeriesSystem {
    fn identifier() -> re_viewer_context::ViewSystemIdentifier {
        "LegacyTimeSeries".into()
    }
}

impl VisualizerSystem for LegacyTimeSeriesSystem {
    fn visualizer_query_info(&self) -> VisualizerQueryInfo {
        let mut query_info = VisualizerQueryInfo::from_archetype::<TimeSeriesScalar>();
        // Although we don't normally include indicator components in required components,
        // we don't want to show this legacy visualizer unless a user is actively using
        // the legacy archetype for their logging. Users just working with Scalar will
        // only see the new visualizer options.
        query_info
            .required
            .insert(TimeSeriesScalar::indicator().name());
        query_info
    }

    fn execute(
        &mut self,
        ctx: &ViewerContext<'_>,
        query: &ViewQuery<'_>,
        _context: &re_viewer_context::ViewContextCollection,
    ) -> Result<Vec<re_renderer::QueueableDrawData>, SpaceViewSystemExecutionError> {
        re_tracing::profile_function!();

        self.annotation_map.load(
            ctx,
            &query.latest_at_query(),
            query
                .iter_visible_data_results(Self::identifier())
                .map(|data| &data.entity_path),
        );

        match self.load_scalars(ctx, query) {
            Ok(_) | Err(QueryError::PrimaryNotFound(_)) => Ok(Vec::new()),
            Err(err) => Err(err.into()),
        }
    }

    fn as_any(&self) -> &dyn std::any::Any {
        self
    }

    fn initial_override_value(
        &self,
        _ctx: &ViewerContext<'_>,
        _query: &re_data_store::LatestAtQuery,
        _store: &re_data_store::DataStore,
        entity_path: &re_log_types::EntityPath,
        component: &re_types::ComponentName,
    ) -> Option<re_log_types::DataCell> {
        if *component == Color::name() {
            Some([initial_override_color(entity_path)].into())
        } else {
            None
        }
    }
}

impl LegacyTimeSeriesSystem {
    fn load_scalars(
        &mut self,
        ctx: &ViewerContext<'_>,
        query: &ViewQuery<'_>,
    ) -> Result<(), QueryError> {
        re_tracing::profile_function!();

        let query_caches = ctx.entity_db.query_caches();
        let store = ctx.entity_db.store();

        let (plot_bounds, time_per_pixel) = determine_plot_bounds_and_time_per_pixel(ctx, query);

        // TODO(cmc): this should be thread-pooled in case there are a gazillon series in the same plot…
        for data_result in query.iter_visible_data_results(Self::identifier()) {
            let annotations = self.annotation_map.find(&data_result.entity_path);
            let annotation_info = annotations
                .resolved_class_description(None)
                .annotation_info();
            let default_color = DefaultColor::EntityPath(&data_result.entity_path);

            const DEFAULT_RADIUS: f32 = 0.75;

            let override_color = lookup_override::<Color>(data_result, ctx).map(|c| c.to_array());
            let override_label = lookup_override::<Text>(data_result, ctx).map(|t| t.0);
            let override_scattered =
                lookup_override::<ScalarScattering>(data_result, ctx).map(|s| s.0);
            let override_radius = lookup_override::<Radius>(data_result, ctx).map(|r| r.0);

            // All the default values for a `PlotPoint`, accounting for both overrides and default
            // values.
            let default_point = PlotPoint {
                time: 0,
                value: 0.0,
                attrs: PlotPointAttrs {
                    label: override_label.clone(), // default value is simply None
                    color: annotation_info.color(override_color, default_color),
                    stroke_width: override_radius.unwrap_or(DEFAULT_RADIUS),
                    kind: if override_scattered.unwrap_or(false) {
                        PlotSeriesKind::Scatter(ScatterAttrs::default())
                    } else {
                        PlotSeriesKind::Continuous
                    },
                },
            };

            let mut points = Vec::new();

            let time_range = determine_time_range(
                query,
                data_result,
                plot_bounds,
                ctx.app_options.experimental_plot_query_clamping,
            );

            {
                re_tracing::profile_scope!("primary", &data_result.entity_path.to_string());

                let query = re_data_store::RangeQuery::new(query.timeline, time_range);

                query_caches.query_archetype_xxx_pov1_comp4::<
                    TimeSeriesScalar,
                    Scalar,
                    ScalarScattering,
                    Color,
                    Radius,
                    Text,
                    _,
                >(
                    ctx.app_options.experimental_primary_caching_range,
                    store,
                    &query.clone().into(),
                    &data_result.entity_path,
                    |entry_range, (times, _, scalars, scatterings, colors, radii, labels)| {
                        // for (time, scalar, scattered, color, radius, label) in itertools::izip!(
                        //     times, scalars.iter(), scatterings, colors, radii, labels
                        // ) {
                        //     //
                        // }

                        // TODO: how do we handle a disabled cache???

                        let times = times.range(entry_range.clone()).map(|(time, _)| time.as_i64());
                        let scalars = scalars.range(entry_range.clone());
                        let scatterings = scatterings.map_or_else(
                            || itertools::Either::Left(std::iter::repeat(&[] as &[Option<ScalarScattering>])),
                            |scatterings| itertools::Either::Right(scatterings.range(entry_range.clone())),
                        );
                        let colors = colors.map_or_else(
                            || itertools::Either::Left(std::iter::repeat(&[] as &[Option<Color>])),
                            |colors| itertools::Either::Right(colors.range(entry_range.clone())),
                        );
                        let radii = radii.map_or_else(
                            || itertools::Either::Left(std::iter::repeat(&[] as &[Option<Radius>])),
                            |radii| itertools::Either::Right(radii.range(entry_range.clone())),
                        );
                        let labels = labels.map_or_else(
                            || itertools::Either::Left(std::iter::repeat(&[] as &[Option<Text>])),
                            |labels| itertools::Either::Right(labels.range(entry_range.clone())),
                        );

                        points = itertools::izip!(times, scalars, scatterings, colors, radii, labels)
                            .map(|(time, scalar, scattered, color, radius, label)| {
                                // TODO: warn if len>1 -> is is costly?
                                scalar.first().map_or_else(|| {
                                    PlotPoint {
                                        time,
                                        value: 0.0,
                                        attrs: PlotPointAttrs {
                                            label: None,
                                            color: egui::Color32::BLACK,
                                            stroke_width: 0.0,
                                            kind: PlotSeriesKind::Clear,
                                        },
                                    }
                                }, |s| {
                                    let mut point = PlotPoint {
                                        time,
                                        value: s.0,
                                        ..default_point.clone()
                                    };

                                    if override_color.is_none() {
                                        if let Some(color) = color.first().copied().flatten().map(|c| {
                                            let [r,g,b,a] = c.to_array();
                                            if a == 255 {
                                                // Common-case optimization
                                                re_renderer::Color32::from_rgb(r, g, b)
                                            } else {
                                                re_renderer::Color32::from_rgba_unmultiplied(r, g, b, a)
                                            }
                                        }) {
                                            point.attrs.color = color;
                                        }
                                    }

                                    if override_label.is_none() {
                                        if let Some(label) = label.first().cloned().flatten().map(|l| l.0) {
                                            point.attrs.label = Some(label);
                                        }
                                    }

                                    #[allow(clippy::collapsible_if)] // readability
                                    if override_scattered.is_none() {
                                        if scattered.first().copied().flatten().map_or(false, |s| s.0) {
                                            point.attrs.kind  = PlotSeriesKind::Scatter(ScatterAttrs::default());
                                        };
                                    }

                                    if override_radius.is_none() {
                                        if let Some(radius) = radius.first().copied().flatten().map(|r| r.0) {
                                            point.attrs.stroke_width = radius;
                                        }
                                    }

                                    point
                                })
                        }).collect_vec();
                    },
                )?;
            }

            // Now convert the `PlotPoints` into `Vec<PlotSeries>`
            points_to_series(
                data_result,
                time_per_pixel,
                points,
                store,
                query,
                &mut self.all_series,
            );
        }

        Ok(())
    }
}