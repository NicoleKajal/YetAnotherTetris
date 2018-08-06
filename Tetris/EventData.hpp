#pragma once
#include <chrono>
#include <memory>
#include "EventType.hpp"
#include "GamePieceShape.hpp"
#include <SFML/Graphics/Color.hpp>

class EventData {
public:
	EventData(EventType event)
	: m_timestamp(std::chrono::system_clock::now()),
	  m_event(event),
	  m_gamePieceShape(GamePieceShape::LINE),
	  m_gamePieceColor(sf::Color::Black){
	}

	EventData(EventType event, GamePieceShape shape, sf::Color color)
	: m_timestamp(std::chrono::system_clock::now()),
	  m_event(event),
	  m_gamePieceShape(shape),
	  m_gamePieceColor(color) {
	}

	inline std::chrono::time_point<std::chrono::system_clock> timestamp() const {
		return m_timestamp;
	}

	inline EventType event() const {
		return m_event;
	}

	inline GamePieceShape gamePieceShape() const {
		return m_gamePieceShape;
	}

	inline sf::Color gamePieceColor() const {
		return m_gamePieceColor;
	}

private:
	const std::chrono::time_point<std::chrono::system_clock>	m_timestamp;
	const EventType												m_event;
	const GamePieceShape										m_gamePieceShape;
	const sf::Color												m_gamePieceColor;
};

typedef std::shared_ptr<EventData> EventDataPointer;
