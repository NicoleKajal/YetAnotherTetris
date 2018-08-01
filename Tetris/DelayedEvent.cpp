#include "stdafx.h"
#include "DelayedEvent.hpp"

/**
 * Create a delayed Event object, which will create a thread that will sleep for the amount of
 * time specified for the delay, send the event after the delay time has elapsed, and the tear
 * itself down (delete itself).
 *
 * @param gameManager	Receiver of the delayed event
 * @param event         Delay event to be sent
 * @param delayTime     Number of millisecond to delay before sending the event
 **/
DelayedEvent::DelayedEvent(GameManager& gameManager, EventType event, int delayTime)
  : m_gameManager(gameManager),
	m_event(event),
	m_delayTime(delayTime),
	m_thread(&DelayedEvent::delayedEventDelivery, this) {
}

/**
 * Delays the sending of an event to the EventHandler.
 **/
void DelayedEvent::delayedEventDelivery() {
	// Delay sending the event for the specified amount of time and then send it.
	std::this_thread::sleep_for(std::chrono::milliseconds(m_delayTime));
	m_gameManager.addEvent(m_event);
}