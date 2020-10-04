#pragma once

#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <vector>

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

//returns the sum of a line starting at staryx, starty, and moving incx, incy each time
//returns <0 if a zero is found
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
