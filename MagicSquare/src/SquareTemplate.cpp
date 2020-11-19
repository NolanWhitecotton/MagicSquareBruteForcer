#include "MagicSquareBruteForcer.h"

SquareTemplate::SquareTemplate(bool isCompact, int squareSize, int reucrMin, int recurMax, bool showIdentical) {
	m_isCompact = isCompact;
	m_squareSize = squareSize;
	m_showIdentical = showIdentical;

	//calculate max and offset
	m_recurMax = recurMax - reucrMin + 1;
	m_recurOffset = reucrMin;
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

int SquareTemplate::convert2dtoLinear(int r, int c) { return r * getSquareSize() + c; }
int SquareTemplate::getLinearR(int pos) { return pos / getSquareSize(); }
int SquareTemplate::getLinearC(int pos) { return pos % getSquareSize(); }
