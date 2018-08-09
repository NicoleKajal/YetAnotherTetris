#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "GamePiece.hpp"
#include <mutex>
#include <vector>

class PreviewBox {
public:
	PreviewBox(sf::RenderWindow& window, float anchorX, float anchorY, int gamePieceCount);
	void draw(GamePieceList& gamePieceList);

private:
	void drawLine(float x1, float y1, float x2, float y2, sf::Color color);
	void drawSquare(float anchorX, float anchorY, sf::Color color);

	mutable std::mutex	m_mutex;			// Used to make object thread-safe
	sf::RenderWindow&	m_window;			// Window in which preview window is to be drawn
	float				m_anchorX;			// Left position of preview window on window
	float				m_anchorY;			// Top position of preview window on window
	int					m_gamePieceCount;	// Number of game pieces in preview window
};
