#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "EventType.hpp"
#include "GameManager.hpp"
#include "EventMonitor.hpp"

// Events must be polled in the window's thread
// This is an important limitation of most operating systems : the event loop(more precisely, the pollEvent or 
// waitEvent function) must be called in the same thread that created the window.This means that if you want to 
// create a dedicated thread for event handling, you'll have to make sure that the window is created in this thread 
// too. If you really want to split things between threads, it is more convenient to keep event handling in the main 
// thread and move the rest (rendering, physics, logic, ...) to a separate thread instead. This configuration will 
// also be compatible with the other limitation described below.

EventMonitor::EventMonitor(sf::RenderWindow& window, GameManager& gameManager)
: m_window(window),
  m_gameManager(gameManager) {

	// SFML supports multi - threaded drawing, and you don't even have to do anything to make it work. 
	// The only thing to remember is to deactivate a window before using it in another thread. That's 
	// because a window(more precisely its OpenGL context) cannot be active in more than one thread at the same time.
	m_window.setActive(false);
	//srand(static_cast<unsigned int>(time(nullptr)));
}

/**
 * This is an important limitation of most operating systems: the event loop (more precisely, 
 * the pollEvent or waitEvent function) must be called in the same thread that created the window.
 */
/*
    Process any pending events, which are polled.  Events must be polled in the window's thread.
*/
void EventMonitor::run() {
	sf::Event event;
	while (m_window.isOpen()) {
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				m_gameManager.addEvent(EventType::EXIT);
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Key::Up:
					m_gameManager.addEvent(EventType::ROTATE_LEFT);
					//m_gameManager.addEvent(EventType::DROP_PIECE);
					break;

				case sf::Keyboard::Key::Down:
					m_gameManager.addEvent(EventType::MOVE_DOWN);
					break;

				case sf::Keyboard::Key::Left:
					m_gameManager.addEvent(EventType::MOVE_LEFT);
					break;

				case sf::Keyboard::Key::Right:
					m_gameManager.addEvent(EventType::MOVE_RIGHT);
					break;

				case sf::Keyboard::Key::Space:
					//m_gameManager.addEvent(EventType::ROTATE_LEFT);
					m_gameManager.addEvent(EventType::DROP_PIECE);
					break;
				}
			}
		}
	}
}
