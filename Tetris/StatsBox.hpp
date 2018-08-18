#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameText.hpp"
#include <mutex>

class StatsBox {
public:
	StatsBox(sf::RenderWindow& window, float x, float y, float height, float width);
	void draw();
	void incrementPieceCount();
	void updateRowCount(int rowCount);
	void updateElapsedTime(int elapsedTime);

private:
	void drawLine(float x1, float y1, float x2, float y2, sf::Color color);

	sf::RenderWindow&	m_window;
	std::mutex			m_mutex;
	int					m_elapsedTime;
	int					m_lineCount;
	int                 m_pieceCount;
	float				m_anchorX;		// Left position of grid on window
	float				m_anchorY;		// Top position of grid on window
	float               m_height;
	float               m_width;
	GameText            m_timeLabel;
	GameText            m_timeText;
	GameText            m_linesLabel;
	GameText            m_linesText;
	GameText            m_piecesLabel;
	GameText            m_piecesText;
};
