#pragma once

class ArgReader {
private:
    int m_argc;
    char** m_argv;

    std::vector<int> argPositions;
    int m_curArg;

    void m_parseArgs();
public:
    ArgReader(int argc, char** argv);
    bool hasMoreArgs();
    void next(std::vector<std::string>& s);
    int getArgumentCount();
    int getCurrentArgNum();
};
