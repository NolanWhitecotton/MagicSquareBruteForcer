#pragma once
class SquareTemplate;
#include <memory>

//the types of lines the square checks
enum class LineType {
    Row,
    Column,
    PositiveDiagonal,
    NegativeDiagonal
};

class Square {
private:
    //data
    SquareTemplate* m_tmplt;

    std::unique_ptr<int[]> m_numsLinear;//size^2 ints
    int m_addedNumCount=0;
    int m_lineSumCache=0;

    //constructor methods
    void m_allocArray(int size);
    void m_addAllFrom(const Square& s);

    void m_printSquare(char lineDelim, bool printHeader, bool showIdentical) const;
public:
    //contructors, destructors, and overloads
    Square(int size, SquareTemplate* tmplt); //create an empty square
    Square(const Square& s); //copy construcor
    
    ~Square();//destructor

    //data getters
    int getNum(int pos) const;
    int getNum(int r, int c) const;
    SquareTemplate* getTemplate() const { return m_tmplt; }
    int getAddedNumCount() const { return m_addedNumCount; }
    int getLineSumCache() const { return m_lineSumCache; }
    int getSize() const;
    int getRecurMax() const;
    int getCompact() const;
    int getLineSum(LineType type, int num) const;

    void printSquare() const; //output
    void checkNextRecur();//check children

    //modifiers
    void add(int n);//add n as the next int, update the caches if updateCaches is true
    void removeLastAdd();//undo the last call to add()
};
