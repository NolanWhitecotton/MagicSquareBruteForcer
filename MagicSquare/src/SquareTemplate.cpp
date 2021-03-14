#include "MagicSquareBruteForcer.h"

SquareTemplate::SquareTemplate(Args *a) {
	m_isCompact = a->compactOutput;
	m_squareSize = a->size;
	m_showIdentical = a->outputIdentical;

	//calculate max and offset
	m_recurMax = a->max - a->min + 1;
	m_recurOffset = a->min;

	//create mutex
	m_outputMutex = new std::mutex();

	//compile the ranges
	findPossibleRanges(m_squareSize, m_recurMax);
	//TODO (DI) create order
}

bool SquareTemplate::getIsCompact() const { return m_isCompact; }
int  SquareTemplate::getSquareSize() const { return m_squareSize; }
int SquareTemplate::getRecurMax() const { return m_recurMax; }
int SquareTemplate::getRecurOffset() const { return m_recurOffset; }
bool SquareTemplate::getShowIdentical() const { return m_showIdentical; }

//void ThreadManager::createTemplate(bool isCompact, int squareSize, int recurMin, int recurMax, bool showIdentical) {
void ThreadManager::createTemplate(Args *a) {
	tmplt = new SquareTemplate(a);
}

void ThreadManager::startCheckThreaded(Args *a) {
	//prep operations to run on threads
	std::vector<std::thread> threadList;
	std::stack<Square*> s;

	//prep work to be done
	for(int i = tmplt->getRecurMax(); i > 0; i--) {//backwards so single threaded will be in order
		Square* newS = new Square(tmplt->getSquareSize(), tmplt);
		newS->add(i);
		s.push(newS);
	}

	//create threads
	for (int i = 0; i < a->threadCount; i++) {
		if (s.empty()) {
			break;
		}

		Square* sq = s.top();
		s.pop();

		threadList.emplace_back(
			[sq]() {
				sq->checkNextRecur();
			}
		);
	}

	//if a thread is empty, delete it an add a new thread
	//TODO budding if the thread queue is empty
	while (!s.empty()) {
		for (int i = 0; i < threadList.size(); i++) {//for every thread
			if (threadList[i].joinable()) {//if thread is joinable
				//delete thread
				threadList[i].join();
				threadList.erase(threadList.begin()+i);

				//get job to do
				Square* sq = s.top();
				s.pop();

				//add to new thread
				threadList.emplace_back(
					[sq]() {
						sq->checkNextRecur();
					}
				);

				tmplt->getOutputMutex()->lock();
				std::cout << "Starting new thread " << s.size() << " jobs left to do." << std::endl;
				tmplt->getOutputMutex()->unlock();

				//break for loop since threadList and s have been modified
				break;
			}
		}
	}

	//join all threads
	for (auto& t : threadList){
		t.join();
	}
}

ThreadManager::ThreadManager(Args *a){
	createTemplate(a);
	startCheckThreaded(a);
}

int SquareTemplate::convert2dtoLinear(int r, int c) { return r * getSquareSize() + c; }
int SquareTemplate::getLinearR(int pos) { return pos / getSquareSize(); }
int SquareTemplate::getLinearC(int pos) { return pos % getSquareSize(); }

std::mutex* SquareTemplate::getOutputMutex() {
	return m_outputMutex;
}

SquareTemplate::~SquareTemplate() {
	delete m_outputMutex;
}

void SquareTemplate::findPossibleRanges(int size, int max) {
	//add nums to vector
	for(int i=0; i<=max+max-1+max-2; i++){
		nums.push_back(0);
	}

	//recur
	findRangeRecur(1,0,size,max,0);

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
		} else {
			if (start && !end) {
				maxPosSum=i-1;
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
	std::cout << "Row Line Sum range = ["<<minPosSum << ", " << maxPosSum << "]"<< std::endl;
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
