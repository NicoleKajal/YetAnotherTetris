#pragma once
#include <memory>
#include <thread>
#include <memory>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameGrid.hpp"
#include "GamePiece.hpp"
#include "EventData.hpp"
#include "EventType.hpp"
#include "MessageQueue.hpp"
#include "EventData.hpp"

class GameManager {
public:
	GameManager(sf::RenderWindow& window);
	void addEvent(EventType event);
	void addEventDelayed(EventType event, int delayTime);

private:
	void processEvents();
	void gameGravity();
	void commitPieceToGrid();
	void playBack();

	sf::RenderWindow&				m_window;
	std::vector<EventDataPointer>	m_eventHistory;
	GameGrid 						m_gameGrid;
	GamePiecePointer          		m_gamePiece;
	MessageQueue<EventType>			m_messageQueue;
	std::thread						m_thread;
	std::thread						m_gravityThread;
};