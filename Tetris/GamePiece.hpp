#pragma once
#include <list>
#include <mutex>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Location.hpp"
#include "GamePieceShape.hpp"
#include "GameAttributes.hpp"

class GameGrid;

typedef Location(*locationArrayPointer)[GameAttributes::GAME_PIECE_LOCATION_COUNT];

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
typedef std::list<GamePiecePointer>::iterator GamePieceListIterator;