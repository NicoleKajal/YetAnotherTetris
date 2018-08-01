#include <SFML/Graphics/RenderWindow.hpp>
#include "stdafx.h"
#include "GameManager.hpp"
#include "EventMonitor.hpp"
#include "GameAttributes.hpp"

const char* GAME_ATTRIBUTES_WINDOW_TITLE = "Yet Another Tetris";

// Events must be polled in the window's thread
// This is an important limitation of most operating systems : the event loop(more precisely, the pollEvent or 
// waitEvent function) must be called in the same thread that created the window.This means that if you want to 
// create a dedicated thread for event handling, you'll have to make sure that the window is created in this thread 
// too. If you really want to split things between threads, it is more convenient to keep event handling in the main 
// thread and move the rest (rendering, physics, logic, ...) to a separate thread instead. This configuration will 
// also be compatible with the other limitation described below.

int main()
{
	sf::RenderWindow window(sf::VideoMode(GameAttributes::WINDOW_WIDTH, GameAttributes::WINDOW_HEIGHT),
		                    GAME_ATTRIBUTES_WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
	GameManager gameManager(window);
	EventMonitor eventMonitor(window, gameManager);
	eventMonitor.run();
	return 0;
}