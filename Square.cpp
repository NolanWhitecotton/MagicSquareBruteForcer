#include "MagicSquareHeader.h"

Square::Square(int size) {
    allocArray(size);
}

Square::Square(const Square& s) {
    allocArray(s.getSize());
    addAllFrom(s);
    setRecurRange(s.getRecurMax());
    setMinimized(s.getMinimized());
}

void Square::allocArray(int size) {
    this->size = size;
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
    for (int i = 0; i < Square::size; i++) {
        free(Square::nums[i]);
    }

    //free row
    free(Square::nums);
}

int Square::getSize() const { return size; }
int Square::isEmpty() const { return addedNumCount == 0; }
int Square::getAddedNumCount() const { return addedNumCount; }
int Square::getRecurMax() const { return recurMax; }
int Square::getMinimized() const { return isMinimized; }

void Square::addAllFrom(const Square& s) {
    for (int i = 0; i < s.getAddedNumCount(); i++) {
        this->add(s.getNum(i));
    }
}

void Square::printSquare() const {//TODO print tranformations
    if (this->isMinimized) {
        for (int i = 0; i < pow(size,2); i++) {
            std::cout << this->getNum(i) << ' ';
        }
    } else {
        std::cout << "Size: " << size << " x " << size << std::endl;
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                std::cout << std::setw(3) << Square::nums[x][y];
            }
            std::cout << "\n";
        }
    }
    std::cout << std::endl;
}

void Square::add(int n) {
    if (getAddedNumCount() < pow(size, size)) {
        //add number
        int x = getLinearX(getAddedNumCount(), Square::size);
        int y = getLinearY(getAddedNumCount(), Square::size);

        nums[x][y] = n;
        
        //cache if at first row end
        if (getAddedNumCount() == size) {//TODO if dynamic size, edit cache function accordingly, the rest should work
            int sum = 0;
            for (int i = 0; i < size; i++) {
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
    return nums[getLinearX(pos, size)][getLinearY(pos, size)];
}

int Square::getNum(int x, int y) const {
    return Square::nums[x][y];
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
    int corners[3] = {getNum(0,size-1), getNum(size-1,0), getNum(size-1,size-1)};
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
    //TODO call getLineSum backwards, so fails happen faster
    if (this->getAddedNumCount() > this->size) {//if row is cached
        //row
        int rSum = getLineSum(*this, getLinearX(getAddedNumCount(), size) - 1, 0, 0, 1);
        if (rSum > 0 && rSum != this->lineSumCache) { return false; }
        //col
        int cSum = getLineSum(*this, 0, getLinearY(getAddedNumCount() - 1, size), 1, 0);
        if (cSum > 0 && cSum != this->lineSumCache) { return false; }
        //+ diag
        int pdSum = getLineSum(*this, 0, size - 1, 1, -1);
        if (pdSum > 0 && pdSum != this->lineSumCache) { return false; }
        //- diag
        int ndSum = getLineSum(*this, 0, 0, 1, 1);
        if (ndSum > 0 && ndSum != this->lineSumCache) { return false; }
    }

    return true;
}

void Square::checkNextRecur() const {
    static int recurs = 0;
    recurs++;
    //std::cout << recurs << std::endl;
    //TODO progress reports
    //base case of complete square
    if (this->getAddedNumCount() >= pow(this->getSize(), 2)) {
        this->printSquare();
        return;
    }

    //tail recur all numbers within range
    for (int i = 1; i <= this->recurMax; i++) {
        Square newSq = Square(*this);
        newSq.add(i);

        if (newSq.isValid()) {
            newSq.checkNextRecur();
        }
    }
}

//set recur max, and offset
void Square::setRecurRange(int min, int max) {
    this->recurMax = max - min + 1;
    this->recurOffset = min;
}

//set the recur max
void Square::setRecurRange(int max) {
    setRecurRange(1, max);
}

//determines the format the square is printed
void Square::setMinimized(bool minimized) {
    isMinimized = minimized;
}

