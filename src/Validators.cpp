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

bool LineSumValidator::run(const Square* sq) const {
	return sq->getLineSum(m_type, m_num) == sq->getLineSumCache();
}

bool CachePossibleValidator::run(const Square* sq) const {
    return (
        sq->getLineSumCache() > sq->getTemplate()->getMinPosSum() &&
        sq->getLineSumCache() < sq->getTemplate()->getMaxPosSum()
    );
}

#include <iostream>//cout
bool RangeValidator::run(const Square* sq) const {
    int num = sq->getNum(m_pos);
	bool output = (num >= m_min && num <= m_max);
	return output;
}
