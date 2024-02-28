#pragma once

namespace Mountain::Layout
{
	enum class AlignItems
	{
		Auto,
		FlexStart,
		Center,
		FlexEnd,
		Stretch,
		Baseline,
		SpaceBetween,
		SpaceAround,
		SpaceEvenly
	};

	enum class FlexDirection
	{
		Column,
		ColumnReverse,
		Row,
		RowReverse
	};

	enum class JustifyContent
	{
		FlexStart,
		Center,
		FlexEnd,
		SpaceBetween,
		SpaceAround,
		SpaceEvenly
	};

	enum class PositionType
	{
		Static,
		Relative,
		Absolute
	};

	enum class DisplayType
	{
		Flex,
		None
	};
}