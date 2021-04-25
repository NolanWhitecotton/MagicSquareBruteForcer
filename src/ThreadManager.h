#pragma once
#include "SquareTemplate.h"
#include "Args.h"
#include <thread>

class ThreadManager {
private:
    SquareTemplate* tmplt;

    void createTemplate(Args* a);
    void startCheckThreaded(Args* a);

public:
    ThreadManager(Args* a);
};
