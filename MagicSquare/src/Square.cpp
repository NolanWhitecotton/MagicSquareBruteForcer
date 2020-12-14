#include "MagicSquareBruteForcer.h"

Square::Square(int size, SquareTemplate* tmplt) {
    m_setTemplate(tmplt);
    m_allocArray(size);
}

Square::Square(const Square& s) {
    m_setTemplate(s.getTemplate());
    m_allocArray(s.getSize());
    m_addAllFrom(s);
}

void Square::m_allocArray(int size) {
    m_addedNumCount = 0;

    //create rows
    m_nums = (int**)calloc(size, sizeof(int*));
    if (m_nums == nullptr) { exit(EXIT_FAILURE); }

    //for all rows
    for (int i = 0; i < size; i++) {
        //create columns
        int* r = (int*)calloc(size, sizeof(int));
        if (r == nullptr) { exit(EXIT_FAILURE); }

        m_nums[i] = r;
    }
}

Square::~Square() {
    m_deconstruct2d(m_nums);
}

void Square::m_deconstruct2d(int** arr) {
    //free all columns
    for (int i = 0; i < getSize(); i++) {
        free(m_nums[i]);
    }

    //free row
    free(m_nums);
}

int Square::getSize() const { return getTemplate()->getSquareSize(); }
int Square::getRecurMax() const { return getTemplate()->getRecurMax(); }
int Square::getCompact() const { return getTemplate()->getIsCompact(); }
int Square::isEmpty() const { return m_addedNumCount == 0; }
int Square::getAddedNumCount() const { return m_addedNumCount; }
int Square::getLineSumCache() const { return m_lineSumCache; }


void Square::m_addAllFrom(const Square& s) {
    for (int i = 0; i < s.getAddedNumCount(); i++) {
        add(s.getNum(i));
    }
}

void Square::printSquare() const {
    if (getCompact()) {
        m_fPrintSquare('\0', false, m_tmplt->getShowIdentical());
    } else {
        m_fPrintSquare('\n', true, m_tmplt->getShowIdentical());
    }
}

void Square::m_fPrintSquare(char lineDelim, bool printHeader, bool showIdentical) const{
    using namespace std;

    if(printHeader) 
        cout << "Size: " << getSize() << " x " << getSize() << endl;

    //print current square
    for (int r = 0; r < getSize(); r++) {
        for (int c = 0; c < getSize(); c++) {
            cout << setw(3) << getNum(r, c);
        }
        cout << lineDelim;
    }
    cout << endl;

    //print all symetries of the current square
    if (showIdentical) {
        for (int c = 0; c < getSize(); c++) {
            for (int r = 0; r < getSize(); r++) {
                cout << setw(3) << getNum(r, c);
            }
            cout << lineDelim;
        }
        cout << endl;

        for (int r = getSize() - 1; r >= 0; r--) {
            for (int c = 0; c < getSize(); c++) {
                cout << setw(3) << getNum(r, c);
            }
            cout << lineDelim;
        }
        cout << endl;

        for (int c = getSize() - 1; c >= 0; c--) {
            for (int r = 0; r < getSize(); r++) {
                cout << setw(3) << getNum(r, c);
            }
            cout << lineDelim;
        }
        cout << endl;

        for (int r = 0; r < getSize(); r++) {
            for (int c = getSize() - 1; c >= 0; c--) {
                cout << setw(3) << getNum(r, c);
            }
            cout << lineDelim;
        }
        cout << endl;

        for (int c = 0; c < getSize(); c++) {
            for (int r = getSize() - 1; r >= 0; r--) {
                cout << setw(3) << getNum(r, c);
            }
            cout << lineDelim;
        }
        cout << endl;

        for (int r = getSize() - 1; r >= 0; r--) {
            for (int c = getSize() - 1; c >= 0; c--) {
                cout << setw(3) << getNum(r, c);
            }
            cout << lineDelim;
        }
        cout << endl;

        for (int c = getSize() - 1; c >= 0; c--) {
            for (int r = getSize() - 1; r >= 0; r--) {
                cout << setw(3) << getNum(r, c);
            }
            cout << lineDelim;
        }
        cout << endl;
    }
}

void Square::add(int n) {
    if (getAddedNumCount() < pow(getSize(), getSize())) {
        //add number
        int r = getTemplate()->getLinearR(getAddedNumCount());
        int c = getTemplate()->getLinearC(getAddedNumCount());
        m_nums[r][c] = n;

        //cache if at first row end
        if (getAddedNumCount() == getSize()) {//TODO (DI) if dynamic insertion, edit cache function accordingly, the rest should work
            int sum = 0;
            for (int i = 0; i < getSize(); i++) {
                sum += getNum(i);
            }
            m_lineSumCache = sum;
        }

        m_addedNumCount++;
    }else{
        std::cout << "Cannot insert another number" << std::endl;
    }
}

int Square::getNum(int pos) const {
    return getNum(getTemplate()->getLinearR(pos), getTemplate()->getLinearC(pos));
}

int Square::getNum(int r, int c) const {
    return m_nums[r][c];
}

bool Square::isValid() const {
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
    
    /*check that the row and column and diagionals are all valid*/
    
    if (getAddedNumCount() > getSize()) {//if row is cached
        //row
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

    return true;
}

void Square::checkNextRecur() const {
    int recurs = 0;
    recurs++;
    //std::cout << recurs << std::endl;
    //TODO (PR) progress reports
    //base case of complete square
    if (getAddedNumCount() >= pow(getSize(), 2)) {
        printSquare();
        return;
    }
    
    //tail recur all numbers within range
    for (int i = 1; i <= getRecurMax(); i++) {
        Square newSq = Square(*this);
        newSq.add(i);

        if (newSq.isValid()) {
            newSq.checkNextRecur();
        }
    }
}

void Square::m_setTemplate(SquareTemplate* tmplt) {
    m_tmplt = tmplt;
}

SquareTemplate* Square::getTemplate() const {
    return m_tmplt;
}

double Square::getCompletion() const {
    int numC = (int)pow(getSize(), 2);

    double total = 0;
    for (int i = 1; i <= numC; i++) {
        double port = pow(((double)1 / (getRecurMax())), i);
        total += port;
    }

    double percent = 0;

    for (int i = 0; i < numC; i++) {
        double adding = ((double)getNum(i) / getRecurMax());
        double port = pow(((double)1 / getRecurMax()), i + 1) / total;
        percent += adding * port;
    }
    return percent * 100;
}

int Square::getLineSum(int startR, int startC, int incR, int incC) const{
    //check ranges
    if (!(inRange(incR, -1, 1) && inRange(incC, -1, 1) &&
        inRange(startR, 0, getSize() - 1) && inRange(startC, 0, getSize() - 1))) {
        std::cout << "invalid getLineSum ranges";
        exit(EXIT_FAILURE);
    }

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
