#pragma once

#include <SFML/Graphics/Color.hpp>
#include "GamePieceShape.hpp"
#include "GamePiece.hpp"
#include "GameGrid.hpp"

class GamePieceFactory {
public:
	static GamePiece* makeGamePiece(GameGrid& gameGrid, GamePieceShape shape, sf::Color color);
	static GamePiece* makeRandomGamePiece(GameGrid& gameGrid);
};