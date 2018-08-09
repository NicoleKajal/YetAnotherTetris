#include "stdafx.h"
#include "PreviewBox.hpp"
#include "GameAttributes.hpp"

static const float BOX_BORDER_WIDTH = 30;
static const int MINI_BOX_ROW_COUNT = 2;
static const int MINI_BOX_COLUMN_COUNT = 4;

struct Offsets {
	float x;
	float y;
};

static Offsets offsetsArray[GameAttributes::GAME_PIECE_SHAPE_COUNT] = {
    {0, -1 * (GameAttributes::SQUARE_HEIGHT / 2)},
	{0, 0},
	{GameAttributes::SQUARE_WIDTH / 2, 0},
	{GameAttributes::SQUARE_WIDTH / 2, 0},
	{GameAttributes::SQUARE_WIDTH / 2, 0},
	{GameAttributes::SQUARE_WIDTH / 2, 0},
	{GameAttributes::SQUARE_WIDTH / 2, 0},
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
	sf::RectangleShape rectangle(sf::Vector2f(GameAttributes::SQUARE_WIDTH, GameAttributes::SQUARE_HEIGHT));
	rectangle.setFillColor(color);
	rectangle.setPosition(sf::Vector2f(x, y));
	m_window.draw(rectangle);
}

void PreviewBox::draw(GamePieceList& gamePieceList) {
	// Draw the lines around the preview box
	float startX = m_anchorX;
	float endX = m_anchorX + MINI_BOX_COLUMN_COUNT * (GameAttributes::SQUARE_WIDTH + GameAttributes::LINE_WIDTH) + (2 * BOX_BORDER_WIDTH);
	float startY = m_anchorY;
	float endY = m_anchorY + (m_gamePieceCount * MINI_BOX_ROW_COUNT) * (GameAttributes::SQUARE_HEIGHT + GameAttributes::LINE_WIDTH) + ((m_gamePieceCount + 1) * BOX_BORDER_WIDTH);

	static const sf::Color grey(50, 50, 50);
	drawLine(startX, startY, endX, startY, grey);
	drawLine(startX, endY, endX, endY, grey);
	drawLine(startX, startY, startX, endY, grey);
	drawLine(endX, startY, endX, endY, grey);

	// Draw the next pieces (each piece is drawn as four squares)
	int pieceCount = 0;
	for (GamePiecePointer gamePiece : gamePieceList) {
		float yMiniBoxOffset = pieceCount++ * (MINI_BOX_ROW_COUNT * GameAttributes::SQUARE_HEIGHT + GameAttributes::LINE_WIDTH + BOX_BORDER_WIDTH);
		for (Location& location : gamePiece->getPreviewLocations()) {
			Offsets offsets = offsetsArray[static_cast<int>(gamePiece->shape())];
			float x = m_anchorX + BOX_BORDER_WIDTH + (GameAttributes::SQUARE_WIDTH + GameAttributes::LINE_WIDTH) * location.column + offsets.x;
			float y = m_anchorY + BOX_BORDER_WIDTH + (GameAttributes::SQUARE_HEIGHT + GameAttributes::LINE_WIDTH) * location.row + yMiniBoxOffset + offsets.y;
			drawSquare(x, y, gamePiece->color());
		}
	}
}