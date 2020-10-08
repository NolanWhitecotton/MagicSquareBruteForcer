#pragma once

#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <vector>
#include "time.h"

class SquareManager {
private:
    bool isCompact;
    int squareSize;
    int recurMax;
    int recurOffset;
    bool showIdentical;
public:
    //constructors
    SquareManager(bool isCompact, int squaresize, int reucrMin, int recurMax, bool showIdentical);

    //getters
    bool getIsCompact() const;
    int  getSquareSize() const;
    int getRecurMax() const;
    int getRecurOffset() const;
    bool getShowIdentical() const;

    //methods
    void startCheck();
};

class Square {
private:
    //data
    SquareManager* manager;
    int** nums;
    int addedNumCount;

    int lineSumCache;

    //constructor methods
    void allocArray(int size);
    void addAllFrom(const Square& s);
    void setManager(SquareManager* manager);

public:
    /*contructors, destructors, and overloads*/
    //create an empty square
    Square(int size, SquareManager* manager);

    //copy construcor
    Square(const Square& s);

    //transform constructor
    Square(const Square& s, bool mirrorX, bool mirrorY, bool rotCW, bool rotCC);//TODO (ID2) transform constructor

    //destructor
    ~Square();

    /*const methods*/
    int isEmpty() const;
    int getNum(int pos) const;
    int getNum(int x, int y) const;
    void printSquare() const;
    bool isValid() const;
    double getCompletion() const;
    SquareManager* getManager() const;
    int getSize() const;
    int getRecurMax() const;
    int getCompact() const;
    int getAddedNumCount() const;
    
    /*recursion*/
    void checkNextRecur() const;

    /*modifiers*/
    //add n as the next int, update the caches if updateCaches is true
    void add(int n);

    /*rotation/mirror modifiers*/
    void mirrorX();//TODO (ID1) rot/mirrors
    void mirrorY();
    void rotCC();
    void rotCW();
};

/*conversions*/ // all done zero indexed
int convert2dtoLinear(int x, int y, int size);
int getLinearX(int pos, int size);
int getLinearY(int pos, int size);

/*
returns the sum of a line starting at staryx, starty, and moving incx, incy each time
returns <0 if a zero is found

incC and incR -1 <= x <= 1
startR or startC must be 0
startR and startC must be  0 <= x < size
*/
int getLineSum(const Square& s, int startR, int startC, int incR, int incC);

//read the arguments and store them in the given variables
void readArgs(int argc, char  *argv[], int *size, int *max,
    int *min, int *progress,
    bool *compact, bool *identical,
    std::string *output);

//returns true if min <= intput <= max
bool inRange(int input, int min, int max);

class ArgReader {
private:
    int argc;
    char** argv;

    std::vector<int> argPositions;
    int curArg;

    void parseArgs();
public:
    ArgReader(int argc, char **argv);
    bool hasMoreArgs();
    void next(std::vector<std::string>& s);
    int getArgumentCount();
    int getCurrentArgNum();
};

void print_vector(const std::vector<std::string>& s);
