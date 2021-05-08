#include "Args.h"
#include "ThreadManager.h"
#include <iostream>//cout
#include <chrono>

int main(int argc, char *argv[]) {
    //read arguments
    Args a = Args(argc, argv);
    
    //start timer
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    //calc squares
    ThreadManager tm(a);

    //end timer
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    //print completion message
    std::chrono::duration<double> calcTime = end - start;
    std::cout << "done in " << round(calcTime.count()*1000) << " ms" << "." << std::endl;
}
