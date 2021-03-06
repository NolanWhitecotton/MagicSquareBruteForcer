#pragma once
#include "Square.h"

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
private:
	LineType m_type;
	int m_num = 0;

public:
	LineSumValidator(LineType type, int num) : m_type(type), m_num(num) {}

	bool run(const Square* sq) const override;
};

//validator to check that the cache is within the possible range
class CachePossibleValidator : public Validator {
public:
	CachePossibleValidator() {}

	bool run(const Square* sq) const override;
};

//calidator to check if a number is within the max and min range
class RangeValidator : public Validator {
private:
	int m_min=0, m_max=0;
	int m_pos=0;

public:
	RangeValidator(int min, int max, int pos) : m_min(min), m_max(max), m_pos(pos) {}

	bool run(const Square* sq) const override;
};
