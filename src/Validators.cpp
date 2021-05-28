#include "Validators.h"
#include "Square.h"
#include "SquareTemplate.h"

bool UniquenessValidator::run(const Square* sq) const {
	for (int i = 0; i < numPos; i++) {
		if (sq->getNum(i) == sq->getNum(numPos)) {
			return false;
		}
	}
	return true;
}

bool MirrorValidator::run(const Square* sq) const {
	return (sq->getNum(msmaller) < sq->getNum(mlarger));
}

int LineSumValidator::getLineSum(const Square* sq, LineType type, int num) const {
    int sum = 0;//the current linesum
    int incAmt = 1;//the amount of increment by
    int pos = 0;//the current position

    //calculate pos and inc ammount for the given bools
    //forwards
    switch (type) {
    case LineType::PositiveDiagonal:
        pos = sq->getTemplate().getSquareSize() - 1;
        incAmt = sq->getTemplate().getSquareSize() - 1;
        break;
    case LineType::NegativeDiagonal:
        pos = 0;
        incAmt = sq->getTemplate().getSquareSize() + 1;
        break;
    case LineType::Row:
        pos = num * sq->getTemplate().getSquareSize();
        incAmt = 1;
        break;
    case LineType::Column:
        pos = num;
        incAmt = sq->getTemplate().getSquareSize();
        break;
    default:
        return -1;
        break;
    }

    //calculate sum
    for (int goal = pos + sq->getTemplate().getSquareSize() * incAmt; pos != goal; pos += incAmt) {
        sum += sq->getNum(pos);
    }

    return sum;
}

bool LineSumValidator::run(const Square* sq) const {
	return sq->getLineSum(m_type, m_num) == sq->getLineSumCache();
}

bool CachePossibleValidator::run(const Square* sq) const {
    return (
        sq->getLineSumCache() > sq->getTemplate().getMinPosSum() &&
        sq->getLineSumCache() < sq->getTemplate().getMaxPosSum()
    );
}

#include <iostream>//cout
bool RangeValidator::run(const Square* sq) const {
    int num = sq->getNum(m_pos);
	bool output = (num >= m_min && num <= m_max);
	return output;
}
