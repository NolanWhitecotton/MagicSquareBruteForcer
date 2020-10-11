#pragma once

class Square {
private:
    //data
    SquareTemplate* tmplt;
    int** nums;
    int addedNumCount;

    int lineSumCache;

    //constructor methods
    void allocArray(int size);
    void addAllFrom(const Square& s);
    void setTemplate(SquareTemplate* tmplt);

public:
    /*contructors, destructors, and overloads*/
    //create an empty square
    Square(int size, SquareTemplate* tmplt);

    //copy construcor
    Square(const Square& s);

    //transform constructor
    Square(const Square& s, bool mirrorR, bool mirrorC, bool rotCW, bool rotCC);//TODO (ID2) transform constructor

    //destructor
    ~Square();

    /*const methods*/
    int isEmpty() const;
    int getNum(int pos) const;
    int getNum(int r, int c) const;
    void printSquare() const;
    bool isValid() const;
    double getCompletion() const;
    SquareTemplate* getTemplate() const;
    int getAddedNumCount() const;

    //pass through to template
    int getSize() const;
    int getRecurMax() const;
    int getCompact() const;

    /// <summary>
    /// calculate the sum of a given line in a given direction
    /// </summary>
    /// <param name="startR">the starting row</param>
    /// <param name="startC">the starting column</param>
    /// <param name="incR">increment step for row</param>
    /// <param name="incC">increment step for column</param>
    /// <returns>the sum of a line provided, or negative if a zero is hit</returns>
    int getLineSum(int startR, int startC, int incR, int incC) const;


    /*recursion*/
    void checkNextRecur() const;

    /*modifiers*/
    //add n as the next int, update the caches if updateCaches is true
    void add(int n);

    /*rotation/mirror modifiers*/
    void mirrorR();//TODO (ID1) rot/mirrors
    void mirrorC();
    void rotCC();
    void rotCW();
};
