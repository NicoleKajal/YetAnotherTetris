#pragma once

namespace GameAttributes {
	// Misc. Attributes
	const float WINDOW_ITEM_SPACING  = 60;
	const int   MAIN_LABEL_FONT_SIZE = 46;
	const int   STATS_FONT_SIZE      = 32;

	// Game Grid Attributes
	const int   GAME_GRID_ROW_COUNT    = 20;
	const int   GAME_GRID_COLUMN_COUNT = 10;
	const float GAME_GRID_SQUARE_SIZE  = 30;
	const float GAME_GRID_LINE_SIZE    = 1;

	// Game Piece Attributes
	// A game piece will always occupy four locations, which can have a maximum height of four
	// locations, a maximum width of four locations, and can be oriented in four different positions
	// (each new orientation can be viewed as a result of being rotated by 90 degrees).
	const int GAME_PIECE_LOCATION_COUNT         = 4;
	const int GAME_PIECE_MAX_HIGHT              = 4;
	const int GAME_PIECE_MAX_WIDTH              = 4;
	const int GAME_PIECE_ORIENTATION_COUNT      = 4;
	const int GAME_PIECE_GRID_ENTRY_ROW         = 0;
	const int GAME_PIECE_GRID_ENTRY_COLUMN      = (GAME_GRID_COLUMN_COUNT - GAME_PIECE_MAX_WIDTH) / 2;
	const int GAME_PIECE_GRID_ENTRY_ORIENTATION = 0;
	const int GAME_PIECE_SHAPE_COUNT            = 7;

	// Preview Box Attributes
	const int   PREVIEW_BOX_ITEM_COUNT        = 3;
	const int   PREVIEW_BOX_ITEM_ROW_COUNT    = 2;
	const int   PREVIEW_BOX_ITEM_COLUMN_COUNT = 4;
	const float PREVIEW_BOX_ITEM_BOX_SIZE     = 30;
	const float PREVIEW_BOX_BORDER_WIDTH      = 30;
	const float PREVIEW_BOX_LINE_SIZE         = 1;

	// Width and height of window items and window
	const float GAME_GRID_WIDTH    = GAME_GRID_COLUMN_COUNT * (GAME_GRID_SQUARE_SIZE + GAME_GRID_LINE_SIZE) + GAME_GRID_LINE_SIZE;
	const float GAME_GRID_HEIGHT   = GAME_GRID_ROW_COUNT * (GAME_GRID_SQUARE_SIZE + GAME_GRID_LINE_SIZE) + GAME_GRID_LINE_SIZE;
	const float PREVIEW_BOX_WIDTH  = PREVIEW_BOX_ITEM_COLUMN_COUNT * (PREVIEW_BOX_ITEM_BOX_SIZE + GAME_GRID_LINE_SIZE) + PREVIEW_BOX_LINE_SIZE + (2 * PREVIEW_BOX_BORDER_WIDTH);
	const float PREVIEW_BOX_HEIGHT = (PREVIEW_BOX_ITEM_COUNT * PREVIEW_BOX_ITEM_ROW_COUNT) * (PREVIEW_BOX_ITEM_BOX_SIZE + PREVIEW_BOX_LINE_SIZE) + ((PREVIEW_BOX_ITEM_COUNT + 1) * PREVIEW_BOX_BORDER_WIDTH);
	const float STATS_BOX_WIDTH    = PREVIEW_BOX_WIDTH;
	const float STATS_BOX_HEIGHT   = PREVIEW_BOX_HEIGHT;
	const float WINDOW_WIDTH       = PREVIEW_BOX_WIDTH + GAME_GRID_WIDTH + PREVIEW_BOX_WIDTH + 4 * WINDOW_ITEM_SPACING;
	const float WINDOW_HEIGHT      = GAME_GRID_HEIGHT + 2 * WINDOW_ITEM_SPACING;

	// Top left coordinate of window items
	const float STATS_BOX_ANCHOR_X   = WINDOW_ITEM_SPACING;
	const float GAME_GRID_ANCHOR_X   = STATS_BOX_ANCHOR_X + STATS_BOX_WIDTH + WINDOW_ITEM_SPACING;
	const float PREVIEW_BOX_ANCHOR_X = GAME_GRID_ANCHOR_X + GAME_GRID_WIDTH + WINDOW_ITEM_SPACING;
	const float GAME_GRID_ANCHOR_Y   = WINDOW_ITEM_SPACING;
	const float PREVIEW_BOX_ANCHOR_Y = GAME_GRID_ANCHOR_Y + 2 * (GAME_GRID_SQUARE_SIZE + GAME_GRID_LINE_SIZE);
	const float STATS_BOX_ANCHOR_Y   = GAME_GRID_ANCHOR_Y + 2 * (GAME_GRID_SQUARE_SIZE + GAME_GRID_LINE_SIZE);
	const float STATS_LABEL_ANCHOR_X = STATS_BOX_ANCHOR_X + STATS_BOX_WIDTH / 2;
	const float STATS_LABEL_ANCHOR_Y = STATS_BOX_ANCHOR_Y - 32;
	const float NEXT_LABEL_ANCHOR_X  = PREVIEW_BOX_ANCHOR_X + PREVIEW_BOX_WIDTH / 2;
	const float NEXT_LABEL_ANCHOR_Y  = PREVIEW_BOX_ANCHOR_Y - 32;
}
