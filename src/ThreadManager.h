#pragma once
struct Args;
#include "SquareTemplate.h"

class ThreadManager {
private:
    SquareTemplate tmplt;

    void startCheckThreaded(Args& a);

public:
    ThreadManager(Args& a);
};
