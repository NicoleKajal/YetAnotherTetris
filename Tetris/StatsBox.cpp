#include "stdafx.h"
#include "StatsBox.hpp"
#include "GameAttributes.hpp"

StatsBox::StatsBox(sf::RenderWindow& window, float x, float y, float height, float width)
: m_window(window),
  m_mutex(),
  m_elapsedTime(0),
  m_lineCount(0),
  m_pieceCount(0),
  m_anchorX(x),
  m_anchorY(y),
  m_height(height),
  m_width(width),
  m_timeLabel("Time", GameAttributes::STATS_FONT_SIZE, x + width / 2, y + 0.5f * height / 6),
  m_timeText("0:00", GameAttributes::STATS_FONT_SIZE, x + width / 2, y + 1.5f * height / 6),
  m_linesLabel("Lines", GameAttributes::STATS_FONT_SIZE, x + width / 2, y + 2.5f * height / 6),
  m_linesText("0", GameAttributes::STATS_FONT_SIZE, x + width / 2, y + 3.5f * height / 6),
  m_piecesLabel("Pieces", GameAttributes::STATS_FONT_SIZE, x + width / 2, y + 4.5f * height / 6),
  m_piecesText("0", GameAttributes::STATS_FONT_SIZE, x + width / 2, y + 5.5f * height / 6) {
}

void StatsBox::incrementPieceCount() {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	m_pieceCount++;
}

void StatsBox::drawLine(float x1, float y1, float x2, float y2, sf::Color color) {
	sf::Vertex points[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2))
	};
	points[0].color = color;
	points[1].color = color;
	m_window.draw(points, 2, sf::Lines);
}

void StatsBox::draw() {
	float rowHeight = m_height / 6;
	float startX = m_anchorX;
	float endX = m_anchorX + m_width;
	float startY = m_anchorY;
	float endY = m_anchorY + m_height;
	static const sf::Color lightGrey(150, 150, 150);
	drawLine(startX, startY, endX, startY, lightGrey);
	drawLine(startX, endY, endX, endY, lightGrey);
	drawLine(startX, startY, startX, endY, lightGrey);
	drawLine(endX, startY, endX, endY, lightGrey);
	for (int row = 0; row < 6; row++) {
		drawLine(startX, startY + row * rowHeight, endX, startY + row * rowHeight, lightGrey);
	}

	{
		std::lock_guard<std::mutex> scopedLock(m_mutex);
		m_piecesText.setNumberCentered(m_pieceCount);
		m_linesText.setNumberCentered(m_lineCount);
		m_timeText.setTimeCentered(m_elapsedTime);
	}

	m_window.draw(m_timeLabel);
	m_window.draw(m_timeText);
	m_window.draw(m_linesLabel);
	m_window.draw(m_linesText);
	m_window.draw(m_piecesLabel);
	m_window.draw(m_piecesText);
}

void StatsBox::updateRowCount(int rowCount) {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	m_lineCount += rowCount;
}

void StatsBox::updateElapsedTime(int elapsedTime) {
	std::lock_guard<std::mutex> scopedLock(m_mutex);
	m_elapsedTime = elapsedTime;
}


