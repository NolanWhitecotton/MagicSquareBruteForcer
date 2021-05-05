#pragma once
#include "Square.h"

//a validator is an object that can be run on a given square to test if it meets specific requirements
class Validator{
public:
	virtual bool run(const Square* sq)  = 0;
};

//validator to check that the specified position is unique within a square
class UniquenessValidator: public Validator {
private:
	int numPos;

public:
	UniquenessValidator(int position) : numPos(position) {}

	bool run(const Square* sq) {
		for (int i = 0; i < numPos - 1; i++) {
			if (sq->getNum(i) == sq->getNum(numPos - 1)) {
				return false;
			}
		}
		return true;
	}
};

//validator to check that a number is less than another, for mirror minimizations
class MirrorValidator : public Validator {
private:
	int msmaller, mlarger;

public:
	MirrorValidator(int smallerPos, int biggerPos, int position) : msmaller(smallerPos), mlarger(biggerPos) {}

	bool run(const Square* sq) {
		return (sq->getNum(msmaller) < sq->getNum(mlarger));
	}
};

//validator to check that a linesum is equal to the cache
class LineSumValidator : public Validator {
public:
	//TODO specifiy which line to sum, use an enum and an int to define them, then only check that one
};

//validator to check that the cache is within the possible range
class CachePossibleValidator : public Validator {
public:
	//TODO check if the linesum cache is between the posSums
};
