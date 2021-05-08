#include "ThreadManager.h"
#include "SquareTemplate.h"
#include "Square.h"
#include "Args.h"
#include <mutex>
#include <stack>
#include <thread>

void ThreadManager::createTemplate(Args& a) {
	tmplt = new SquareTemplate(a);
}

void ThreadManager::startCheckThreaded(Args& a) {
	//prep operations to run on threads
	std::vector<std::thread> threadList;
	std::stack<Square*> s;
	std::mutex stackmutex;

	//queue work to be done
	for (int i = tmplt->getRecurMax(); i > 0; i--) {//backwards so single threaded will be in order
		Square* newS = new Square(tmplt->getSquareSize(), tmplt);
		newS->add(i);
		if (tmplt->doTests(newS)) {
			s.push(newS);
		} else {
			delete newS;
		}
	}

	//create threads
	for (int i = 0; i < a.threadCount; i++) {
		if (s.empty()) {//check that there arent more threads than queue length
			break;
		}

		threadList.emplace_back(
			[&s, &stackmutex]() {
				//grab from the queue and calculate it until queue is empty
				stackmutex.lock();
				while (!s.empty()) {
					Square* sq = s.top();
					s.pop();
					stackmutex.unlock();

					sq->checkNextRecur();
					delete sq;

					stackmutex.lock();
				}
				stackmutex.unlock();
			}
		);
	}

	//join all threads
	for (auto& t : threadList) {
		if (t.joinable())
			t.join();
	}
}

ThreadManager::ThreadManager(Args& a) {
	createTemplate(a);
	startCheckThreaded(a);
}
