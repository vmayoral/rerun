# DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/python/mod.rs
# Based on "crates/store/re_types/definitions/rerun/datatypes/video.fbs".

# You can extend this class by creating a "VideoConfigExt" class in "video_config_ext.py".

from __future__ import annotations

from typing import Any, Sequence, Union

import numpy as np
import numpy.typing as npt
import pyarrow as pa
from attrs import define, field

from .. import datatypes
from .._baseclasses import (
    BaseBatch,
    BaseExtensionType,
)
from .._converters import (
    to_np_uint8,
)

__all__ = ["VideoConfig", "VideoConfigArrayLike", "VideoConfigBatch", "VideoConfigLike", "VideoConfigType"]


def _video_config__codec__special_field_converter_override(x: datatypes.Utf8Like) -> datatypes.Utf8:
    if isinstance(x, datatypes.Utf8):
        return x
    else:
        return datatypes.Utf8(x)


def _video_config__coded_height__special_field_converter_override(x: datatypes.UInt16Like) -> datatypes.UInt16:
    if isinstance(x, datatypes.UInt16):
        return x
    else:
        return datatypes.UInt16(x)


def _video_config__coded_width__special_field_converter_override(x: datatypes.UInt16Like) -> datatypes.UInt16:
    if isinstance(x, datatypes.UInt16):
        return x
    else:
        return datatypes.UInt16(x)


@define(init=False)
class VideoConfig:
    """**Datatype**: Video configuration."""

    def __init__(
        self: Any,
        codec: datatypes.Utf8Like,
        coded_height: datatypes.UInt16Like,
        coded_width: datatypes.UInt16Like,
        description: npt.ArrayLike,
    ):
        """
        Create a new instance of the VideoConfig datatype.

        Parameters
        ----------
        codec:
            String used to identify the codec and some of its configuration.
        coded_height:
            Natural height of the video.
        coded_width:
            Natural width of the video.
        description:
            Codec-specific configuration.

        """

        # You can define your own __init__ function as a member of VideoConfigExt in video_config_ext.py
        self.__attrs_init__(codec=codec, coded_height=coded_height, coded_width=coded_width, description=description)

    codec: datatypes.Utf8 = field(converter=_video_config__codec__special_field_converter_override)
    # String used to identify the codec and some of its configuration.
    #
    # (Docstring intentionally commented out to hide this field from the docs)

    coded_height: datatypes.UInt16 = field(converter=_video_config__coded_height__special_field_converter_override)
    # Natural height of the video.
    #
    # (Docstring intentionally commented out to hide this field from the docs)

    coded_width: datatypes.UInt16 = field(converter=_video_config__coded_width__special_field_converter_override)
    # Natural width of the video.
    #
    # (Docstring intentionally commented out to hide this field from the docs)

    description: npt.NDArray[np.uint8] = field(converter=to_np_uint8)
    # Codec-specific configuration.
    #
    # (Docstring intentionally commented out to hide this field from the docs)


VideoConfigLike = VideoConfig
VideoConfigArrayLike = Union[
    VideoConfig,
    Sequence[VideoConfigLike],
]


class VideoConfigType(BaseExtensionType):
    _TYPE_NAME: str = "rerun.datatypes.VideoConfig"

    def __init__(self) -> None:
        pa.ExtensionType.__init__(
            self,
            pa.struct([
                pa.field("codec", pa.utf8(), nullable=False, metadata={}),
                pa.field("coded_height", pa.uint16(), nullable=False, metadata={}),
                pa.field("coded_width", pa.uint16(), nullable=False, metadata={}),
                pa.field(
                    "description",
                    pa.list_(pa.field("item", pa.uint8(), nullable=False, metadata={})),
                    nullable=False,
                    metadata={},
                ),
            ]),
            self._TYPE_NAME,
        )


class VideoConfigBatch(BaseBatch[VideoConfigArrayLike]):
    _ARROW_TYPE = VideoConfigType()

    @staticmethod
    def _native_to_pa_array(data: VideoConfigArrayLike, data_type: pa.DataType) -> pa.Array:
        raise NotImplementedError(
            "Arrow serialization of VideoConfig not implemented: We lack codegen for arrow-serialization of general structs"
        )  # You need to implement native_to_pa_array_override in video_config_ext.py
