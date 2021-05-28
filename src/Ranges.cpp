#include "Ranges.h"
#include "Square.h"

int FullRange::getMin(const Square* sq) const {return m_min;}
int FullRange::getMax(const Square* sq) const {return m_max;}

int LineSumRange::getMin(const Square* sq) const {
	return getMax(sq);
}

int LineSumRange::getMax(const Square* sq) const {
	return sq->getLineSumCache() - sq->getLineSum(m_dir, m_pos);
}
