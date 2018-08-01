#pragma once

namespace GameAttributes {
	const int   WINDOW_WIDTH = 900;
	const int   WINDOW_HEIGHT = 700;
	const int   GAME_GRID_ROW_COUNT = 20;
	const int   GAME_GRID_COLUMN_COUNT = 10;
	const float BOX_HEIGHT = 30;
	const float BOX_WIDTH = 30;
	const float LINE_WIDTH = 1;
	const float GAME_GRID_TOTAL_WIDTH = GAME_GRID_COLUMN_COUNT * (BOX_WIDTH + LINE_WIDTH);
	const float GAME_GRID_TOTAL_HEIGHT = GAME_GRID_ROW_COUNT * (BOX_HEIGHT + LINE_WIDTH);
	const float GAME_GRID_ANCHOR_X = (WINDOW_WIDTH - GAME_GRID_TOTAL_WIDTH) / 2;
	const float GAME_GRID_ANCHOR_Y = 40;
}
