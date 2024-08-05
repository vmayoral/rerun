// DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/store/re_types/definitions/rerun/blueprint/archetypes/dataframe_query.fbs".

#pragma once

#include "../../blueprint/components/dataframe_view_mode.hpp"
#include "../../blueprint/components/latest_at_queries.hpp"
#include "../../blueprint/components/time_range_queries.hpp"
#include "../../blueprint/components/timeline.hpp"
#include "../../collection.hpp"
#include "../../compiler_utils.hpp"
#include "../../data_cell.hpp"
#include "../../indicator_component.hpp"
#include "../../result.hpp"

#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

namespace rerun::blueprint::archetypes {
    /// **Archetype**: Configuration for the dataframe view
    struct DataframeQuery {
        /// Name of the timeline this applies to.
        std::optional<rerun::blueprint::components::Timeline> timeline;

        /// Type of query: latest at or range
        std::optional<rerun::blueprint::components::DataframeViewMode> mode;

        /// Times (1 for latest at, 2 for range)
        std::optional<rerun::blueprint::components::LatestAtQueries> latest_at_queries;

        /// Times (1 for latest at, 2 for range)
        std::optional<rerun::blueprint::components::TimeRangeQueries> time_range_queries;

      public:
        static constexpr const char IndicatorComponentName[] =
            "rerun.blueprint.components.DataframeQueryIndicator";

        /// Indicator component, used to identify the archetype when converting to a list of components.
        using IndicatorComponent = rerun::components::IndicatorComponent<IndicatorComponentName>;

      public:
        DataframeQuery() = default;
        DataframeQuery(DataframeQuery&& other) = default;

        /// Name of the timeline this applies to.
        DataframeQuery with_timeline(rerun::blueprint::components::Timeline _timeline) && {
            timeline = std::move(_timeline);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }

        /// Type of query: latest at or range
        DataframeQuery with_mode(rerun::blueprint::components::DataframeViewMode _mode) && {
            mode = std::move(_mode);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }

        /// Times (1 for latest at, 2 for range)
        DataframeQuery with_latest_at_queries(
            rerun::blueprint::components::LatestAtQueries _latest_at_queries
        ) && {
            latest_at_queries = std::move(_latest_at_queries);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }

        /// Times (1 for latest at, 2 for range)
        DataframeQuery with_time_range_queries(
            rerun::blueprint::components::TimeRangeQueries _time_range_queries
        ) && {
            time_range_queries = std::move(_time_range_queries);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }
    };

} // namespace rerun::blueprint::archetypes

namespace rerun {
    /// \private
    template <typename T>
    struct AsComponents;

    /// \private
    template <>
    struct AsComponents<blueprint::archetypes::DataframeQuery> {
        /// Serialize all set component batches.
        static Result<std::vector<DataCell>> serialize(
            const blueprint::archetypes::DataframeQuery& archetype
        );
    };
} // namespace rerun
