#include "ThreadManager.h"

void ThreadManager::createTemplate(Args* a) {
	tmplt = new SquareTemplate(a);
}

void ThreadManager::startCheckThreaded(Args* a) {
	//prep operations to run on threads
	std::vector<std::thread> threadList;
	std::stack<Square*> s;
	std::mutex* stackmutex = new std::mutex();

	//queue work to be done
	for (int i = tmplt->getRecurMax(); i > 0; i--) {//backwards so single threaded will be in order
		Square* newS = new Square(tmplt->getSquareSize(), tmplt);
		newS->add(i);
		s.push(newS);
	}

	//create threads
	for (int i = 0; i < a->threadCount; i++) {
		if (s.empty()) {//check that there arent more threads than queue length
			break;
		}

		threadList.emplace_back(
			[&s, &stackmutex]() {
				//grab from the queue and calculate it until queue is empty
				stackmutex->lock();
				while (!s.empty()) {
					Square* sq = s.top();
					s.pop();
					stackmutex->unlock();

					sq->checkNextRecur();
					delete sq;

					stackmutex->lock();
				}
				stackmutex->unlock();
			}
		);
	}

	//join all threads
	for (auto& t : threadList) {
		if (t.joinable())
			t.join();
	}
}

ThreadManager::ThreadManager(Args* a) {
	createTemplate(a);
	startCheckThreaded(a);
}

SquareTemplate::~SquareTemplate() {
	delete m_outputMutex;
}

void SquareTemplate::findPossibleRanges(int size, int max) {
	//add nums to vector
	for (int i = 0; i <= max + max - 1 + max - 2; i++) {
		nums.push_back(0);
	}

	//recur
	findRangeRecur(1, 0, size, max, 0);

	//calculate the valid ranges
	bool start = false;
	bool end = false;
	for (int i = 0; i < nums.size(); i++) {
		//std::cout << i << ": " << nums[i] << std::endl;
		if (nums[i] >= (m_squareSize * 2 + 2)) {
			if (!start) {
				minPosSum = i;
				start = true;
			}
		}
		else {
			if (start && !end) {
				maxPosSum = i - 1;
				end = true;
			}
		}
	}

	//edge cases
	if (!end) {
		maxPosSum = (int)nums.size() - 1;
	}
	if (!start) {
		std::cout << "There are no possible squares given this range." << std::endl;
	}

	//print the valid range
	std::cout << "Row Line Sum range = [" << minPosSum << ", " << maxPosSum << "]" << std::endl;
}

void SquareTemplate::findRangeRecur(int min, int count, int maxSize, int maxNum, int sum) {
	if (count >= maxSize) {
		nums[sum]++;
		return;
	}
	for (int i = min; i < maxNum; i++) {
		findRangeRecur(i, count + 1, maxSize, maxNum, sum + i);
	}
}
