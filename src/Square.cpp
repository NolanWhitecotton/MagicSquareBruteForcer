#include "Square.h"
#include "SquareTemplate.h"
#include "Validators.h"
#include <iomanip> //setw
#include <iostream> //cout
#include <mutex>


Square::Square(int size, SquareTemplate* tmplt) : m_tmplt(tmplt){
    m_allocArray(size);
}

Square::Square(const Square& s) : m_tmplt(s.getTemplate()){
    m_allocArray(s.getSize());
    m_addAllFrom(s);
}

int Square::getSize() const { return getTemplate()->getSquareSize(); }
int Square::getRecurMax() const { return getTemplate()->getRecurMax(); }
int Square::getCompact() const { return getTemplate()->getIsCompact(); }

void Square::m_allocArray(int size) {
    m_lineSumCache = 0;
    m_addedNumCount = 0;

    //create rows
    m_numsLinear = std::make_unique<int[]>((size_t)size*size);

    //set all ints to 0
    for (int i = 0; i < (int)getSize() * (int)getSize(); i++) {
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
    if (getCompact()) {
        m_printSquare('\0', false, m_tmplt->getShowIdentical());
    } else {
        m_printSquare('\n', true, m_tmplt->getShowIdentical());
    }
}

bool getBitFlag(int n, int pos) {
    int bitMask = 1 << (pos - 1); //if n is 3, then this will give 0b100
    return (n & bitMask) == bitMask;
}

void Square::m_printSquare(char lineDelim, bool printHeader, bool showIdentical) const {
    using namespace std;

    //lock mutex
    getTemplate()->getOutputMutex()->lock();

    //print square(s)
    for (int i = 0; i < (showIdentical ? 0b1000 : 0b001); i++) {//for all rotations/reflections to print
        //print the square header
        if (printHeader)
            cout << "Size: " << getSize() << " x " << getSize() << endl;

        //get the modifiers from the binary representation of i
        bool firstsub = getBitFlag(i, 1); //read the row backwards
        bool secondsub = getBitFlag(i, 2); //read the col backwards
        bool reverse = getBitFlag(i, 3); //swap r and c

        //calc charWidth
        int biggestNum = (getTemplate()->getRecurMax() + getTemplate()->getRecurOffset() - 1);
        int outputWidth = (int)std::to_string(biggestNum).length()+1;
        if (getTemplate()->getRecurOffset() < 1) {//room for negative signs
            outputWidth++;
        }

        //for every position on the square
        for (int r = 0; r < getSize(); r++) {
            for (int c = 0; c < getSize(); c++) {
                //declare the position on the square
                int first = r, second = c;

                //apply modifiers
                if (reverse) {
                    first = c;
                    second = r;
                }

                if (firstsub)
                    first = getSize() - first - 1;
                if (secondsub)
                    second = getSize() - second - 1;

                //calc num with offset
                int num = getNum(first, second);
                num += getTemplate()->getRecurOffset() - 1;

                //print number
                cout << setw(outputWidth) << num;
            }
            cout << lineDelim;
        }
        cout << endl;
    }
    
    //unlock mutex
    getTemplate()->getOutputMutex()->unlock();
}

void Square::add(int n) {
    //add number
    m_numsLinear[(size_t)getAddedNumCount()] = n;//TODO (DI) change which number gets added dynamically

    m_addedNumCount++;

    //cache if at first row end
    if (getAddedNumCount() == getSize()) {//TODO (DI) cache should by dynamic
        int sum = 0;
        for (int i = 0; i < getSize(); i++) {
            sum += getNum(i);
        }
        m_lineSumCache = sum;
    }
}

//undoes the last add
void Square::removeLastAdd() {
    //undo possible cache
    if (getAddedNumCount() == getSize()) { //TODO (DI) cache should clear dynamically
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
    return m_numsLinear[(size_t)r * getSize() + c];
}

void Square::checkNextRecur() {
    //TODO (PR) progress reports
    //base case of complete square
    if (getAddedNumCount() >= getSize()*getSize()) {
        printSquare();
        return;
    }
    
    //recur for all valid squares with applicable ranges added
    int min = getTemplate()->getMinRange(getAddedNumCount()-1, this);
    int max = getTemplate()->getMaxRange(getAddedNumCount()-1, this);
    for (int i = min; i <= max; i++) {
        add(i);

        if (getTemplate()->doTests(this)) {//run validators
            checkNextRecur();
        }

        removeLastAdd();
    }
}
