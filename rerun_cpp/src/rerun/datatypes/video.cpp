// DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/store/re_types/definitions/rerun/datatypes/video.fbs".

#include "video.hpp"

#include "uint64.hpp"
#include "video_config.hpp"
#include "video_segment.hpp"

#include <arrow/builder.h>
#include <arrow/type_fwd.h>

namespace rerun::datatypes {}

namespace rerun {
    const std::shared_ptr<arrow::DataType>& Loggable<datatypes::Video>::arrow_datatype() {
        static const auto datatype = arrow::struct_({
            arrow::field(
                "config",
                Loggable<rerun::datatypes::VideoConfig>::arrow_datatype(),
                false
            ),
            arrow::field("timescale", Loggable<rerun::datatypes::UInt64>::arrow_datatype(), false),
            arrow::field("duration", Loggable<rerun::datatypes::UInt64>::arrow_datatype(), false),
            arrow::field(
                "segments",
                arrow::list(arrow::field(
                    "item",
                    Loggable<rerun::datatypes::VideoSegment>::arrow_datatype(),
                    false
                )),
                false
            ),
            arrow::field("data", arrow::list(arrow::field("item", arrow::uint8(), false)), false),
        });
        return datatype;
    }

    Result<std::shared_ptr<arrow::Array>> Loggable<datatypes::Video>::to_arrow(
        const datatypes::Video* instances, size_t num_instances
    ) {
        // TODO(andreas): Allow configuring the memory pool.
        arrow::MemoryPool* pool = arrow::default_memory_pool();
        auto datatype = arrow_datatype();

        ARROW_ASSIGN_OR_RAISE(auto builder, arrow::MakeBuilder(datatype, pool))
        if (instances && num_instances > 0) {
            RR_RETURN_NOT_OK(Loggable<datatypes::Video>::fill_arrow_array_builder(
                static_cast<arrow::StructBuilder*>(builder.get()),
                instances,
                num_instances
            ));
        }
        std::shared_ptr<arrow::Array> array;
        ARROW_RETURN_NOT_OK(builder->Finish(&array));
        return array;
    }

    rerun::Error Loggable<datatypes::Video>::fill_arrow_array_builder(
        arrow::StructBuilder* builder, const datatypes::Video* elements, size_t num_elements
    ) {
        if (builder == nullptr) {
            return rerun::Error(ErrorCode::UnexpectedNullArgument, "Passed array builder is null.");
        }
        if (elements == nullptr) {
            return rerun::Error(
                ErrorCode::UnexpectedNullArgument,
                "Cannot serialize null pointer to arrow array."
            );
        }

        {
            auto field_builder = static_cast<arrow::StructBuilder*>(builder->field_builder(0));
            ARROW_RETURN_NOT_OK(field_builder->Reserve(static_cast<int64_t>(num_elements)));
            for (size_t elem_idx = 0; elem_idx < num_elements; elem_idx += 1) {
                RR_RETURN_NOT_OK(Loggable<rerun::datatypes::VideoConfig>::fill_arrow_array_builder(
                    field_builder,
                    &elements[elem_idx].config,
                    1
                ));
            }
        }
        {
            auto field_builder = static_cast<arrow::UInt64Builder*>(builder->field_builder(1));
            ARROW_RETURN_NOT_OK(field_builder->Reserve(static_cast<int64_t>(num_elements)));
            for (size_t elem_idx = 0; elem_idx < num_elements; elem_idx += 1) {
                RR_RETURN_NOT_OK(Loggable<rerun::datatypes::UInt64>::fill_arrow_array_builder(
                    field_builder,
                    &elements[elem_idx].timescale,
                    1
                ));
            }
        }
        {
            auto field_builder = static_cast<arrow::UInt64Builder*>(builder->field_builder(2));
            ARROW_RETURN_NOT_OK(field_builder->Reserve(static_cast<int64_t>(num_elements)));
            for (size_t elem_idx = 0; elem_idx < num_elements; elem_idx += 1) {
                RR_RETURN_NOT_OK(Loggable<rerun::datatypes::UInt64>::fill_arrow_array_builder(
                    field_builder,
                    &elements[elem_idx].duration,
                    1
                ));
            }
        }
        {
            auto field_builder = static_cast<arrow::ListBuilder*>(builder->field_builder(3));
            auto value_builder = static_cast<arrow::StructBuilder*>(field_builder->value_builder());
            ARROW_RETURN_NOT_OK(field_builder->Reserve(static_cast<int64_t>(num_elements)));
            ARROW_RETURN_NOT_OK(value_builder->Reserve(static_cast<int64_t>(num_elements * 2)));

            for (size_t elem_idx = 0; elem_idx < num_elements; elem_idx += 1) {
                const auto& element = elements[elem_idx];
                ARROW_RETURN_NOT_OK(field_builder->Append());
                if (element.segments.data()) {
                    RR_RETURN_NOT_OK(
                        Loggable<rerun::datatypes::VideoSegment>::fill_arrow_array_builder(
                            value_builder,
                            element.segments.data(),
                            element.segments.size()
                        )
                    );
                }
            }
        }
        {
            auto field_builder = static_cast<arrow::ListBuilder*>(builder->field_builder(4));
            auto value_builder = static_cast<arrow::UInt8Builder*>(field_builder->value_builder());
            ARROW_RETURN_NOT_OK(field_builder->Reserve(static_cast<int64_t>(num_elements)));
            ARROW_RETURN_NOT_OK(value_builder->Reserve(static_cast<int64_t>(num_elements * 2)));

            for (size_t elem_idx = 0; elem_idx < num_elements; elem_idx += 1) {
                const auto& element = elements[elem_idx];
                ARROW_RETURN_NOT_OK(field_builder->Append());
                ARROW_RETURN_NOT_OK(value_builder->AppendValues(
                    element.data.data(),
                    static_cast<int64_t>(element.data.size()),
                    nullptr
                ));
            }
        }
        ARROW_RETURN_NOT_OK(builder->AppendValues(static_cast<int64_t>(num_elements), nullptr));

        return Error::ok();
    }
} // namespace rerun
