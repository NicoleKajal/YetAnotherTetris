#pragma once
#include <thread>
#include "EventType.hpp"
#include "GameManager.hpp"

class DelayedEvent {
public:
	DelayedEvent(GameManager& eventHandler, EventType event, int delayTime);

private:
	void delayedEventDelivery();

	GameManager&  m_gameManager;
	EventType     m_event;
	int           m_delayTime;
	std::thread   m_thread;
};
