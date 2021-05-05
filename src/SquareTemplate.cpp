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
	generateValidators();

	//TODO (DI) create instertion/checking orders
}

//create and add all validators to the validator list
void SquareTemplate::generateValidators() {
	validators.resize((size_t)m_squareSize*m_squareSize);//resize vector to square size

	//add uniqueness validators
	for (int i = 0; i < m_squareSize * m_squareSize; i++) {//for every square position
		validators[i].push_back(new UniquenessValidator(i));//TODO deconstruct
	}

	int pos;
	//insert corner mirrors
	//TODO test these placements on higher order squares
	//top right
	pos = convert2dtoLinear(0, getSquareSize()) - 1;
	validators[pos].push_back(new MirrorValidator(0, pos));//TODO deconstruct
	//bottom left
	pos = convert2dtoLinear(getSquareSize() - 1, 0);
	validators[pos].push_back(new MirrorValidator(0, pos));//TODO deconstruct
	//bottom right
	pos = convert2dtoLinear(getSquareSize() - 1, getSquareSize() - 1);
	validators[pos].push_back(new MirrorValidator(0, pos));//TODO deconstruct

	//insert negitive diag mirror
	pos = convert2dtoLinear(0, 1);
	int pos2 = convert2dtoLinear(1, 0);
	validators[pos2].push_back(new MirrorValidator(pos, pos2));

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
