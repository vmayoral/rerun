// DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/store/re_types/definitions/rerun/components/resolution2d.fbs".

#pragma once

#include "../datatypes/uvec2d.hpp"
#include "../rerun_sdk_export.hpp"
#include "../result.hpp"

#include <array>
#include <cstdint>
#include <memory>

namespace rerun::components {
    /// **Component**: The width and height of a 2D image.
    struct Resolution2D {
        rerun::datatypes::UVec2D wh;

      public: // START of extensions from resolution2d_ext.cpp:
        /// Construct resolution from width and height.
        Resolution2D(uint32_t width, uint32_t height) : wh{width, height} {}

        uint32_t width() const {
            return wh.x();
        }

        uint32_t height() const {
            return wh.y();
        }

        // END of extensions from resolution2d_ext.cpp, start of generated code:

      public:
        Resolution2D() = default;

        Resolution2D(rerun::datatypes::UVec2D wh_) : wh(wh_) {}

        Resolution2D& operator=(rerun::datatypes::UVec2D wh_) {
            wh = wh_;
            return *this;
        }

        Resolution2D(std::array<uint32_t, 2> xy_) : wh(xy_) {}

        Resolution2D& operator=(std::array<uint32_t, 2> xy_) {
            wh = xy_;
            return *this;
        }

        /// Cast to the underlying UVec2D datatype
        operator rerun::datatypes::UVec2D() const {
            return wh;
        }
    };
} // namespace rerun::components

namespace rerun {
    static_assert(sizeof(rerun::datatypes::UVec2D) == sizeof(components::Resolution2D));

    /// \private
    template <>
    struct Loggable<components::Resolution2D> {
        static constexpr const char Name[] = "rerun.components.Resolution2D";

        /// Returns the arrow data type this type corresponds to.
        static const std::shared_ptr<arrow::DataType>& arrow_datatype() {
            return Loggable<rerun::datatypes::UVec2D>::arrow_datatype();
        }

        /// Serializes an array of `rerun::components::Resolution2D` into an arrow array.
        static Result<std::shared_ptr<arrow::Array>> to_arrow(
            const components::Resolution2D* instances, size_t num_instances
        ) {
            return Loggable<rerun::datatypes::UVec2D>::to_arrow(&instances->wh, num_instances);
        }
    };
} // namespace rerun
