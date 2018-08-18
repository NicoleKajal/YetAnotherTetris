#include <cstdlib>
#include "stdafx.h"
#include "Location.hpp"
#include "GameAttributes.hpp"
#include "GamePieceShape.hpp"
#include "GamePieceFactory.hpp"

Location gamepieceLocations[GameAttributes::GAME_PIECE_SHAPE_COUNT][GameAttributes::GAME_PIECE_ORIENTATION_COUNT][GameAttributes::GAME_PIECE_LOCATION_COUNT] =
{
	{ // GAME_PIECE_SHAPE_LINE
	{ { 1,0 },{ 1,1 },{ 1,2 },{ 1,3 } },
	{ { 0,2 },{ 1,2 },{ 2,2 },{ 3,2 } },
	{ { 2,0 },{ 2,1 },{ 2,2 },{ 2,3 } },
    { { 0,1 },{ 1,1 },{ 2,1 },{ 3,1 } },
	},
	{ // GAME_PIECE_SHAPE_SQUARE
	{ { 0,1 },{ 0,2 },{ 1,1 },{ 1,2 } },
	{ { 0,1 },{ 0,2 },{ 1,1 },{ 1,2 } },
	{ { 0,1 },{ 0,2 },{ 1,1 },{ 1,2 } },
	{ { 0,1 },{ 0,2 },{ 1,1 },{ 1,2 } },
	},
	{ // GAME_PIECE_SHAPE_L
	{ { 0,2 },{ 1,0 },{ 1,1 },{ 1,2 } },
	{ { 0,1 },{ 1,1 },{ 2,1 },{ 2,2 } },
	{ { 1,0 },{ 1,1 },{ 1,2 },{ 2,0 } },
    { { 0,0 },{ 0,1 },{ 1,1 },{ 2,1 } },
	},
	{ // GAME_PIECE_SHAPE_J
	{ { 0,0 },{ 1,0 },{ 1,1 },{ 1,2 } },
    { { 0,1 },{ 0,2 },{ 1,1 },{ 2,1 } },
	{ { 1,0 },{ 1,1 },{ 1,2 },{ 2,2 } },
	{ { 0,1 },{ 1,1 },{ 2,0 },{ 2,1 } },
	},
	{ // GAME_PIECE_SHAPE_T
	{ { 0,1 },{ 1,0 },{ 1,1 },{ 1,2 } },
	{ { 0,1 },{ 1,1 },{ 1,2 },{ 2,1 } },
	{ { 1,0 },{ 1,1 },{ 1,2 },{ 2,1 } },
	{ { 0,1 },{ 1,0 },{ 1,1 },{ 2,1 } }
	},
	{ // GAME_PIECE_SHAPE_Z
	{ { 0,0 },{ 0,1 },{ 1,1 },{ 1,2 } },
	{ { 0,2 },{ 1,1 },{ 1,2 },{ 2,1 } },
	{ { 1,0 },{ 1,1 },{ 2,1 },{ 2,2 } },
    { { 0,1 },{ 1,0 },{ 1,1 },{ 2,0 } },
	},
	{ // GAME_PIECE_SHAPE_S
	{ { 0,1 },{ 0,2 },{ 1,0 },{ 1,1 } },
    { { 0,1 },{ 1,1 },{ 1,2 },{ 2,2 } },
    { { 1,1 },{ 1,2 },{ 2,0 },{ 2,1 } },
    { { 0,0 },{ 1,0 },{ 1,1 },{ 2,1 } },
	}
};
const sf::Color blue(0, 0, 220);
static const sf::Color red(240, 0, 0);
static const sf::Color green(0, 240, 0);
static const sf::Color yellow(240, 240, 0);
static const sf::Color purple(240, 0, 240);
static const sf::Color orange(240, 240, 0);
static const sf::Color cyan(0, 240, 240);

const int GAME_PIECE_COLOR_COUNT = 7;
sf::Color gamePieceColors[GAME_PIECE_COLOR_COUNT] = {
	green,
	blue,
	red,
	yellow,
	purple,
	orange,
	cyan
};

GamePiece* GamePieceFactory::makeGamePiece(GameGrid& gameGrid, GamePieceShape shape, sf::Color color) {
	return new GamePiece(gameGrid, gamepieceLocations[static_cast<int>(shape)], shape, color);
}
sf::Color lastColor = sf::Color::White;

GamePiece* GamePieceFactory::makeRandomGamePiece(GameGrid& gameGrid) {
	sf::Color newColor;
	const int MAX_RETRIES(3);
	for (int retry = 0; retry < MAX_RETRIES; retry++) {
		newColor = gamePieceColors[std::rand() % GAME_PIECE_COLOR_COUNT];
		if (newColor != lastColor)
			break;
	}
	lastColor = newColor;
	int index = std::rand() % 10;
	if (index >= GameAttributes::GAME_PIECE_SHAPE_COUNT) {
		index = 0;
	}
	GamePieceShape shape = static_cast<GamePieceShape>(index);
	return new GamePiece(gameGrid, gamepieceLocations[static_cast<int>(shape)], shape, newColor);
}
