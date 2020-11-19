#pragma once

class SquareTemplate {
private:
    bool m_isCompact;
    int m_squareSize;
    int m_recurMax;
    int m_recurOffset;
    bool m_showIdentical;
public:
    //constructors
    SquareTemplate(bool isCompact, int squaresize, int reucrMin, int recurMax, bool showIdentical);

    //getters
    bool getIsCompact() const;
    int  getSquareSize() const;
    int getRecurMax() const;
    int getRecurOffset() const;
    bool getShowIdentical() const;

    //methods
    void startCheck();

    int convert2dtoLinear(int r, int c);
    int getLinearR(int pos);
    int getLinearC(int pos);
};
