#pragma once

class Square {
private:
    //data
    SquareTemplate* m_tmplt;

    std::unique_ptr<int[]> m_numsLinear;//size^2 ints
    int m_addedNumCount;
    int m_lineSumCache;

    //constructor methods
    void m_allocArray(int size);
    void m_addAllFrom(const Square& s);
    void m_setTemplate(SquareTemplate* tmplt);

    void m_printSquare(char lineDelim, bool printHeader, bool showIdentical) const;
public:
    /*contructors, destructors, and overloads*/
    //create an empty square
    Square(int size, SquareTemplate* tmplt);

    //copy construcor
    Square(const Square& s);

    //destructor
    ~Square();

    //data getters
    int getNum(int pos) const;
    int getNum(int r, int c) const;
    SquareTemplate* getTemplate() const;
    int getAddedNumCount() const { return m_addedNumCount; }
    int getLineSumCache() const { return m_lineSumCache; }
    int getSize() const { return getTemplate()->getSquareSize(); }
    int getRecurMax() const { return getTemplate()->getRecurMax(); }
    int getCompact() const { return getTemplate()->getIsCompact(); }

    //data checker
    bool isValid() const;

    //output
    void printSquare() const;

    //calculate the sum of a given line in a given direction
    //int getLineSum(int startR, int startC, int incR, int incC) const;
    int getLineSum(bool row, bool diag, bool positive, int num) const;

    //recursion
    void checkNextRecur();

    //modifiers
    void add(int n);//add n as the next int, update the caches if updateCaches is true
    void removeLastAdd();
};
