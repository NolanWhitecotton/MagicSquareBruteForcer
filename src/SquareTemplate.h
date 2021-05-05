#pragma once
#include <vector>
#include <mutex>
#include "Args.h"
#include "Validators.h"

class SquareTemplate {
private:
    std::vector<int> nums;

    std::mutex* m_outputMutex;

    int m_squareSize;
    int m_recurMax;
    int m_recurOffset;
    int minPosSum;
    int maxPosSum;

    bool m_isCompact;
    bool m_showIdentical;


    void findRangeRecur_helper(int min, int count, int maxSize, int maxNum, int sum);
    void findRangeRecur(int min, int size);
    void findPossibleRanges(int size, int max);
    void generateValidators();

public:
    //validator lists
    std::vector<std::vector<Validator*>> validators;//TODO make this private

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
