#pragma once
class Square;

//a validator is an object that can be run on a given square to test if it meets specific requirements
class Validator{
public:
	virtual bool run(const Square* sq) const = 0;
	virtual ~Validator() {};
};

//validator to check that the specified position is unique within a square
class UniquenessValidator: public Validator {
private:
	int numPos = 0;

public:
	UniquenessValidator(int position) : numPos(position) {}

	bool run(const Square* sq) const override;
};

//validator to check that a number is less than another, for mirror minimizations
class MirrorValidator : public Validator {
private:
	int msmaller=0, mlarger=0;

public:
	MirrorValidator(int smallerPos, int biggerPos) : msmaller(smallerPos), mlarger(biggerPos) {}

	bool run(const Square* sq) const override;
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
