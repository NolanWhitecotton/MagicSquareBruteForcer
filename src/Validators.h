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

//the types of lines the square checks
enum class LineType {
	Row,
	Column,
	PositiveDiagonal,
	NegativeDiagonal
};

//validator to check that a linesum is equal to the cache
class LineSumValidator : public Validator {
private:
	LineType m_type;
	int m_num = 0;

	int getLineSum(const Square* sq, LineType type, int num) const;

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
	int m_max, m_min;
	int m_pos;

public:
	RangeValidator(int max, int min, int pos) : m_max(max), m_min(min), m_pos(pos) {}

	bool run(const Square* sq) const override;
};
