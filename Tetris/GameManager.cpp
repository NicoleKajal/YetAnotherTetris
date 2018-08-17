#include <memory>
#include "stdafx.h"
#include "StatsBox.hpp"
#include "EventData.hpp"
#include "GamePiece.hpp"
#include "PreviewBox.hpp"
#include "GameManager.hpp"
#include "DelayedEvent.hpp"
#include "GameAttributes.hpp"
#include "GamePieceFactory.hpp"
#include <iostream>
#include <chrono>

const int FONT_SIZE = 46;

GameManager::GameManager(sf::RenderWindow& window)
: m_window(window),
  m_nextLabel("Next", FONT_SIZE, GameAttributes::GAME_PREVIEW_BOX_X + GameAttributes::PREVIEW_BOX_WIDTH / 2, GameAttributes::GAME_GRID_ANCHOR_Y + 28),
  m_statsLabel("Stats", FONT_SIZE, GameAttributes::SCREEN_ITEM_PADDING + GameAttributes::PREVIEW_BOX_WIDTH / 2, GameAttributes::GAME_GRID_ANCHOR_Y + 28),
  m_eventHistory(),
  m_gameGrid(m_window, GameAttributes::GAME_GRID_ANCHOR_X, GameAttributes::GAME_GRID_ANCHOR_Y,
	         GameAttributes::GAME_GRID_ROW_COUNT, GameAttributes::GAME_GRID_COLUMN_COUNT),
  m_gamePiece(),
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
	addEvent(EventType::CREATE_NEW_GAME_PIECE);
}

void GameManager::processEvents() {
	auto start = std::chrono::high_resolution_clock::now();
	StatsBox statsBox(m_window, GameAttributes::STATS_BOX_X, GameAttributes::STATS_BOX_Y, GameAttributes::PREVIEW_BOX_HEIGHT, GameAttributes::STATS_BOX_WIDTH);
	PreviewBox previewBox(m_window, GameAttributes::GAME_PREVIEW_BOX_X, GameAttributes::GAME_PREVIEW_BOX_Y, GameAttributes::PREVIEW_COUNT);
	GamePieceList upcomingGamePieces;

	for (int previewCount = 0; previewCount < GameAttributes::PREVIEW_COUNT; previewCount++) {
		upcomingGamePieces.push_back(GamePiecePointer(GamePieceFactory::makeRandomGamePiece(m_gameGrid)));
	}

	bool gameDone = false;
	addEvent(EventType::CREATE_NEW_GAME_PIECE);
	for (;;) {
		EventType event = m_messageQueue.remove();

		switch (event) {
		    case EventType::CREATE_NEW_GAME_PIECE:
				m_gamePiece = upcomingGamePieces.front();
				upcomingGamePieces.pop_front();
				upcomingGamePieces.push_back(GamePiecePointer(GamePieceFactory::makeRandomGamePiece(m_gameGrid)));
				m_eventHistory.push_back(EventDataPointer(new EventData(event, m_gamePiece->shape(), m_gamePiece->color())));
				if (!m_gamePiece->canEnterGrid()) {
					gameDone = true;
					playBack();
				}
				else {
					statsBox.incrementPieceCount();
				}
				break;
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
				}
				break;
			case EventType::EXIT:
				m_window.close();
				break;
			case EventType::REMOVE_ROWS:
			{
				int rowCount = m_gameGrid.deleteRowsToBeDeleted();
				statsBox.updateRowCount(rowCount);
			}
				break;
			case EventType::COMPACT_GRID:
				m_gameGrid.compactGrid();
				break;
			default:
				break;
		}

		if (event != EventType::CREATE_NEW_GAME_PIECE) {
			m_eventHistory.push_back(EventDataPointer(new EventData(event)));
		}
		
		// Render the drawings in the window.  The steps taken following the recommended sequence
		// described in the SFML 2D drawing tutorial, which are:
		//  1) Clear previous content of the window's display buffer
		//  2) Draw objects in the window's display buffer
		//  3) Display the contents of display buffer on the screen

		if (!gameDone) {
			auto finish = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = finish - start;
			double seconds = elapsed.count();

			statsBox.updateElapsedTime(static_cast<int>(seconds));
			m_window.clear();
			m_gameGrid.draw();
			previewBox.draw(upcomingGamePieces);
			m_gamePiece->draw();
			statsBox.draw();
			m_window.draw(m_statsLabel);
			m_window.draw(m_nextLabel);
			m_window.display();
		}
	}
}
void GameManager::playBack() {

	const int PREVIEW_COUNT = 3;
	PreviewBox previewBox(m_window, 650, 100, PREVIEW_COUNT);
	GamePieceList upcomingGamePieces;

	for (size_t index = 0; index < m_eventHistory.size(); index++) {
		EventDataPointer eventData = m_eventHistory[index];
		//for (EventDataPointer eventData : m_eventHistory) {
		if (eventData->event() == EventType::CREATE_NEW_GAME_PIECE) {
			upcomingGamePieces.push_back(GamePiecePointer(GamePieceFactory::makeGamePiece(m_gameGrid, eventData->gamePieceShape(), eventData->gamePieceColor())));
		}
	}

	bool gameDone = false;
    std::this_thread::sleep_for(std::chrono::seconds(3));
	m_gameGrid.reset();

	for (size_t index = 0; index < m_eventHistory.size(); index++) {
	    EventDataPointer eventData = m_eventHistory[index];
		switch (eventData->event()) {
			case EventType::CREATE_NEW_GAME_PIECE:
				m_gamePiece = upcomingGamePieces.front();
				upcomingGamePieces.pop_front();
				if (!m_gamePiece->canEnterGrid()) {
					gameDone = true;
					playBack();
				}
				break;
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
				m_gamePiece->commitToGrid();
				break;
			case EventType::MOVE_DOWN:
				if (!m_gamePiece->moveDown()) {
					m_gamePiece->commitToGrid();
				}
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

		if (!gameDone) {
			m_window.clear();
			m_gameGrid.draw();
			m_gamePiece->draw(); 
			previewBox.draw(upcomingGamePieces);
			m_window.display();
		}

		if ((index + 1) >= m_eventHistory.size()) {
			return;
		}

		EventDataPointer nextEventData = m_eventHistory[index + 1];

		std::chrono::duration<double> sleepDuration = nextEventData->timestamp() - eventData->timestamp();

		std::this_thread::sleep_for(sleepDuration / 2);
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
	const int CHANGE_VALUE = 10;
	int delay = 1000;
	int changeCountDown = CHANGE_VALUE;
	for (;;) {
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		addEvent(EventType::MOVE_DOWN);
		if (changeCountDown <= 0) {
			changeCountDown = CHANGE_VALUE;
			if (delay > MIN_DELAY) {
				delay -= 20;
			}
		}
	}
}


