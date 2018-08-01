#include <iostream>
#include "stdafx.h"
#include "GamePiece.hpp"
#include "GameManager.hpp"
#include "DelayedEvent.hpp"
#include "GameAttributes.hpp"
#include "GamePieceFactory.hpp"

GameManager::GameManager(sf::RenderWindow& window)
: m_window(window),
  m_gameGrid(m_window, GameAttributes::GAME_GRID_ANCHOR_X, GameAttributes::GAME_GRID_ANCHOR_Y,
	         GameAttributes::GAME_GRID_ROW_COUNT, GameAttributes::GAME_GRID_COLUMN_COUNT),
  m_gamePiece(GamePieceFactory::makeRandomGamePiece(m_gameGrid)),
  m_messageQueue(), 
  m_thread(&GameManager::processEvents, this),
  m_gravityThread(&GameManager::gameGravity, this) {
}

void GameManager::commitPieceToGrid() {
	m_gamePiece->commitToGrid();
	if (m_gameGrid.hasRowsToBeDeleted()) {
		m_gameGrid.highlightRowsToBeDeleted();
		addEventDelayed(EventType::REMOVE_ROWS, 100);
		addEventDelayed(EventType::COMPACT_GRID, 200);
	}
	m_gamePiece.reset(GamePieceFactory::makeRandomGamePiece(m_gameGrid));
}
void GameManager::processEvents() {
	for (;;) {
		EventType event = m_messageQueue.remove();

		switch (event) {
		case EventType::MOVE_LEFT:
				m_gamePiece->moveLeft();
				break;
			case EventType::MOVE_RIGHT:
				m_gamePiece->moveRight();
				break;
			case EventType::ROTATE_LEFT:
				m_gamePiece->rotateLeft();
				break;
			case EventType::MOVE_UP:
				m_gamePiece->rotateLeft();
				break;
			case EventType::DROP_PIECE:
				m_gamePiece->drop();
				commitPieceToGrid();
				break;
			case EventType::MOVE_DOWN:
				if (!m_gamePiece->moveDown()) {
					commitPieceToGrid();				
					// check for end of game if piece can't be added to grid
				}
				break;
			case EventType::EXIT:
				m_window.close();
				break;
			case EventType::REMOVE_ROWS:
				m_gameGrid.deleteRowsToBeDeleted();
				break;
			case EventType::COMPACT_GRID:
				m_gameGrid.compactGrid();
				break;
			default:
				break;
		}

		// Render the drawings in the window.  The steps taken following the recommended sequence
		// described in the SFML 2D drawing tutorial, which are:
		//  1) Clear previous content of the window's display buffer
		//  2) Draw objects in the window's display buffer
		//  3) Display the contents of display buffer on the screen

		m_window.clear();
		m_gameGrid.draw();
		m_gamePiece->draw();
		m_window.display();
	}
}

void GameManager::addEvent(EventType event) {
	m_messageQueue.add(event);
}

void GameManager::addEventDelayed(EventType event, int delayTime) {
	new DelayedEvent(*this, event, delayTime);
}

void GameManager::gameGravity() {
	const int MIN_DELAY = 200;
	const int CHANGE_VALUE = 20;
	int delay = 1000;
	int changeCountDown = CHANGE_VALUE;
	for (;;) {
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		addEvent(EventType::MOVE_DOWN);
		if (changeCountDown <= 0) {
			changeCountDown = CHANGE_VALUE;
			if (delay > MIN_DELAY) {
				delay -= 10;
			}
		}
	}
}


