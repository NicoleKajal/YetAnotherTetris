#pragma once
#include <memory>
#include <thread>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameGrid.hpp"
#include "GamePiece.hpp"
#include "EventType.hpp"
#include "MessageQueue.hpp"

class GameManager {
public:
	GameManager(sf::RenderWindow& window);
	void addEvent(EventType event);
	void addEventDelayed(EventType event, int delayTime);

private:
	void processEvents();
	void gameGravity();
	void commitPieceToGrid();

	sf::RenderWindow&           m_window;
	GameGrid 					m_gameGrid;
	std::shared_ptr<GamePiece>	m_gamePiece;
	MessageQueue<EventType>		m_messageQueue;
	std::thread					m_thread;
	std::thread                 m_gravityThread;
};