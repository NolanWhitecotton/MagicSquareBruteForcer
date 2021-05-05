#pragma once
#include <vector>
#include <mutex>
struct Args;
class Validator;

class SquareTemplate {
private:
    std::vector<int> nums;

    std::mutex* m_outputMutex;

    int m_squareSize=0;
    int m_recurMax=0;
    int m_recurOffset=0;
    int minPosSum=0;
    int maxPosSum=0;

    bool m_isCompact=false;
    bool m_showIdentical=true;


    void findRangeRecur_helper(int min, int count, int maxSize, int maxNum, int sum);
    void findRangeRecur(int min, int size);
    void findPossibleRanges(int size, int max);
    void generateValidators();

public:
    //validator lists
    std::vector<std::vector<Validator*>> validators;//TODO make validator list private

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
