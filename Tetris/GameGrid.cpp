#include <stdint.h>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "stdafx.h"
#include "GameGrid.hpp"

GameGrid::GameGrid(sf::RenderWindow& window, float anchorX, float anchorY, int rowCount, int columnCount)
: m_mutex(),
  m_window(window),
  m_anchorX(anchorX),
  m_anchorY(anchorY),
  m_rowCount(rowCount),
  m_columnCount(columnCount),
  m_rowsToBeDeleted(),
  m_grid() {

	m_grid.resize(m_rowCount);
	clearGrid();
}

void GameGrid::clearGrid() {
	for (int row = 0; row < m_rowCount; row++) {
		m_grid[row].resize(m_columnCount);
		for (int column = 0; column < m_columnCount; column++) {
			m_grid[row][column] = sf::Color::Black;
		}
	}
}

void GameGrid::reset() {
	m_rowsToBeDeleted.clear();
	clearGrid();
}

bool GameGrid::locationsAvailable(std::list<Location> locationsList) {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	for (Location& location : locationsList) {
		// check that the row is in the grid.
		if ((location.row >= m_rowCount) || (location.row < 0)) {
			return false;
		}
		// check that the row is in the grid.
		if ((location.column >= m_columnCount) || (location.column < 0)) {
			return false;
		}
		// check that the location is not occupied
		if (m_grid[location.row][location.column] != sf::Color::Black) {
			return false;
		}
	}
	return true;
}

void GameGrid::commitLocations(std::list<Location> locationsList, sf::Color color) {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	for (Location& location : locationsList) {
		m_grid[location.row][location.column] = color;
	}

	for (int row = 0; row < m_rowCount; row++) {
		if (isRowFull(row)) {
			m_rowsToBeDeleted.push_back(row);
		}
	}
}

bool GameGrid::isRowFull(int row) {
	for (int column = 0; column < m_columnCount; column++) {
		if (m_grid[row][column] == sf::Color::Black) {
			return false;
		}
	}
	return true;
}

void GameGrid::setRowColor(int row, sf::Color color) {
	for (int column = 0; column < m_columnCount; column++) {
		m_grid[row][column] = color;
	}
}

void GameGrid::highlightRowsToBeDeleted() {
	for (int row : m_rowsToBeDeleted) {
		setRowColor(row, sf::Color::White);
	}
}

int GameGrid::deleteRowsToBeDeleted() {
	int rowCount = 0;
	for (int row : m_rowsToBeDeleted) {
		setRowColor(row, sf::Color::Black);
		rowCount++;
	}
	return rowCount;
}

void GameGrid::compactGrid() {
	int offset = 0;
	for (std::list<int>::reverse_iterator iter = m_rowsToBeDeleted.rbegin(); iter != m_rowsToBeDeleted.rend(); ++iter) {
		int row = *iter + offset;
		deleteRow(row);
		offset++;
	}
	m_rowsToBeDeleted.clear();
}

void GameGrid::drawLine(float x1, float y1, float x2, float y2, sf::Color color) {
	sf::Vertex points[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2))
	};
	points[0].color = color;
	points[1].color = color;
	m_window.draw(points, 2, sf::Lines);
}

void GameGrid::drawGridLines() {
	static const sf::Color grey(100, 100, 100);
	static const sf::Color lightGrey(150, 150, 150);

	float startX = m_anchorX;
	float endX = m_anchorX + m_columnCount * (GameAttributes::SQUARE_WIDTH + GameAttributes::LINE_WIDTH);

	// Draw lines for the rows
	for (float row = 0; row <= m_rowCount; ++row) {
		float y = m_anchorY + row * (GameAttributes::SQUARE_HEIGHT + GameAttributes::LINE_WIDTH);
		drawLine(startX, y, endX, y, grey);
	}

	float startY = m_anchorY;
	float endY = m_anchorY + m_rowCount * (GameAttributes::SQUARE_HEIGHT + GameAttributes::LINE_WIDTH);

	// Draw lines for the columns
	for (float column = 0; column <= m_columnCount; ++column) {
		float x = m_anchorX + column * (GameAttributes::SQUARE_WIDTH + GameAttributes::LINE_WIDTH);
		drawLine(x, startY, x, endY, grey);
	}

	drawLine(startX, startY, endX, startY, lightGrey);
	drawLine(startX, endY, endX, endY, lightGrey);
	drawLine(startX, startY, startX, endY, lightGrey);
	drawLine(endX, startY, endX, endY, lightGrey);


}

void GameGrid::drawSquare(int row, int column, sf::Color color) {
	float x = m_anchorX + (GameAttributes::SQUARE_WIDTH + GameAttributes::LINE_WIDTH) * column;
	float y = GameAttributes::LINE_WIDTH + m_anchorY + (GameAttributes::SQUARE_HEIGHT + GameAttributes::LINE_WIDTH) * row;

	sf::RectangleShape rectangle(sf::Vector2f(GameAttributes::SQUARE_WIDTH, GameAttributes::SQUARE_HEIGHT));
	rectangle.setFillColor(color);
	rectangle.setPosition(sf::Vector2f(x, y));
	m_window.draw(rectangle);
}

void GameGrid::drawGhostSquare(int row, int column, sf::Color color) {
	const float GHOST_LINE_THICKNESS = 2;
	float x = m_anchorX + (GameAttributes::SQUARE_WIDTH + GameAttributes::LINE_WIDTH) * column + GHOST_LINE_THICKNESS;
	float y = GameAttributes::LINE_WIDTH + m_anchorY + (GameAttributes::SQUARE_HEIGHT + GameAttributes::LINE_WIDTH) * row + GHOST_LINE_THICKNESS;

	sf::RectangleShape rectangle(sf::Vector2f(GameAttributes::SQUARE_WIDTH - (2 * GHOST_LINE_THICKNESS), GameAttributes::SQUARE_HEIGHT - (2 * GHOST_LINE_THICKNESS)));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setPosition(sf::Vector2f(x, y));
	m_window.draw(rectangle);
}

void GameGrid::draw() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	// draw the grid lines
	drawGridLines();

	// Draw the existing pieces
	for (int row = 0; row < m_rowCount; row++) {
		for (int column = 0; column < m_columnCount; column++) {
			if (m_grid[row][column] != sf::Color::Black) {
				drawSquare(row, column, m_grid[row][column]);
			}
		}
	}
}

void GameGrid::drawPieceLocations(std::list<Location> locationsList, sf::Color color, bool ghost) {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	for (Location& location : locationsList) {
		drawSquare(location.row, location.column, color);
		if (ghost) {
			drawGhostSquare(location.row, location.column, color);
		}
	}
}

void GameGrid::deleteRow(int rowToBeDeleted) {
	for (int row = rowToBeDeleted; row >= 0; row--) {
		for (int column = 0; column < m_columnCount; column++) {
			if (row != 0) {
				m_grid[row][column] = m_grid[row - 1][column];
			}
			else {
			    m_grid[row][column] = sf::Color::Black;
			}
		}
	}
}

bool GameGrid::hasRowsToBeDeleted() {
	return !m_rowsToBeDeleted.empty();
}

