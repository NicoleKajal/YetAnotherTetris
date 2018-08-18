#include "stdafx.h"
#include "PreviewBox.hpp"
#include "GameAttributes.hpp"


struct Offsets {
	float x;
	float y;
};

static Offsets offsetsArray[GameAttributes::GAME_PIECE_SHAPE_COUNT] = {
    {0, -1 * (GameAttributes::GAME_GRID_SQUARE_SIZE / 2)},
	{0, 0},
	{GameAttributes::GAME_GRID_SQUARE_SIZE / 2, 0},
	{GameAttributes::GAME_GRID_SQUARE_SIZE / 2, 0},
	{GameAttributes::GAME_GRID_SQUARE_SIZE / 2, 0},
	{GameAttributes::GAME_GRID_SQUARE_SIZE / 2, 0},
	{GameAttributes::GAME_GRID_SQUARE_SIZE / 2, 0},
};

PreviewBox::PreviewBox(sf::RenderWindow& window, float anchorX, float anchorY, int gamePieceCount)
  : m_mutex(),
	m_window(window),
	m_anchorX(anchorX),
	m_anchorY(anchorY),
	m_gamePieceCount(gamePieceCount) {
}

void PreviewBox::drawLine(float x1, float y1, float x2, float y2, sf::Color color) {
	sf::Vertex points[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2))
	};
	points[0].color = color;
	points[1].color = color;
	m_window.draw(points, 2, sf::Lines);
}

void PreviewBox::drawSquare(float x, float y, sf::Color color) {
	sf::RectangleShape rectangle(sf::Vector2f(GameAttributes::GAME_GRID_SQUARE_SIZE, GameAttributes::GAME_GRID_SQUARE_SIZE));
	rectangle.setFillColor(color);
	rectangle.setPosition(sf::Vector2f(x, y));
	m_window.draw(rectangle);
}

void PreviewBox::draw(GamePieceList& gamePieceList) {
	// Draw the lines around the preview box
	float startX = m_anchorX;
	float endX = m_anchorX + GameAttributes::PREVIEW_BOX_WIDTH;
	float startY = m_anchorY;
	float endY = m_anchorY + (m_gamePieceCount * GameAttributes::PREVIEW_BOX_ITEM_ROW_COUNT) * (GameAttributes::GAME_GRID_SQUARE_SIZE + GameAttributes::GAME_GRID_LINE_SIZE) + ((m_gamePieceCount + 1) * GameAttributes::PREVIEW_BOX_BORDER_WIDTH);

	static const sf::Color lightGrey(150, 150, 150);
	drawLine(startX, startY, endX, startY, lightGrey);
	drawLine(startX, endY, endX, endY, lightGrey);
	drawLine(startX, startY, startX, endY, lightGrey);
	drawLine(endX, startY, endX, endY, lightGrey);

	// Draw the next pieces (each piece is drawn as four squares)
	int pieceCount = 0;
	for (GamePiecePointer gamePiece: gamePieceList) {
		float yMiniBoxOffset = pieceCount * (GameAttributes::PREVIEW_BOX_ITEM_ROW_COUNT * GameAttributes::GAME_GRID_SQUARE_SIZE + GameAttributes::GAME_GRID_LINE_SIZE + GameAttributes::PREVIEW_BOX_BORDER_WIDTH);
		for (Location& location : gamePiece->getPreviewLocations()) {
			Offsets offsets = offsetsArray[static_cast<int>(gamePiece->shape())];
			float x = m_anchorX + GameAttributes::PREVIEW_BOX_BORDER_WIDTH + (GameAttributes::GAME_GRID_SQUARE_SIZE + GameAttributes::GAME_GRID_LINE_SIZE) * location.column + offsets.x;
			float y = m_anchorY + GameAttributes::PREVIEW_BOX_BORDER_WIDTH + (GameAttributes::GAME_GRID_SQUARE_SIZE + GameAttributes::GAME_GRID_LINE_SIZE) * location.row + yMiniBoxOffset + offsets.y;
			drawSquare(x, y, gamePiece->color());
		}
		if (++pieceCount >= m_gamePieceCount)
			break;
	}
}