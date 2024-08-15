// DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/store/re_types/definitions/rerun/datatypes/video.fbs".

#pragma once

#include "../result.hpp"
#include "uint32.hpp"
#include "uint64.hpp"

#include <cstdint>
#include <memory>

namespace arrow {
    class Array;
    class DataType;
    class StructBuilder;
} // namespace arrow

namespace rerun::datatypes {
    /// **Datatype**: A video sample.
    ///
    /// Similar to a frame of video, but decoding a full frame typically requires more than one sample.
    ///
    /// Samples can either be key frames or delta frames. Only key frames have enough data to decode a full frame,
    /// delta frames always require the context of a key frame and possibly also some number of preceding delta
    /// frames to decode a full frame.
    ///
    /// The type of a given sample is implicit in its position in the `datatypes::VideoSegment` it belongs to,
    /// where the first sample is always a key frame.
    struct VideoSample {
        /// Time at which this sample appears, in time units.
        rerun::datatypes::UInt64 timestamp;

        /// Offset into video data.
        rerun::datatypes::UInt32 byte_offset;

        /// Length of the sample starting at the sample's byte offset.
        rerun::datatypes::UInt32 byte_length;

      public:
        VideoSample() = default;
    };
} // namespace rerun::datatypes

namespace rerun {
    template <typename T>
    struct Loggable;

    /// \private
    template <>
    struct Loggable<datatypes::VideoSample> {
        static constexpr const char Name[] = "rerun.datatypes.VideoSample";

        /// Returns the arrow data type this type corresponds to.
        static const std::shared_ptr<arrow::DataType>& arrow_datatype();

        /// Serializes an array of `rerun::datatypes::VideoSample` into an arrow array.
        static Result<std::shared_ptr<arrow::Array>> to_arrow(
            const datatypes::VideoSample* instances, size_t num_instances
        );

        /// Fills an arrow array builder with an array of this type.
        static rerun::Error fill_arrow_array_builder(
            arrow::StructBuilder* builder, const datatypes::VideoSample* elements,
            size_t num_elements
        );
    };
} // namespace rerun
