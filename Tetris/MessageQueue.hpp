#pragma once

#include <list>
#include <mutex>
#include <condition_variable>

template<class MessageType>
class MessageQueue {
public:
	MessageQueue()
	: m_mutex(), m_notifier(), m_queue() {
	}

	void add(MessageType message) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push_back(message);
		m_notifier.notify_one();
	}

	MessageType remove() {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_notifier.wait(lock, [this] {return !m_queue.empty();});
		MessageType message = m_queue.front();
		m_queue.pop_front();
		return message;
	}

private:
	std::mutex              m_mutex;
	std::condition_variable m_notifier;
	std::list<MessageType>  m_queue;
};