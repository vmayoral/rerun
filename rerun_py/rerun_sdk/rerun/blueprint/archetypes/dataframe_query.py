# DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/python/mod.rs
# Based on "crates/store/re_types/definitions/rerun/blueprint/archetypes/dataframe_query.fbs".

# You can extend this class by creating a "DataframeQueryExt" class in "dataframe_query_ext.py".

from __future__ import annotations

from typing import Any

from attrs import define, field

from ... import datatypes
from ..._baseclasses import (
    Archetype,
)
from ...blueprint import components as blueprint_components
from ...error_utils import catch_and_log_exceptions

__all__ = ["DataframeQuery"]


@define(str=False, repr=False, init=False)
class DataframeQuery(Archetype):
    """**Archetype**: Configuration for the dataframe view."""

    def __init__(
        self: Any,
        *,
        timeline: datatypes.Utf8Like | None = None,
        mode: blueprint_components.DataframeViewModeLike | None = None,
        latest_at_queries: blueprint_components.LatestAtQueriesLike | None = None,
        time_range_queries: blueprint_components.TimeRangeQueriesLike | None = None,
    ):
        """
        Create a new instance of the DataframeQuery archetype.

        Parameters
        ----------
        timeline:
            Name of the timeline this applies to.
        mode:
            Type of query: latest at or range
        latest_at_queries:
            Times (1 for latest at, 2 for range)
        time_range_queries:
            Times (1 for latest at, 2 for range)

        """

        # You can define your own __init__ function as a member of DataframeQueryExt in dataframe_query_ext.py
        with catch_and_log_exceptions(context=self.__class__.__name__):
            self.__attrs_init__(
                timeline=timeline, mode=mode, latest_at_queries=latest_at_queries, time_range_queries=time_range_queries
            )
            return
        self.__attrs_clear__()

    def __attrs_clear__(self) -> None:
        """Convenience method for calling `__attrs_init__` with all `None`s."""
        self.__attrs_init__(
            timeline=None,  # type: ignore[arg-type]
            mode=None,  # type: ignore[arg-type]
            latest_at_queries=None,  # type: ignore[arg-type]
            time_range_queries=None,  # type: ignore[arg-type]
        )

    @classmethod
    def _clear(cls) -> DataframeQuery:
        """Produce an empty DataframeQuery, bypassing `__init__`."""
        inst = cls.__new__(cls)
        inst.__attrs_clear__()
        return inst

    timeline: blueprint_components.TimelineBatch | None = field(
        metadata={"component": "optional"},
        default=None,
        converter=blueprint_components.TimelineBatch._optional,  # type: ignore[misc]
    )
    # Name of the timeline this applies to.
    #
    # (Docstring intentionally commented out to hide this field from the docs)

    mode: blueprint_components.DataframeViewModeBatch | None = field(
        metadata={"component": "optional"},
        default=None,
        converter=blueprint_components.DataframeViewModeBatch._optional,  # type: ignore[misc]
    )
    # Type of query: latest at or range
    #
    # (Docstring intentionally commented out to hide this field from the docs)

    latest_at_queries: blueprint_components.LatestAtQueriesBatch | None = field(
        metadata={"component": "optional"},
        default=None,
        converter=blueprint_components.LatestAtQueriesBatch._optional,  # type: ignore[misc]
    )
    # Times (1 for latest at, 2 for range)
    #
    # (Docstring intentionally commented out to hide this field from the docs)

    time_range_queries: blueprint_components.TimeRangeQueriesBatch | None = field(
        metadata={"component": "optional"},
        default=None,
        converter=blueprint_components.TimeRangeQueriesBatch._optional,  # type: ignore[misc]
    )
    # Times (1 for latest at, 2 for range)
    #
    # (Docstring intentionally commented out to hide this field from the docs)

    __str__ = Archetype.__str__
    __repr__ = Archetype.__repr__  # type: ignore[assignment]
