#include "MagicSquareBruteForcer.h"

int main(int argc, char *argv[]) {
    //read arguments
    Args* a = new Args(argc, argv);
    
    //start timer
    std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();

    //calc squares
    ThreadManager tm(a);

    //end timer
    std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

    //print completion message
    std::chrono::duration<double> calcTime = end - start;
    std::cout << "done in " << round(calcTime.count()*1000) << " ms" << "." << std::endl;
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
