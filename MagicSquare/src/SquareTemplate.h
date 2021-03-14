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
    bool getIsCompact() const;
    int  getSquareSize() const;
    int getRecurMax() const;
    int getRecurOffset() const;
    bool getShowIdentical() const;

    //methods
    int convert2dtoLinear(int r, int c);
    int getLinearR(int pos);
    int getLinearC(int pos);
    int getMinPosSum() const { return minPosSum; }
    int getMaxPosSum() const { return maxPosSum; }

    std::mutex* getOutputMutex();
};


class ThreadManager {
private:
    SquareTemplate* tmplt;

    void createTemplate(Args* a);
    void startCheckThreaded(Args* a);

public:
    ThreadManager(Args* a);
};
