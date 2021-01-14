#include "MagicSquareBruteForcer.h"

Square::Square(int size, SquareTemplate* tmplt) {
    m_setTemplate(tmplt);
    m_allocArray(size);
    m_setAllZero();
}

Square::Square(const Square& s) {
    m_setTemplate(s.getTemplate());
    m_allocArray(s.getSize());
    m_addAllFrom(s);
}

void Square::m_setAllZero() {
    //set all ints to 0
    for (int i = 0; i < getSize() * getSize(); i++) {
        m_numsLinear[i] = 0;
    }
}

void Square::m_allocArray(int size) {
    m_addedNumCount = 0;

    //create rows
    m_numsLinear = (new int[size*size]());//alloc size^2 ints
    if (!m_numsLinear) { exit(EXIT_FAILURE); }
}

Square::~Square() {
    delete m_numsLinear;
}

int Square::getSize() const { return getTemplate()->getSquareSize(); }
int Square::getRecurMax() const { return getTemplate()->getRecurMax(); }
int Square::getCompact() const { return getTemplate()->getIsCompact(); }
int Square::getAddedNumCount() const { return m_addedNumCount; }
int Square::getLineSumCache() const { return m_lineSumCache; }

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

bool getKthBit(unsigned int n, unsigned int k) {return ((n & (1 << (k - 1))) >> (k - 1)) == 1;}
void Square::m_printSquare(char lineDelim, bool printHeader, bool showIdentical) const {
    using namespace std;

    //lock mutex
    getTemplate()->getOutputMutex()->lock();

    //print square(s)
    for (int i = 0; i < (showIdentical ? 8 : 1); i++) {//for all rotations/reflections to print
        //print the square header
        if (printHeader)
            cout << "Size: " << getSize() << " x " << getSize() << endl;

        //get the modifiers from the binary representation of i
        bool firstsub = getKthBit(i, 1); //read the row backwards
        bool secondsub = getKthBit(i, 2); //read the col backwards
        bool reverse = getKthBit(i, 3); //swap r and c


        //calc charWidth
        int biggestNum = (getTemplate()->getRecurMax() + getTemplate()->getRecurOffset());
        int charWidth = ceil(((double)biggestNum / 10));

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
                cout << setw(charWidth+1) << num;
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
    m_numsLinear[getAddedNumCount()] = n;//TODO (DI)

    //cache if at first row end
    if (getAddedNumCount() == getSize()) {//TODO (DI) if dynamic insertion, edit cache function accordingly, the rest should work
        int sum = 0;
        for (int i = 0; i < getSize(); i++) {
            sum += getNum(i);
        }
        m_lineSumCache = sum;
    }

    m_addedNumCount++;
}

int Square::getNum(int pos) const {
    return m_numsLinear[pos];
}
int Square::getNum(int r, int c) const {
    return m_numsLinear[r*getSize()+c];
}

bool Square::isValid() const {//TODO (DI)
    /*check that the newest number is not repeated*/
    for (int i = 0; i < getAddedNumCount() - 1; i++) {
        if (getNum(i) == getNum(getAddedNumCount()-1)) {
            return false;
        }
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
    if (getNum(0, 1) != 0 && getNum(1, 0) != 0 && getNum(0, 1) > getNum(1, 0)) {
        return false;
    }
    
    //check that the row and column and diagionals are all valid
    if (getAddedNumCount() > getSize()) {//if row is cached
        int rSum = getLineSum(getTemplate()->getLinearR(getAddedNumCount()) - 1, getSize()-1, 0, -1);
        if (rSum > 0 && rSum != getLineSumCache()) { return false; }
        //col
        int cSum = getLineSum(getSize()-1, getTemplate()->getLinearC(getAddedNumCount() - 1), -1, 0);
        if (cSum > 0 && cSum != getLineSumCache()) { return false; }
        //+ diag
        int pdSum = getLineSum(getSize()-1, 0, -1, 1);
        if (pdSum > 0 && pdSum != getLineSumCache()) { return false; }
        //- diag
        int ndSum = getLineSum(getSize() - 1, getSize() - 1, -1, -1);
        if (ndSum > 0 && ndSum != getLineSumCache()) { return false; }
    }

    //check that the linesum cache is within the valid range
    if (getAddedNumCount() == getSize()+1) {//if row is cached
        if (!inRange(getLineSumCache(), getTemplate()->getMinPosSum(), getTemplate()->getMaxPosSum())) {
            return false;
        }
    }

    return true;
}

void Square::checkNextRecur() const {
    //TODO (PR) progress reports
    //base case of complete valid square
    if (getAddedNumCount() >= getSize()*getSize()) {
        printSquare();
        return;
    }
    
    //recur for all valid squares with every legal number appended
    for (int i = 1; i <= getRecurMax(); i++) {
        Square newSq = Square(*this);
        newSq.add(i);

        if (newSq.isValid()) {
            newSq.checkNextRecur();
        }
    }
}

void Square::m_setTemplate(SquareTemplate* tmplt) {m_tmplt = tmplt;}
SquareTemplate* Square::getTemplate() const {return m_tmplt;}

int Square::getLineSum(int startR, int startC, int incR, int incC) const{
    //get sum
    int goalR = (startR + incR * getSize()) + (incR >= 0 ? -1 : 1);
    int goalC = (startC + incC * getSize()) + (incC >= 0 ? -1 : 1);

    int sum = 0, r = startR, c = startC;
    bool atEnd = false;
    while (!atEnd) {
        //add sum
        int toAdd = getNum(r, c);
        if (toAdd == 0) {
            return -1;
        }
        sum += toAdd;

        //check atEnd
        atEnd = ((r == goalR) || (c == goalC));

        //inc r and c
        r += incR;
        c += incC;
    }

    return sum;
}
