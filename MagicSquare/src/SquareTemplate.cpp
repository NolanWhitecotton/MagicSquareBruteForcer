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

void SquareTemplate::startCheck() {//TODO (MI) multiple numbers can be instered at the same time if their sum is known to equal the square cache
	Square sq = Square(getSquareSize(), &*this);
	sq.checkNextRecur();
}

void SquareTemplate::startCheckThreaded() {
	std::vector<std::thread> threadList;

	//prep threaded operations
	//std::stack<> s;

	//create threads
	for (int i = 1; i <= getRecurMax(); i++) {//TODO allow variable amout of threads specificed in args
		threadList.emplace_back([this, i]() {
			Square sq = Square(getSquareSize(), &*this);
			sq.add(i);
			sq.checkNextRecur();
		});
	}

	//check that minimal number of thereads are parked
	bool done = false;
	while (!done) {
		done = true;
		for (int i = 0; i < threadList.size(); i++) {
			if (!threadList[i].joinable()) {
				done = false;
				break;
			}
		}
		

	}

	//join threads
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
