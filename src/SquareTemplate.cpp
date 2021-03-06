#include "SquareTemplate.h"
#include "Args.h"
#include "Validators.h"
#include "Ranges.h"
#include "Square.h"
#include <iostream>//cout

//calculates a normalized max given a max and a min, assume min is the offset
int CalcMaxWithOffset(int max, int min) { return max - min + 1; }

SquareTemplate::SquareTemplate(Args& a)
	: m_isCompact(a.compactOutput), m_squareSize(a.size), m_showIdentical(a.outputIdentical),
	m_recurMax(CalcMaxWithOffset(a.max, a.min)), m_recurOffset(a.min)
{
	//generate metadata about the square
	findPossibleRanges(m_squareSize, m_recurMax);
	generateRanges();
	generateValidators();
	cacheIndex = getSquareSize();

	//TODO (DI) create dynamic instertion/checking orders
}

//generate and add all ranges to the range list
void SquareTemplate::generateRanges()
{
	ranges.resize((size_t)m_squareSize * m_squareSize);

	//insert fullRanges
	//inner square
	for (int r = 0; r < m_squareSize - 1; r++) {
		for (int c = 0; c < m_squareSize - 1; c++) {
			ranges[convert2dtoLinear(r, c)] = (new FullRange(1, m_recurMax));
		}
	}
	//end first row
	ranges[convert2dtoLinear(0, m_squareSize - 1)] = (new FullRange(1, m_recurMax));

	//insert LineSums
	for (int i = 1; i < m_squareSize - 1; i++) {//the -1 in m_squareSize is because it is going to get overwritten the cols
		ranges[convert2dtoLinear(i, m_squareSize - 1)] = (new LineSumRange(LineType::Row, i));
	}
	for (int i = 0; i < m_squareSize; i++) {
		ranges[convert2dtoLinear(m_squareSize - 1, i)] = (new LineSumRange(LineType::Column, i));
	}
}

//create and add all validators to the validator list
void SquareTemplate::generateValidators()
{
	validators.resize((size_t)m_squareSize * m_squareSize);//resize vector to square size

	//add uniqueness validators
	for (int i = 0; i < m_squareSize * m_squareSize; i++) {//for every square position
		validators[i].push_back(new UniquenessValidator(i));
	}

	//insert mirror validators
	int pos1 = 0, pos2 = 0;
	//top right
	pos2 = convert2dtoLinear(0, getSquareSize()) - 1;
	validators[pos2].push_back(new MirrorValidator(0, pos2));
	//bottom left
	pos2 = convert2dtoLinear(getSquareSize() - 1, 0);
	validators[pos2].push_back(new MirrorValidator(0, pos2));
	//bottom right
	pos2 = convert2dtoLinear(getSquareSize() - 1, getSquareSize() - 1);
	validators[pos2].push_back(new MirrorValidator(0, pos2));
	//negitive diag mirror
	pos1 = convert2dtoLinear(0, 1);
	pos2 = convert2dtoLinear(1, 0);
	validators[pos2].push_back(new MirrorValidator(pos1, pos2));

	//insert linesum validators
	for (int i = 0; i < getSquareSize(); i++) {
		//insert row validator
		validators[convert2dtoLinear(i, getSquareSize() - 1)].push_back(new LineSumValidator(LineType::Row, i));

		//insert col validator
		validators[convert2dtoLinear(getSquareSize() - 1, i)].push_back(new LineSumValidator(LineType::Column, i));
	}

	//insert negative diag validator
	validators[convert2dtoLinear(getSquareSize() - 1, getSquareSize() - 1)].push_back(new LineSumValidator(LineType::NegativeDiagonal, 0));

	//insert positive diag validator
	validators[convert2dtoLinear(getSquareSize() - 1, 0)].push_back(new LineSumValidator(LineType::PositiveDiagonal, 0));

	//insert CachePossibleValidator
	validators[convert2dtoLinear(0, getSquareSize() - 1)].push_back(new CachePossibleValidator());

	//insert rangeValidators
	for (int i = 1; i < m_squareSize - 1; i++) {//the -1 in m_squareSize is because it is going to get overwritten the cols
		pos1 = convert2dtoLinear(i, m_squareSize - 1);
		validators[pos1].push_back(new RangeValidator(1, m_recurMax, pos1));
	}
	for (int i = 0; i < m_squareSize; i++) {
		pos1 = convert2dtoLinear(m_squareSize - 1, i);
		validators[pos1].push_back(new RangeValidator(1, m_recurMax, pos1));
	}
}

int SquareTemplate::getMinRange(int pos, const Square* square)
{
	return ranges.at(pos)->getMin(square);
}

int SquareTemplate::getMaxRange(int pos, const Square* square)
{
	return ranges.at(pos)->getMax(square);
}

SquareTemplate::~SquareTemplate()
{
	//delete validators
	for (auto vlist : validators) {
		for (auto v : vlist) {
			delete v;
		}
	}

	//delete ranges
	for (auto r : ranges) {
		delete r;
	}
}

void SquareTemplate::findPossibleRanges(int size, int max)
{
	//add nums to vector
	for (int i = 0; i <= max * size; i++) {
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
	for (size_t i = nums.size() - 1; i > minPosSum; i--) {
		if (nums[i] >= neededSums) {
			maxPosSum = (int)i;
			break;
		}
	}

	//print the valid range
	std::cout << "Row Line Sum range = [" << minPosSum << ", " << maxPosSum << "]" << std::endl;
}

//recursively finds the number of ways to get to every line ending for the given size and max
void SquareTemplate::findRangeRecur(int size, int max)
{
	findRangeRecur_helper(1, 0, size, max, 0);
}

//The helper function of findRangeRecur that handles passing the metadata
void SquareTemplate::findRangeRecur_helper(int min, int count, int maxSize, int maxNum, int sum)
{
	if (count >= maxSize) { //if size reached
		nums.at(sum)++;
	} else {
		for (int i = min; i < maxNum; i++) {
			findRangeRecur_helper(i, count + 1, maxSize, maxNum, sum + i);
		}
	}
}

bool SquareTemplate::doTests(const Square* sq) const
{
	//run all nessacary validators
	auto& list = (sq->getTemplate().validators.at((size_t)sq->getAddedNumCount() - 1));//get the validators for the just added pos
	for (Validator* val : list) {//for every applicable validator
		if (!val->run(sq)) {//run it
			return false;
		}
	}

	return true;
}
