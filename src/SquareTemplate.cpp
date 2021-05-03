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
	for (int i = 0; i <= max*size; i++) {
		nums.push_back(0);
	}

	//recur
	findRangeRecur(size, max);

	int neededSums = m_squareSize * 2 + 2;//rows, cols, two diags
	//calc minPosSum
	int found = false;
	for (int i = 0; i < (int)nums.size(); i++) {
		if (nums[i] >= neededSums) {
			minPosSum = i;
			found = true;
			break;
		}
	}
	if (!found) {
		std::cout << "There are no possible squares given this range." << std::endl;
		exit(EXIT_FAILURE);
	}

	//cal maxPosSum
	maxPosSum = (int)nums.size() - 1;
	for (size_t i = nums.size()-1; i > minPosSum; i--) {
		if (nums[i] >= neededSums) {
			maxPosSum = (int)i;
			break;
		}
	}

	//print the valid range
	std::cout << "Row Line Sum range = [" << minPosSum << ", " << maxPosSum << "]" << std::endl;
}

//recursively finds the number of ways to get to every line ending for the given size and max
void SquareTemplate::findRangeRecur(int size, int max) {
	findRangeRecur_helper(1, 0, size, max, 0);
}

//The helper function of findRangeRecur that handles passing the metadata
void SquareTemplate::findRangeRecur_helper(int min, int count, int maxSize, int maxNum, int sum) {
	if (count >= maxSize) { //if size reached
		nums.at(sum)++;
	} else {
		for (int i = min; i < maxNum; i++) {
			findRangeRecur_helper(i, count + 1, maxSize, maxNum, sum + i);
		}
	}
}
