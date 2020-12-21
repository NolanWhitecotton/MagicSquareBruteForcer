#include "MagicSquareBruteForcer.h"

int main(int argc, char *argv[]) {
    //read arguments
    Args a;
    a.loadArgs(argc, argv);

    if (a.checkArgRanges()) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    
    //start timer
    time_t start;
    time(&start);

    //calc squares
    SquareTemplate sqt = SquareTemplate(a.compactOutput, a.size, a.min, a.max, a.outputIdentical);
    sqt.startCheckThreaded(a.threadCount);

    //end timer
    time_t end;
    time(&end);

    //print completion message
    int calcTime = std::difftime(end,start);
    std::cout << "done in " << calcTime << " second" << (calcTime==1 ? "" : "s") << "." << std::endl;
}

void print_vector(const std::vector<std::string>& s) {
    using namespace std;

    for (vector<std::string>::const_iterator it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

bool inRange(int input, int min, int max) {
    return input <= max && input >= min;
}
