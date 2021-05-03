#pragma once
#include "Square.h"

class Validator{
	virtual bool run(Square& sq) = 0;
};

class UniquenessValidator: public Validator {
	int numPos;
	//TODO specifiy which add to check then only check that one on run
	UniquenessValidator(int position) : numPos(position) {}

	bool run(Square& sq) {
		for (int i = 0; i < numPos - 1; i++) {
			if (sq.getNum(i) == sq.getNum(numPos - 1)) {
				return false;
			}
		}
		return true;
	}
};


class MirrorValidator : public Validator {
	int msmaller, mlarger;

	MirrorValidator(int smallerPos, int biggerPos) : msmaller(smallerPos), mlarger(biggerPos) {}

	bool run(Square& sq) {
		
	}
	//TODO specifiy which locations to compare to do in constructor, then only check that on run
};

class LineSumValidator : public Validator {
	//TODO specifiy which line to sum, use an enum and an int to define them, then only check that one
};

class CachePossibleValidator : public Validator {
	//TODO check if the linesum cache is between the posSums
};
