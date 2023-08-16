# NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.

from __future__ import annotations

from typing import TYPE_CHECKING, Any, Sequence, Union

import pyarrow as pa
from attrs import define, field

# noqa: F401
from .. import datatypes
from .._baseclasses import (
    BaseExtensionArray,
    BaseExtensionType,
)
from ._overrides import (
    classdescription_info_converter,
    classdescription_init,
    classdescription_keypoint_annotations_converter,
    classdescription_keypoint_connections_converter,
    classdescription_native_to_pa_array,
)

__all__ = [
    "ClassDescription",
    "ClassDescriptionArray",
    "ClassDescriptionArrayLike",
    "ClassDescriptionLike",
    "ClassDescriptionType",
]


@define(init=False)
class ClassDescription:
    """
    The description of a semantic Class.

    If an entity is annotated with a corresponding `ClassId`, rerun will use
    the attached `AnnotationInfo` to derive labels and colors.

    Keypoints within an annotation class can similarly be annotated with a
    `KeypointId` in which case we should defer to the label and color for the
    `AnnotationInfo` specifically associated with the Keypoint.

    Keypoints within the class can also be decorated with skeletal edges.
    Keypoint-connections are pairs of `KeypointId`s. If an edge is
    defined, and both keypoints exist within the instance of the class, then the
    keypoints should be connected with an edge. The edge should be labeled and
    colored as described by the class's `AnnotationInfo`.
    """

    def __init__(self, *args, **kwargs):  # type: ignore[no-untyped-def]
        classdescription_init(self, *args, **kwargs)

    info: datatypes.AnnotationInfo = field(converter=classdescription_info_converter)
    """
    The `AnnotationInfo` for the class.
    """

    keypoint_annotations: list[datatypes.AnnotationInfo] = field(
        converter=classdescription_keypoint_annotations_converter
    )
    """
    The `AnnotationInfo` for all of the keypoints.
    """

    keypoint_connections: list[datatypes.KeypointPair] = field(
        converter=classdescription_keypoint_connections_converter
    )
    """
    The connections between keypoints.
    """


if TYPE_CHECKING:
    ClassDescriptionLike = Union[ClassDescription, datatypes.AnnotationInfoLike]
else:
    ClassDescriptionLike = Any

ClassDescriptionArrayLike = Union[
    ClassDescription,
    Sequence[ClassDescriptionLike],
]


# --- Arrow support ---


class ClassDescriptionType(BaseExtensionType):
    def __init__(self) -> None:
        pa.ExtensionType.__init__(
            self,
            pa.struct(
                [
                    pa.field(
                        "info",
                        pa.struct(
                            [
                                pa.field("id", pa.uint16(), nullable=False, metadata={}),
                                pa.field("label", pa.utf8(), nullable=True, metadata={}),
                                pa.field("color", pa.uint32(), nullable=True, metadata={}),
                            ]
                        ),
                        nullable=False,
                        metadata={},
                    ),
                    pa.field(
                        "keypoint_annotations",
                        pa.list_(
                            pa.field(
                                "item",
                                pa.struct(
                                    [
                                        pa.field("id", pa.uint16(), nullable=False, metadata={}),
                                        pa.field("label", pa.utf8(), nullable=True, metadata={}),
                                        pa.field("color", pa.uint32(), nullable=True, metadata={}),
                                    ]
                                ),
                                nullable=False,
                                metadata={},
                            )
                        ),
                        nullable=False,
                        metadata={},
                    ),
                    pa.field(
                        "keypoint_connections",
                        pa.list_(
                            pa.field(
                                "item",
                                pa.struct(
                                    [
                                        pa.field("keypoint0", pa.uint16(), nullable=False, metadata={}),
                                        pa.field("keypoint1", pa.uint16(), nullable=False, metadata={}),
                                    ]
                                ),
                                nullable=False,
                                metadata={},
                            )
                        ),
                        nullable=False,
                        metadata={},
                    ),
                ]
            ),
            "rerun.datatypes.ClassDescription",
        )


class ClassDescriptionArray(BaseExtensionArray[ClassDescriptionArrayLike]):
    _EXTENSION_NAME = "rerun.datatypes.ClassDescription"
    _EXTENSION_TYPE = ClassDescriptionType

    @staticmethod
    def _native_to_pa_array(data: ClassDescriptionArrayLike, data_type: pa.DataType) -> pa.Array:
        return classdescription_native_to_pa_array(data, data_type)


ClassDescriptionType._ARRAY_TYPE = ClassDescriptionArray

# TODO(cmc): bring back registration to pyarrow once legacy types are gone
# pa.register_extension_type(ClassDescriptionType())
