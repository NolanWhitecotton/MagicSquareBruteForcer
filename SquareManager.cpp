#include "MagicSquareHeader.h"

SquareManager::SquareManager(bool isCompact, int squareSize, int reucrMin, int recurMax, bool showIdentical) {
	this->isCompact = isCompact;
	this->squareSize = squareSize;
	this->showIdentical = showIdentical;

	//calculate max and offset
	this->recurMax = recurMax - reucrMin + 1;
	this->recurOffset = reucrMin;
}

bool SquareManager::getIsCompact() const { return this->isCompact; }
int  SquareManager::getSquareSize() const { return this->squareSize; }
int SquareManager::getRecurMax() const { return this->recurMax; }
int SquareManager::getRecurOffset() const { return this->recurOffset; }
bool SquareManager::getShowIdentical() const { return this->showIdentical; }

void SquareManager::startCheck() {//TODO (MI) multiple numbers can be instered at the same time if their sum is known to equal the square cache
	Square sq = Square(this->getSquareSize(), &*this);
	sq.checkNextRecur();
}

