#pragma once

enum class EventType {
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	REMOVE_ROWS,
	COMPACT_GRID,
	DROP_PIECE,
	EXIT,
};