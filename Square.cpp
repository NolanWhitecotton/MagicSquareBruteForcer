#include "MagicSquareHeader.h"

Square::Square(int size, SquareManager* manager) {
    this->setManager(manager);
    allocArray(size);
}

Square::Square(const Square& s) {
    this->setManager(s.getManager());
    this->allocArray(s.getSize());
    this->addAllFrom(s);
}

void Square::allocArray(int size) {
    this->addedNumCount = 0;

    //create rows
    Square::nums = (int**)calloc(size, sizeof(int*));
    if (nums == nullptr) { exit(EXIT_FAILURE); }

    //for all rows
    for (int i = 0; i < size; i++) {
        //create columns
        int* r = (int*)calloc(size, sizeof(int));
        if (r == nullptr) { exit(EXIT_FAILURE); }

        Square::nums[i] = r;
    }
}

Square::~Square() {
    //free all columns
    for (int i = 0; i < this->getSize(); i++) {
        free(this->nums[i]);
    }

    //free row
    free(this->nums);
}

int Square::getSize() const { return this->getManager()->getSquareSize(); }
int Square::isEmpty() const { return addedNumCount == 0; }
int Square::getAddedNumCount() const { return addedNumCount; }
int Square::getRecurMax() const { return this->getManager()->getRecurMax(); }
int Square::getCompact() const { return this->getManager()->getIsCompact(); }

void Square::addAllFrom(const Square& s) {
    for (int i = 0; i < s.getAddedNumCount(); i++) {
        this->add(s.getNum(i));
    }
}

void Square::printSquare() const {//TODO (ID3) print tranformations
    if (this->getCompact()) {
        for (int i = 0; i < pow(this->getSize(),2); i++) {
            std::cout << this->getNum(i) << ' ';
        }
    } else {
        std::cout << "Size: " << this->getSize() << " x " << this->getSize() << std::endl;
        for (int x = 0; x < this->getSize(); x++) {
            for (int y = 0; y < this->getSize(); y++) {
                std::cout << std::setw(3) << Square::nums[x][y];
            }
            std::cout << "\n";
        }
    }
    std::cout << std::endl;
}

void Square::add(int n) {
    if (getAddedNumCount() < pow(this->getSize(), this->getSize())) {
        //add number
        int x = getLinearX(getAddedNumCount(), this->getSize());
        int y = getLinearY(getAddedNumCount(), this->getSize());
        nums[x][y] = n;

        //cache if at first row end
        if (getAddedNumCount() == this->getSize()) {//TODO (DI) if dynamic insertion, edit cache function accordingly, the rest should work
            int sum = 0;
            for (int i = 0; i < this->getSize(); i++) {
                sum += getNum(i);
            }
            lineSumCache = sum;
        }

        addedNumCount++;
    }else{
        std::cout << "Cannot insert another number" << std::endl;
    }
}

int Square::getNum(int pos) const {
    return nums[getLinearX(pos, this->getSize())][getLinearY(pos, this->getSize())];
}

int Square::getNum(int r, int c) const {
    return Square::nums[r][c];
}

bool Square::isValid() const {
    /*check that the newest number is not repeated*/
    for (int i = 0; i < getAddedNumCount() - 1; i++) {
        if (this->getNum(i) == this->getNum(getAddedNumCount()-1)) {
            return false;
        }
    }
    
    /*check if square is minimized*/
    //check if the lowest corner is in the top left
    int corners[3] = {
        getNum(0,this->getSize() -1), 
        getNum(this->getSize() -1,0), 
        getNum(this->getSize() -1, this->getSize() -1)
    };

    for (int i = 0; i < 2; i++) {
        if (corners[i] != 0 && getNum(0, 0) > corners[i]) {
            return false;
        }
    }
    //check if its mirrored on the diag
    if (getNum(0, 2) != 0 && getNum(2, 0) != 0 && getNum(0, 2) < getNum(2, 0)) {
        return false;
    }
    
    /*check that the row and column and diagionals are all valid*/
    //TODO (EF2) call getLineSum backwards, so fails happen faster
    if (this->getAddedNumCount() > this->getSize()) {//if row is cached
        //row
        int rSum = getLineSum(*this, getLinearX(getAddedNumCount(), this->getSize()) - 1, 0, 0, 1);
        if (rSum > 0 && rSum != this->lineSumCache) { return false; }
        //col
        int cSum = getLineSum(*this, 0, getLinearY(getAddedNumCount() - 1, this->getSize()), 1, 0);
        if (cSum > 0 && cSum != this->lineSumCache) { return false; }
        //+ diag
        int pdSum = getLineSum(*this, 0, this->getSize() - 1, 1, -1);
        if (pdSum > 0 && pdSum != this->lineSumCache) { return false; }
        //- diag
        int ndSum = getLineSum(*this, 0, 0, 1, 1);
        if (ndSum > 0 && ndSum != this->lineSumCache) { return false; }
    }

    return true;
}

void Square::checkNextRecur() const {
    int recurs = 0;
    recurs++;
    //std::cout << recurs << std::endl;
    //TODO (PR) progress reports
    //base case of complete square
    if (this->getAddedNumCount() >= pow(this->getSize(), 2)) {
        this->printSquare();
        return;
    }
    
    //tail recur all numbers within range
    for (int i = 1; i <= this->getRecurMax(); i++) {
        Square newSq = Square(*this);
        newSq.add(i);

        if (newSq.isValid()) {
            newSq.checkNextRecur();
        }
    }
}

void Square::setManager(SquareManager* manager) {
    this->manager = manager;
}

SquareManager* Square::getManager() const {
    return this->manager;
}
