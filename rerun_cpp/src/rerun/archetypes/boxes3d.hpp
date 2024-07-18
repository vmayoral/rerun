// DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/store/re_types/definitions/rerun/archetypes/boxes3d.fbs".

#pragma once

#include "../collection.hpp"
#include "../compiler_utils.hpp"
#include "../components/class_id.hpp"
#include "../components/color.hpp"
#include "../components/half_size3d.hpp"
#include "../components/position3d.hpp"
#include "../components/radius.hpp"
#include "../components/rotation3d.hpp"
#include "../components/text.hpp"
#include "../data_cell.hpp"
#include "../indicator_component.hpp"
#include "../result.hpp"

#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

namespace rerun::archetypes {
    /// **Archetype**: 3D boxes with half-extents and optional center, rotations, colors etc.
    ///
    /// ## Example
    ///
    /// ### Batch of 3D boxes
    /// ![image](https://static.rerun.io/box3d_batch/6d3e453c3a0201ae42bbae9de941198513535f1d/full.png)
    ///
    /// ```cpp
    /// #include <rerun.hpp>
    ///
    /// int main() {
    ///     const auto rec = rerun::RecordingStream("rerun_example_box3d_batch");
    ///     rec.spawn().exit_on_failure();
    ///
    ///     rec.log(
    ///         "batch",
    ///         rerun::Boxes3D::from_centers_and_half_sizes(
    ///             {{2.0f, 0.0f, 0.0f}, {-2.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 2.0f}},
    ///             {{2.0f, 2.0f, 1.0f}, {1.0f, 1.0f, 0.5f}, {2.0f, 0.5f, 1.0f}}
    ///         )
    ///             .with_rotations({
    ///                 rerun::Quaternion::IDENTITY,
    ///                 // 45 degrees around Z
    ///                 rerun::Quaternion::from_xyzw(0.0f, 0.0f, 0.382683f, 0.923880f),
    ///                 rerun::RotationAxisAngle({0.0f, 1.0f, 0.0f}, rerun::Angle::degrees(30.0f)),
    ///             })
    ///             .with_radii({0.025f})
    ///             .with_colors({
    ///                 rerun::Rgba32(255, 0, 0),
    ///                 rerun::Rgba32(0, 255, 0),
    ///                 rerun::Rgba32(0, 0, 255),
    ///             })
    ///             .with_labels({"red", "green", "blue"})
    ///     );
    /// }
    /// ```
    struct Boxes3D {
        /// All half-extents that make up the batch of boxes.
        Collection<rerun::components::HalfSize3D> half_sizes;

        /// Optional center positions of the boxes.
        std::optional<Collection<rerun::components::Position3D>> centers;

        /// Optional rotations of the boxes.
        std::optional<Collection<rerun::components::Rotation3D>> rotations;

        /// Optional colors for the boxes.
        std::optional<Collection<rerun::components::Color>> colors;

        /// Optional radii for the lines that make up the boxes.
        std::optional<Collection<rerun::components::Radius>> radii;

        /// Optional text labels for the boxes.
        ///
        /// If there's a single label present, it will be placed at the center of the entity.
        /// Otherwise, each instance will have its own label.
        std::optional<Collection<rerun::components::Text>> labels;

        /// Optional `components::ClassId`s for the boxes.
        ///
        /// The `components::ClassId` provides colors and labels if not specified explicitly.
        std::optional<Collection<rerun::components::ClassId>> class_ids;

      public:
        static constexpr const char IndicatorComponentName[] = "rerun.components.Boxes3DIndicator";

        /// Indicator component, used to identify the archetype when converting to a list of components.
        using IndicatorComponent = rerun::components::IndicatorComponent<IndicatorComponentName>;

      public: // START of extensions from boxes3d_ext.cpp:
        /// Creates new `Boxes3D` with `half_sizes` centered around the local origin.
        static Boxes3D from_half_sizes(Collection<components::HalfSize3D> half_sizes) {
            Boxes3D boxes;
            boxes.half_sizes = std::move(half_sizes);
            return boxes;
        }

        /// Creates new `Boxes3D` with `centers` and `half_sizes`.
        static Boxes3D from_centers_and_half_sizes(
            Collection<components::Position3D> centers,
            Collection<components::HalfSize3D> half_sizes
        ) {
            Boxes3D boxes;
            boxes.half_sizes = std::move(half_sizes);
            boxes.centers = std::move(centers);
            return boxes;
        }

        /// Creates new `Boxes3D` with `half_sizes` created from (full) sizes.
        ///
        /// TODO(#3285): Does *not* preserve data as-is and instead creates half-sizes from the
        /// input data.
        /// TODO(andreas): This should not take an std::vector.
        static Boxes3D from_sizes(const std::vector<datatypes::Vec3D>& sizes);

        /// Creates new `Boxes3D` with `centers` and `half_sizes` created from centers and (full)
        /// sizes.
        ///
        /// TODO(#3285): Does *not* preserve data as-is and instead creates centers and half-sizes
        /// from the input data.
        /// TODO(andreas): This should not take an std::vector.
        static Boxes3D from_centers_and_sizes(
            Collection<components::Position3D> centers, const std::vector<datatypes::Vec3D>& sizes
        ) {
            Boxes3D boxes = from_sizes(std::move(sizes));
            boxes.centers = std::move(centers);
            return boxes;
        }

        /// Creates new `Boxes3D` with `half_sizes` and `centers` created from minimums and (full)
        /// sizes.
        ///
        /// TODO(#3285): Does *not* preserve data as-is and instead creates centers and half-sizes
        /// from the input data.
        /// TODO(andreas): This should not take an std::vector.
        static Boxes3D from_mins_and_sizes(
            const std::vector<datatypes::Vec3D>& mins, const std::vector<datatypes::Vec3D>& sizes
        );

        // END of extensions from boxes3d_ext.cpp, start of generated code:

      public:
        Boxes3D() = default;
        Boxes3D(Boxes3D&& other) = default;

        /// Optional center positions of the boxes.
        Boxes3D with_centers(Collection<rerun::components::Position3D> _centers) && {
            centers = std::move(_centers);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }

        /// Optional rotations of the boxes.
        Boxes3D with_rotations(Collection<rerun::components::Rotation3D> _rotations) && {
            rotations = std::move(_rotations);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }

        /// Optional colors for the boxes.
        Boxes3D with_colors(Collection<rerun::components::Color> _colors) && {
            colors = std::move(_colors);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }

        /// Optional radii for the lines that make up the boxes.
        Boxes3D with_radii(Collection<rerun::components::Radius> _radii) && {
            radii = std::move(_radii);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }

        /// Optional text labels for the boxes.
        ///
        /// If there's a single label present, it will be placed at the center of the entity.
        /// Otherwise, each instance will have its own label.
        Boxes3D with_labels(Collection<rerun::components::Text> _labels) && {
            labels = std::move(_labels);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }

        /// Optional `components::ClassId`s for the boxes.
        ///
        /// The `components::ClassId` provides colors and labels if not specified explicitly.
        Boxes3D with_class_ids(Collection<rerun::components::ClassId> _class_ids) && {
            class_ids = std::move(_class_ids);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }
    };

} // namespace rerun::archetypes

namespace rerun {
    /// \private
    template <typename T>
    struct AsComponents;

    /// \private
    template <>
    struct AsComponents<archetypes::Boxes3D> {
        /// Serialize all set component batches.
        static Result<std::vector<DataCell>> serialize(const archetypes::Boxes3D& archetype);
    };
} // namespace rerun
