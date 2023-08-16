# NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.

from __future__ import annotations

from typing import TYPE_CHECKING, Any, Sequence, Union

import pyarrow as pa
from attrs import define, field

from .. import datatypes
from .._baseclasses import (
    BaseExtensionArray,
    BaseExtensionType,
)
from ._overrides import keypointpair_native_to_pa_array  # noqa: F401

__all__ = ["KeypointPair", "KeypointPairArray", "KeypointPairArrayLike", "KeypointPairLike", "KeypointPairType"]


def _keypointpair_keypoint0_converter(x: datatypes.KeypointIdLike) -> datatypes.KeypointId:
    if isinstance(x, datatypes.KeypointId):
        return x
    else:
        return datatypes.KeypointId(x)


def _keypointpair_keypoint1_converter(x: datatypes.KeypointIdLike) -> datatypes.KeypointId:
    if isinstance(x, datatypes.KeypointId):
        return x
    else:
        return datatypes.KeypointId(x)


@define
class KeypointPair:
    """A connection between two `Keypoints`."""

    keypoint0: datatypes.KeypointId = field(converter=_keypointpair_keypoint0_converter)
    keypoint1: datatypes.KeypointId = field(converter=_keypointpair_keypoint1_converter)


if TYPE_CHECKING:
    KeypointPairLike = Union[KeypointPair, Sequence[datatypes.KeypointIdLike]]
else:
    KeypointPairLike = Any

KeypointPairArrayLike = Union[
    KeypointPair,
    Sequence[KeypointPairLike],
]


# --- Arrow support ---


class KeypointPairType(BaseExtensionType):
    def __init__(self) -> None:
        pa.ExtensionType.__init__(
            self,
            pa.struct(
                [
                    pa.field("keypoint0", pa.uint16(), nullable=False, metadata={}),
                    pa.field("keypoint1", pa.uint16(), nullable=False, metadata={}),
                ]
            ),
            "rerun.datatypes.KeypointPair",
        )


class KeypointPairArray(BaseExtensionArray[KeypointPairArrayLike]):
    _EXTENSION_NAME = "rerun.datatypes.KeypointPair"
    _EXTENSION_TYPE = KeypointPairType

    @staticmethod
    def _native_to_pa_array(data: KeypointPairArrayLike, data_type: pa.DataType) -> pa.Array:
        return keypointpair_native_to_pa_array(data, data_type)


KeypointPairType._ARRAY_TYPE = KeypointPairArray

# TODO(cmc): bring back registration to pyarrow once legacy types are gone
# pa.register_extension_type(KeypointPairType())
