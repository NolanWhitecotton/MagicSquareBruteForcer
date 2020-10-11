#include "MagicSquareBruteForcer.h"

SquareTemplate::SquareTemplate(bool isCompact, int squareSize, int reucrMin, int recurMax, bool showIdentical) {
	this->isCompact = isCompact;
	this->squareSize = squareSize;
	this->showIdentical = showIdentical;

	//calculate max and offset
	this->recurMax = recurMax - reucrMin + 1;
	recurOffset = reucrMin;
}

bool SquareTemplate::getIsCompact() const { return isCompact; }
int  SquareTemplate::getSquareSize() const { return squareSize; }
int SquareTemplate::getRecurMax() const { return recurMax; }
int SquareTemplate::getRecurOffset() const { return recurOffset; }
bool SquareTemplate::getShowIdentical() const { return showIdentical; }

void SquareTemplate::startCheck() {//TODO (MI) multiple numbers can be instered at the same time if their sum is known to equal the square cache
	Square sq = Square(getSquareSize(), &*this);
	sq.checkNextRecur();
}

int SquareTemplate::convert2dtoLinear(int r, int c) { return r * getSquareSize() + c; }
int SquareTemplate::getLinearR(int pos) { return pos / getSquareSize(); }
int SquareTemplate::getLinearC(int pos) { return pos % getSquareSize(); }
