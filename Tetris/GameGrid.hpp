#pragma once

#include <mutex>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/RenderWindow.hpp"
#include "GamePiece.hpp"
#include "GameAttributes.hpp"

class GameGrid {
public:
	GameGrid(sf::RenderWindow& window, float anchorX, float anchorY, int rowCount, int columnCount);
	bool locationsAvailable(std::list<Location> locationsList);
	void commitLocations(std::list<Location> locationsList, sf::Color color);
	void drawPieceLocations(std::list<Location> locationsList, sf::Color color, bool ghost);
	void draw();
	void highlightRowsToBeDeleted();
	int deleteRowsToBeDeleted();
	void compactGrid();
	bool hasRowsToBeDeleted();
	void reset();
private:
	void deleteRow(int row);
	void drawSquare(int row, int column, sf::Color color);
	void drawGridLines();
	bool isRowFull(int row);
	void setRowColor(int row, sf::Color color);
	void drawGhostSquare(int row, int column, sf::Color color);
	void clearGrid();
	void drawLine(float x1, float y1, float x2, float y2, sf::Color color);

	mutable std::mutex						m_mutex;		// Used to make object thread-safe
	sf::RenderWindow&						m_window;		// Window in which grid is to be drawn
	float									m_anchorX;		// Left position of grid on window
	float									m_anchorY;		// Top position of grid on window
	int										m_rowCount;
	int										m_columnCount;
	std::list<int>							m_rowsToBeDeleted;
	std::vector< std::vector<sf::Color>>    m_grid;
};
