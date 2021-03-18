#include "SquareTemplate.h"
#include <iostream>//cout

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
	//TODO (DI) create instertion/checking orders
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
