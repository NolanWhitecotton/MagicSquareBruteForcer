#pragma once

#include <iostream>
#include <math.h>
#include <iomanip>

class Square {
private:
    int size;
    int **nums;
    int addedNumCount;

    bool isMinimized = false;
    int recurMax;
    bool recurOffset;

    void allocArray(int size);

    int lineSumCache;

    void addAllFrom(const Square& s);
public:
    /*contructors, destructors, and overloads*/
    //create an empty square
    Square(int size);

    //copy construcor
    Square(const Square& s);

    //transform constructor
    Square(const Square& s, bool mirrorX, bool mirrorY, bool rotCW, bool rotCC);//TODO transform constructor

    //destructor
    ~Square();

    /*const methods*/
    int getSize() const;
    int isEmpty() const;
    int getAddedNumCount() const;
    int getNum(int pos) const;
    int getNum(int x, int y) const;
    void printSquare() const;
    bool isValid() const;
    int getRecurMax() const;
    int getMinimized() const;

    /*recursion*/
    void checkNextRecur() const;

    /*modifiers*/
    //add n as the next int, update the caches if updateCaches is true
    void add(int n);

    /*settings*/
    void setRecurRange(int min, int max);
    void setRecurRange(int max);
    void setMinimized(bool minimized);

    /*rotation/mirror modifiers*/
    void mirrorX();//TODO rot/mirrors
    void mirrorY();
    void rotCC();
    void rotCW();
};

/*conversions*/ // all done zero indexed
int convert2dtoLinear(int x, int y, int size);
int getLinearX(int pos, int size);
int getLinearY(int pos, int size);
