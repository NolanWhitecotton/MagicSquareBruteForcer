#pragma once
class SquareTemplate;
struct Args;

class ThreadManager {
private:
    SquareTemplate* tmplt;

    void createTemplate(Args& a);
    void startCheckThreaded(Args& a);

public:
    ThreadManager(Args& a);
};
