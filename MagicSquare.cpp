#include "MagicSquareHeader.h"
/*
things to add
-arg support minimized=false, doRotations=true, min=1, max=req
-dynamic (proven?) ordering
    -start near center?
    -move in the position that minimizes the time until next line completion
    -this can be cached once at the begining
*/
int main() {
    Square sq = Square(3);

    sq.setMinimized(false);
    sq.setRecurRange(1, 9);

    sq.checkNextRecur();
}

int convert2dtoLinear(int x, int y, int size) {return x * size + y;}
int getLinearX(int pos, int size) {return pos / size;}
int getLinearY(int pos, int size) {return pos % size;}

void Square::checkNextRecur() const {
    static int recurs = 0;
    recurs++;
    //std::cout << recurs << std::endl;
    //TODO progress reports
    //base case of complete square
    if (this->getAddedNumCount() >= pow(this->getSize(),2)) {
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
    this->recurMax = max - min +1;
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
