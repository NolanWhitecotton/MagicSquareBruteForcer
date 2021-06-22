#pragma once
#include <vector>
#include <mutex>
struct Args;
class Validator;
class Square;
class Range;

class SquareTemplate {
private:
    std::vector<int> nums; //the number of times that theoretical sums can occur given the range
    std::vector<std::vector<Validator*>> validators; //the list of tests to run to see if a magic square is possible
    std::vector<Range*> ranges; //the list of ranges to iterate through

    std::mutex m_outputMutex; //mutex for cout

    int m_squareSize=0;//the length of the square
    int m_recurMax=0;//the maximum number toa add to the square
    int m_recurOffset=0;//the offset from 0 that the final square will display
    int minPosSum=0;//the minimum possible linesum cache that can make a valid square
    int maxPosSum=0;//the maxium possible lineum cache that can make a valid square
    int cacheIndex=0;//the count of numbers added after which the linesumcache will be calculated

    bool m_isCompact=false;
    bool m_showIdentical=true;

    void findRangeRecur_helper(int min, int count, int maxSize, int maxNum, int sum);
    void findRangeRecur(int min, int size);
    void findPossibleRanges(int size, int max);
    void generateValidators();
    void generateRanges();

public:
    //constructors
    SquareTemplate(Args& a);
    ~SquareTemplate();
    
    bool doTests(const Square* sq) const;//run validators on a square

    //getters
    bool getIsCompact() const { return m_isCompact; }
    int getSquareSize() const { return m_squareSize; }
    int getSquareArea() const { return m_squareSize * m_squareSize; } //TODO cache square area?
    int getRecurMax() const { return m_recurMax; }
    int getRecurOffset() const {return m_recurOffset;}
    bool getShowIdentical() const { return m_showIdentical; }
    int getMinPosSum() const { return minPosSum; }
    int getMaxPosSum() const { return maxPosSum; }
    std::mutex& getOutputMutex() { return m_outputMutex; }
    int getMinRange(int pos, const Square* square);
    int getMaxRange(int pos, const Square* square);
    int getCacheIndex() { return cacheIndex; }

    //methods
    int convert2dtoLinear(int r, int c) { return r * getSquareSize() + c; }
    int getLinearR(int pos) { return pos / getSquareSize(); }
    int getLinearC(int pos) { return pos % getSquareSize(); }
};
