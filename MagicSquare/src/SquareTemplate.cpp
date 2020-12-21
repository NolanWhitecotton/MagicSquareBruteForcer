#include "MagicSquareBruteForcer.h"
#include <stack>


SquareTemplate::SquareTemplate(bool isCompact, int squareSize, int reucrMin, int recurMax, bool showIdentical) {
	m_isCompact = isCompact;
	m_squareSize = squareSize;
	m_showIdentical = showIdentical;

	//calculate max and offset
	m_recurMax = recurMax - reucrMin + 1;
	m_recurOffset = reucrMin;

	//create mutex
	m_outputMutex = new std::mutex();
}

bool SquareTemplate::getIsCompact() const { return m_isCompact; }
int  SquareTemplate::getSquareSize() const { return m_squareSize; }
int SquareTemplate::getRecurMax() const { return m_recurMax; }
int SquareTemplate::getRecurOffset() const { return m_recurOffset; }
bool SquareTemplate::getShowIdentical() const { return m_showIdentical; }

void SquareTemplate::startCheckThreaded(int threadCount) {
	//prep operations to run on threads
	std::vector<std::thread> threadList;
	std::stack<Square*> s;

	//prep work to be done
	for(int i = getRecurMax(); i > 0; i--) {//backwards so single threaded will be in order
		Square* newS = new Square(getSquareSize(), &*this);
		newS->add(i);
		s.push(newS);
	}

	//create threads
	for (int i = 0; i < threadCount; i++) {
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

				//add new thread
				Square* sq = s.top();
				s.pop();

				threadList.emplace_back(
					[sq]() {
						sq->checkNextRecur();
					}
				);

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

int SquareTemplate::convert2dtoLinear(int r, int c) { return r * getSquareSize() + c; }
int SquareTemplate::getLinearR(int pos) { return pos / getSquareSize(); }
int SquareTemplate::getLinearC(int pos) { return pos % getSquareSize(); }

std::mutex* SquareTemplate::getOutputMutex() {
	return m_outputMutex;
}

SquareTemplate::~SquareTemplate() {
	delete m_outputMutex;
}
