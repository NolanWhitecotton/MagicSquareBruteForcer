#pragma once

class ArgReader {
private:
    int argc;
    char** argv;

    std::vector<int> argPositions;
    int curArg;

    void parseArgs();
public:
    ArgReader(int argc, char** argv);
    bool hasMoreArgs();
    void next(std::vector<std::string>& s);
    int getArgumentCount();
    int getCurrentArgNum();
};
