#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <stack>

class SquareTemplate {
private:
    bool m_isCompact;
    int m_squareSize;
    int m_recurMax;
    int m_recurOffset;
    bool m_showIdentical;

    std::mutex* m_outputMutex;

    int minPosSum;
    int maxPosSum;

    std::vector<int> nums;
    void findRangeRecur(int min, int count, int maxSize, int maxNum, int sum);
    void findPossibleRanges(int size, int max);

public:
    //constructors
    SquareTemplate(Args *a);
    ~SquareTemplate();

    //getters
    bool getIsCompact() const { return m_isCompact; }
    int  getSquareSize() const { return m_squareSize; }
    int getRecurMax() const { return m_recurMax; }
    int getRecurOffset() const {return m_recurOffset;}
    bool getShowIdentical() const { return m_showIdentical; }
    int getMinPosSum() const { return minPosSum; }
    int getMaxPosSum() const { return maxPosSum; }
    std::mutex* getOutputMutex() { return m_outputMutex; }

    //methods
    int convert2dtoLinear(int r, int c) { return r * getSquareSize() + c; }
    int getLinearR(int pos) { return pos / getSquareSize(); }
    int getLinearC(int pos) { return pos % getSquareSize(); }
};


class ThreadManager {
private:
    SquareTemplate* tmplt;

    void createTemplate(Args* a);
    void startCheckThreaded(Args* a);

public:
    ThreadManager(Args* a);
};
