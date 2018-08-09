#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "GamePiece.hpp"
#include "GameGrid.hpp"

static const int GAME_PIECE_GRID_ENTRY_ROW = 0;
static const int GAME_PIECE_GRID_ENTRY_COLUMN = (GameAttributes::GAME_GRID_COLUMN_COUNT - GAME_PIECE_MAX_WIDTH) / 2;
static const int GAME_PIECE_GRID_ENTRY_ORIENTATION = 0;

GamePiece::GamePiece(GameGrid &gameGrid, locationArrayPointer locations, GamePieceShape shape, sf::Color color)
: m_mutex(),
  m_shape(shape),
  m_color(color),
  m_gameGrid(gameGrid),
  m_anchorRow(GAME_PIECE_GRID_ENTRY_ROW),
  m_anchorColumn(GAME_PIECE_GRID_ENTRY_COLUMN),
  m_orientation(GAME_PIECE_GRID_ENTRY_ORIENTATION),
  m_locations(locations) {
}

GamePiece::GamePiece(const GamePiece &gamePiece)
: m_mutex(),
  m_shape(gamePiece.shape()),
  m_color(gamePiece.color()),
  m_gameGrid(gamePiece.gameGrid()),
  m_anchorRow(gamePiece.anchorRow()),
  m_anchorColumn(gamePiece.anchorColumn()),
  m_orientation(gamePiece.orientation()),
  m_locations(gamePiece.locations()) {
}

bool GamePiece::rotateRight() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	return tryMove(m_orientation, (m_orientation + 1) >= GAME_PIECE_ORIENTATION_COUNT ? 0 : m_orientation + 1);
}

bool GamePiece::rotateLeft() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	return tryMove(m_orientation, (m_orientation == 0 ? GAME_PIECE_ORIENTATION_COUNT : m_orientation) - 1);
}

bool GamePiece::moveLeft() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	return tryMove(m_anchorColumn, m_anchorColumn - 1);
}

bool GamePiece::moveRight() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	return tryMove(m_anchorColumn, m_anchorColumn + 1);
}

bool GamePiece::moveUp() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	return tryMove(m_anchorRow, m_anchorRow - 1);
}

bool GamePiece::moveDown() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	return tryMove(m_anchorRow, m_anchorRow + 1);
}

bool GamePiece::drop() {
	while (moveDown()) {
		;
	}
	return true;
}

bool GamePiece::canEnterGrid() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	return m_gameGrid.locationsAvailable(getGridLocations());
}

void GamePiece::commitToGrid() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	m_gameGrid.commitLocations(getGridLocations(), m_color);
}

bool GamePiece::tryMove(int& parameter, int newValue) {
	int originalValue = parameter;
	parameter = newValue;
	bool success = m_gameGrid.locationsAvailable(getGridLocations());
	if (!success) {
		parameter = originalValue;
	}
	return success;
}

std::list<Location> GamePiece::getGridLocations() {
	std::list <Location> pieceLocations;
	for (int index = 0; index < GAME_PIECE_LOCATION_COUNT; index++) {
		Location location = m_locations[m_orientation][index];
		location.row += m_anchorRow;
		location.column += m_anchorColumn;
		pieceLocations.push_back(location);
	}
	return pieceLocations;
}

std::list<Location> GamePiece::getPreviewLocations() {
	std::list <Location> pieceLocations;
	for (int index = 0; index < GAME_PIECE_LOCATION_COUNT; index++) {
		Location location = m_locations[m_orientation][index];
		pieceLocations.push_back(location);
	}
	return pieceLocations;
}

void GamePiece::draw() {
	const sf::Color blue(0, 0, 220);
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	GamePiece ghostGamePiece = *this;
	ghostGamePiece.drop();
	sf::Color ghostColor(m_color.r / 2, m_color.g / 2, m_color.b / 2);
	if (m_color == blue)
		ghostColor = m_color;

	m_gameGrid.drawPieceLocations(ghostGamePiece.getGridLocations(), ghostColor, true);
	m_gameGrid.drawPieceLocations(getGridLocations(), m_color, false);
}

GameGrid& GamePiece::gameGrid() const {
	return m_gameGrid;
}
int GamePiece::anchorRow() const {
	return m_anchorRow;
}
int GamePiece::anchorColumn() const {
	return m_anchorColumn;
}
int GamePiece::orientation() const {
	return m_orientation;
}
sf::Color GamePiece::color() const {
	return m_color;
}
GamePieceShape GamePiece::shape() const {
	return m_shape;
}
locationArrayPointer GamePiece::locations() const {
	return m_locations;
}