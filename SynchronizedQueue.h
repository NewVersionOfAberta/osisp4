#pragma once

#include <Windows.h>
#include <queue>

#define SYNCHRONIZED_QUEUE_SPINCOUNT 1024

template <typename T>
class SynchronizedQueue
{
public:
	SynchronizedQueue() {
		InitializeCriticalSectionAndSpinCount(&m_criticalSection, SYNCHRONIZED_QUEUE_SPINCOUNT);
	}

	~SynchronizedQueue() {
		DeleteCriticalSection(&m_criticalSection);
	}

	void push(T element) {
		EnterCriticalSection(&m_criticalSection);

		m_quque.push(element);

		LeaveCriticalSection(&m_criticalSection);
	}

	T pop() {
		T element;

		EnterCriticalSection(&m_criticalSection);

		if (m_quque.empty()) {
			element = {};
		}
		else {
			element = m_quque.front();
			m_quque.pop();
		}

		LeaveCriticalSection(&m_criticalSection);

		return element;
	}
private:
	CRITICAL_SECTION m_criticalSection;
	std::queue<T> m_quque;
};