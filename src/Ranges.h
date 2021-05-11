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
	FullRange(int min, int max) : m_min(min), m_max(max) {}

	int getMin(const Square* sq) const override;
	int getMax(const Square* sq) const override;
};

//get the exact number to complete a linesum given a cache
class LineSumRange : public Range {
private:
	LineType m_dir;
	int m_pos = 0;

public:
	LineSumRange(LineType dir, int pos) : m_dir(dir), m_pos(pos) {}

	int getMin(const Square* sq) const override;
	int getMax(const Square* sq) const override;
};
