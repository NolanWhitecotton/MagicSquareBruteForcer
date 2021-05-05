#include "Square.h"
#include <iomanip> //setw
#include <iostream> //cout
#include <mutex>
#include "Validators.h"

Square::Square(int size, SquareTemplate* tmplt) : m_tmplt(tmplt){
    m_allocArray(size);
}

Square::Square(const Square& s) : m_tmplt(s.getTemplate()){
    m_allocArray(s.getSize());
    m_addAllFrom(s);
}

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

bool Square::isValid() const {//TODO (DI) each test should be picked dynamically
    /*check that the newest number is not repeated*/
    //TODO validators should be created and stored in template constructor
    //TODO should test after every add
    UniquenessValidator uv(getAddedNumCount());
    Validator *v = &uv;
    if (!v->run(this)) {
        return false;
    }
    
    
    /*check if square is minimized*/
    //check if the lowest corner is in the top left
    int corners[4] = {
        getNum(0,0),
        getNum(0,getSize()-1), 
        getNum(getSize()-1, 0), 
        getNum(getSize()-1, getSize()-1)
    };

    for (int i = 1; i < 4; i++) {
        if (corners[i] != 0) {
            if (corners[i] < corners[0]) {
                return false;
            }
        }
    }

    //check if its mirrored on the diag
    int val01 = getNum(0, 1);
    int val10 = getNum(1, 0);
    if (val01 != 0 && val10 != 0 && val01 > val10) {
        return false;
    }
    
    //check that the row and column and diagionals are all valid
    if (getAddedNumCount() > getSize()) {//if row is cached
        //row
        int rSum = getLineSum(true, false, false, getTemplate()->getLinearR(getAddedNumCount()) - 1);
        if (rSum > 0 && rSum != getLineSumCache()) { return false; }
        //col
        int cSum = getLineSum(false, false, false, getTemplate()->getLinearC(getAddedNumCount()) - 1);
        if (cSum > 0 && cSum != getLineSumCache()) { return false; }
        //+ diag
        int pdSum = getLineSum(false, true, true, 0);
        if (pdSum > 0 && pdSum != getLineSumCache()) { return false; }
        //- diag
        int ndSum = getLineSum(false, true, false, 0);
        if (ndSum > 0 && ndSum != getLineSumCache()) { return false; }
    }

    //check that the linesum cache is within the valid range
    if (getAddedNumCount() == getSize()) {//if row is cached
        if(getLineSumCache() < getTemplate()->getMinPosSum() || getLineSumCache() > getTemplate()->getMaxPosSum())
            return false;
    }

    return true;
}

void Square::checkNextRecur() {
    //TODO (PR) progress reports
    //base case of complete valid square
    if (getAddedNumCount() >= getSize()*getSize()) {
        printSquare();
        return;
    }
    
    //recur for all valid squares with every legal number appended
    for (int i = 1; i <= getRecurMax(); i++) {
        add(i);

        if (isValid()) {
            if (true) {//TODO if fork on depth && depth is reached
                checkNextRecur();
            } else {
                //TODO (FK) write fork methods
                //TODO (FK) figure out how to add to work queue
            }
        }

        removeLastAdd();
    }
}



//diag is true if you want a diag, false if you want row or col
//row is true if you want a row, false if col
//positive is true if you want a postive diag 
//num is the row or col to caluclate
int Square::getLineSum(bool row, bool diag, bool positive, int num) const{
    int sum = 0;//the current linesum
    int incAmt;//the amount of increment by
    int pos;//the current position

    //calculate pos and inc ammount for the given bools
    //forwards
    /*if (diag) {//diag
        if (positive) {//positive diag
            pos = getSize() - 1;
            incAmt = getSize() - 1;
        }else {//negative diag
            pos = 0;
            incAmt = getSize() + 1;
        }
    }else if (row) {//row
        pos = num *getSize();
        incAmt = 1;
    } else {//col
        pos = num;
        incAmt = getSize();
    }*/
    //reverse TODO (DI) use forewards, this is faster without DI
    if (diag) {//diag
	    if (positive) {//positive diag
		    pos = getSize() * (getSize()-1);
		    incAmt = -1*getSize()+1;
	    }else {//negative diag
		    pos = getSize()*getSize() - 1;
		    incAmt = -1*(getSize()+1);
	    }
    }else if (row) {//row
	    pos = ((num+1) * getSize())-1;
	    incAmt = -1;
    } else {//col
	    pos = getSize()*(getSize() - 1) + num;
	    incAmt = -1*getSize();
    }

    //calculate sum
    for (int goal = pos + getSize() * incAmt; pos != goal; pos += incAmt) {
        int toAdd = getNum(pos);
        if (toAdd == 0)
            return -1;
        sum += toAdd;
    }

    return sum;
}
