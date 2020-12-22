#pragma once

class Square {
private:
    //data
    SquareTemplate* m_tmplt;
    int** m_nums;
    int m_addedNumCount;

    int m_lineSumCache;

    //constructor methods
    void m_allocArray(int size);
    void m_addAllFrom(const Square& s);
    void m_setTemplate(SquareTemplate* tmplt);
    void m_deconstruct2d(int** arr);

    void m_printSquare(char lineDelim, bool printHeader, bool showIdentical) const;

public:
    /*contructors, destructors, and overloads*/
    //create an empty square
    Square(int size, SquareTemplate* tmplt);

    //copy construcor
    Square(const Square& s);

    //destructor
    ~Square();

    /*const methods*/
    int isEmpty() const;
    int getNum(int pos) const;
    int getNum(int r, int c) const;
    void printSquare() const;
    bool isValid() const;
    SquareTemplate* getTemplate() const;
    int getAddedNumCount() const;
    int getLineSumCache() const;

    //pass through to template
    int getSize() const;
    int getRecurMax() const;
    int getCompact() const;

    //calculate the sum of a given line in a given direction
    int getLineSum(int startR, int startC, int incR, int incC) const;

    /*recursion*/
    void checkNextRecur() const;

    /*modifiers*/
    //add n as the next int, update the caches if updateCaches is true
    void add(int n);
};
