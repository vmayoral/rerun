// DO NOT EDIT! This file was auto-generated by crates/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/re_types/definitions/rerun/blueprint/components/included_query.fbs".

#pragma once

#include "../../datatypes/uuid.hpp"
#include "../../result.hpp"

#include <array>
#include <cstdint>
#include <memory>

namespace arrow {
    class Array;
    class DataType;
    class FixedSizeListBuilder;
} // namespace arrow

namespace rerun::blueprint::components {
    /// **Component**: Each query id refers to a `QueryExpression` component.
    ///
    /// Unstable. Used for the ongoing blueprint experimentations.
    struct IncludedQuery {
        rerun::datatypes::Uuid query_id;

      public:
        IncludedQuery() = default;

        IncludedQuery(rerun::datatypes::Uuid query_id_) : query_id(query_id_) {}

        IncludedQuery& operator=(rerun::datatypes::Uuid query_id_) {
            query_id = query_id_;
            return *this;
        }

        IncludedQuery(std::array<uint8_t, 16> bytes_) : query_id(bytes_) {}

        IncludedQuery& operator=(std::array<uint8_t, 16> bytes_) {
            query_id = bytes_;
            return *this;
        }

        /// Cast to the underlying Uuid datatype
        operator rerun::datatypes::Uuid() const {
            return query_id;
        }
    };
} // namespace rerun::blueprint::components

namespace rerun {
    template <typename T>
    struct Loggable;

    /// \private
    template <>
    struct Loggable<blueprint::components::IncludedQuery> {
        static constexpr const char Name[] = "rerun.blueprint.components.IncludedQuery";

        /// Returns the arrow data type this type corresponds to.
        static const std::shared_ptr<arrow::DataType>& arrow_datatype();

        /// Fills an arrow array builder with an array of this type.
        static rerun::Error fill_arrow_array_builder(
            arrow::FixedSizeListBuilder* builder,
            const blueprint::components::IncludedQuery* elements, size_t num_elements
        );

        /// Serializes an array of `rerun::blueprint:: components::IncludedQuery` into an arrow array.
        static Result<std::shared_ptr<arrow::Array>> to_arrow(
            const blueprint::components::IncludedQuery* instances, size_t num_instances
        );
    };
} // namespace rerun