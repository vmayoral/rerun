# DO NOT EDIT! This file was auto-generated by crates/re_types_builder/src/codegen/python/mod.rs
# Based on "crates/re_types/definitions/rerun/datatypes/bool.fbs".

# You can extend this class by creating a "BoolExt" class in "bool_ext.py".

from __future__ import annotations

from typing import TYPE_CHECKING, Any, Sequence, Union

import pyarrow as pa
from attrs import define, field

from .._baseclasses import BaseBatch, BaseExtensionType
from .bool_ext import BoolExt

__all__ = ["Bool", "BoolArrayLike", "BoolBatch", "BoolLike", "BoolType"]


@define(init=False)
class Bool(BoolExt):
    """**Datatype**: A single boolean."""

    def __init__(self: Any, value: BoolLike):
        """Create a new instance of the Bool datatype."""

        # You can define your own __init__ function as a member of BoolExt in bool_ext.py
        self.__attrs_init__(value=value)

    def __bool__(self) -> bool:
        return self.value

    value: bool = field(converter=bool)


if TYPE_CHECKING:
    BoolLike = Union[Bool, bool]
else:
    BoolLike = Any

BoolArrayLike = Union[
    Bool,
    Sequence[BoolLike],
]


class BoolType(BaseExtensionType):
    _TYPE_NAME: str = "rerun.datatypes.Bool"

    def __init__(self) -> None:
        pa.ExtensionType.__init__(self, pa.bool_(), self._TYPE_NAME)


class BoolBatch(BaseBatch[BoolArrayLike]):
    _ARROW_TYPE = BoolType()

    @staticmethod
    def _native_to_pa_array(data: BoolArrayLike, data_type: pa.DataType) -> pa.Array:
        return BoolExt.native_to_pa_array_override(data, data_type)
