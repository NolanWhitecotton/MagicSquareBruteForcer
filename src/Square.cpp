#include "Square.h"
#include "SquareTemplate.h"
#include "Validators.h"
#include <iomanip> //setw
#include <iostream> //cout
#include <mutex>


Square::Square(int size, SquareTemplate& tmplt) : m_tmplt(tmplt){
    m_allocArray(size);
}

Square::Square(const Square& s) : m_tmplt(s.getTemplate()){
    m_allocArray(s.getTemplate().getSquareSize());
    m_addAllFrom(s);
}

void Square::m_allocArray(int size) {
    m_lineSumCache = 0;
    m_addedNumCount = 0;

    //create rows
    m_numsLinear = std::make_unique<int[]>((size_t)size*size);

    //set all ints to 0
    for (int i = 0; i < getTemplate().getSquareArea(); i++) {
        m_numsLinear[(size_t)i] = 0;
    }
}

Square::~Square() {}

void Square::m_addAllFrom(const Square& s) {
    for (int i = 0; i < s.getAddedNumCount(); i++) {
        add(s.getNum(i));
    }
}

void Square::printSquare() const {
    if (getTemplate().getIsCompact()) {
        m_printSquare('\0', false, m_tmplt.getShowIdentical());
    } else {
        m_printSquare('\n', true, m_tmplt.getShowIdentical());
    }
}

bool getBitFlag(int n, int pos) {
    int bitMask = 1 << (pos - 1); //if n is 3, then this will give 0b100
    return (n & bitMask) == bitMask;
}

void Square::m_printSquare(char lineDelim, bool printHeader, bool showIdentical) const {
    using namespace std;

    //lock mutex
    getTemplate().getOutputMutex().lock();

    //print square(s)
    for (int i = 0; i < (showIdentical ? 0b1000 : 0b001); i++) {//for all rotations/reflections to print
        //print the square header
        if (printHeader)
            std::cout << "Size: " << getTemplate().getSquareSize() << " x " << getTemplate().getSquareSize() << endl;

        //get the modifiers from the binary representation of i
        bool firstsub = getBitFlag(i, 1); //read the row backwards
        bool secondsub = getBitFlag(i, 2); //read the col backwards
        bool reverse = getBitFlag(i, 3); //swap r and c

        //calc charWidth
        int biggestNum = (getTemplate().getRecurMax() + getTemplate().getRecurOffset() - 1);
        int outputWidth = (int)std::to_string(biggestNum).length()+1;
        if (getTemplate().getRecurOffset() < 1) {//room for negative signs
            outputWidth++;
        }

        //for every position on the square
        for (int r = 0; r < getTemplate().getSquareSize(); r++) {
            for (int c = 0; c < getTemplate().getSquareSize(); c++) {
                //declare the position on the square
                int first = r, second = c;

                //apply modifiers
                if (reverse) {
                    first = c;
                    second = r;
                }

                if (firstsub)
                    first = getTemplate().getSquareSize() - first - 1;
                if (secondsub)
                    second = getTemplate().getSquareSize() - second - 1;

                //calc num with offset
                int num = getNum(first, second);
                num += getTemplate().getRecurOffset() - 1;

                //print number
                std::cout << setw(outputWidth) << num;
            }
            std::cout << lineDelim;
        }
        std::cout << endl;
    }
    
    //unlock mutex
    getTemplate().getOutputMutex().unlock();
}

void Square::add(int n) {
    //add number
    m_numsLinear[(size_t)getAddedNumCount()] = n;//TODO (DI) change which number gets added dynamically

    m_addedNumCount++;

    //cache if at first row end
    if (getAddedNumCount() == getTemplate().getSquareSize()) {//TODO (DI) cache should by dynamic
        int sum = 0;
        for (int i = 0; i < getTemplate().getSquareSize(); i++) {
            sum += getNum(i);
        }
        m_lineSumCache = sum;
    }
}

//undoes the last add
void Square::removeLastAdd() {
    //undo possible cache
    if (getAddedNumCount() == getTemplate().getSquareSize()) { //TODO (DI) cache should clear dynamically
        m_lineSumCache = 0;
    }

    //dec addedNumCount
    m_addedNumCount--;

    //delete number
    m_numsLinear[(size_t)getAddedNumCount()] = 0;//TODO (DI) number should be reset dynamically
}

int Square::getNum(int pos) const {
    return m_numsLinear[(size_t)pos];
}
int Square::getNum(int r, int c) const {
    return m_numsLinear[(size_t)r * getTemplate().getSquareSize() + c];
}

void Square::checkNextRecur() {
    //TODO (PR) progress reports
    //base case of complete square
    if (getAddedNumCount() >= getTemplate().getSquareArea()) {
        printSquare();
        return;
    }
    
    //recur for all valid squares with applicable ranges added
    int min = getTemplate()->getMinRange(getAddedNumCount(), this);
    int max = getTemplate()->getMaxRange(getAddedNumCount(), this);
    for (int i = min; i <= max; i++) {
        add(i);

        if (getTemplate().doTests(this)) {//run validators
            checkNextRecur();
        }

        removeLastAdd();
    }
}

int Square::getLineSum(LineType type, int num) const {
    int sum = 0;//the current linesum
    int incAmt = 1;//the amount of increment by
    int pos = 0;//the current position

    //calculate pos and inc ammount for the given bools
    //forwards
    switch (type) {
    case LineType::PositiveDiagonal:
        pos = getSize() - 1;
        incAmt = getSize() - 1;
        break;
    case LineType::NegativeDiagonal:
        pos = 0;
        incAmt = getSize() + 1;
        break;
    case LineType::Row:
        pos = num * getSize();
        incAmt = 1;
        break;
    case LineType::Column:
        pos = num;
        incAmt = getSize();
        break;
    default:
        return -2;
        break;
    }

    //calculate sum
    for (int goal = pos + getSize() * incAmt; pos != goal; pos += incAmt) {
        int toAdd = getNum(pos);
        sum += toAdd;
    }

    return sum;
}

