#pragma once
class Square;

class Range {
public:
	virtual int getMin(const Square* sq) const = 0;
	virtual int getMax(const Square* sq) const = 0;
	virtual ~Range() {};
};

//give the entire range, ignores the square argument
class FullRange : public Range {
private:
	int m_min=0, m_max=0;

public:
	int getMin(const Square* sq) const override;
	int getMax(const Square* sq) const override;
};

//get the exact number to complete a linesum given a cache
//TODO this needs linesum enum and method
class LineSumRange : public Range {
private:
	
};
