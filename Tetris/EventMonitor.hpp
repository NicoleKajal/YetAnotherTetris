#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameManager.hpp"

class EventMonitor
{
public:
	EventMonitor(sf::RenderWindow& window, GameManager& gameManager);
	void run();

private:
	sf::RenderWindow&	m_window;
	GameManager&        m_gameManager;
};
