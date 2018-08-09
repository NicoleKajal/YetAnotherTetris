#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <mutex>
#include <memory>
#include "Location.hpp"
#include "GamePieceShape.hpp"

class GameGrid;

// A game piece will always occupy four locations, which can have a maximum height of four
// locations, a maximum width of four locations, and can be oriented in four different positions
// (each new orientation can be viewed as a result of being rotated by 90 degrees).
const int GAME_PIECE_LOCATION_COUNT = 4;
const int GAME_PIECE_MAX_HIGHT = 4;
const int GAME_PIECE_MAX_WIDTH = 4;
const int GAME_PIECE_ORIENTATION_COUNT = 4;

typedef Location(*locationArrayPointer)[GAME_PIECE_LOCATION_COUNT];

class GamePiece {
public:
	GamePiece(GameGrid& gameGrid, locationArrayPointer locations, GamePieceShape shape, sf::Color color);
	GamePiece(const GamePiece &gamePiece);
	bool canEnterGrid();
	bool rotateRight();
	bool rotateLeft();
	bool moveLeft();
	bool moveRight();
	bool drop();
	bool moveDown();
	bool moveUp();
	void commitToGrid();
	void draw();
	GameGrid& gameGrid() const;
	int anchorRow() const;
	int anchorColumn() const;
	int orientation() const;
	sf::Color color() const;
	GamePieceShape shape() const;
	locationArrayPointer locations() const;
	std::list<Location> getGridLocations();
	std::list<Location> getPreviewLocations();

private:
	bool tryMove(int& parameter, int newValue);
	
	mutable std::mutex      m_mutex;
	const GamePieceShape    m_shape;
	const sf::Color			m_color;
	int                     m_anchorRow;
	int				        m_anchorColumn;
	int				        m_orientation;
	locationArrayPointer	m_locations;
	GameGrid&               m_gameGrid;
};

typedef std::shared_ptr<GamePiece> GamePiecePointer;
typedef std::list<GamePiecePointer> GamePieceList;