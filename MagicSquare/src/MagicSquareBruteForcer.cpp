#include "MagicSquareBruteForcer.h"
#include "../Dependencies/cxxopts.hpp"

int main(int argc, char *argv[]) {
    //read args with cxxopts 2.2.0
    cxxopts::Options options("MSBF", "Find all the possible magic squares of size n using number n-m");

    options.add_options()
        ("s,size", "The size of the square", cxxopts::value<int>())
        ("m,max", "The max number to search with inclusive", cxxopts::value<int>())
        ("n,min", "The minimum number to search with inclusive", cxxopts::value<int>()->default_value("1"))
        ("c,compact", "Weather or not to use compact output", cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
        ("i,identical", "Weather or not to include mirrors and rotations", cxxopts::value<bool>()->default_value("true")->implicit_value("false"))
        ("o,output", "Weather or not to include mirrors and rotations", cxxopts::value<std::string>())
        ;

    int size, max, min, progress;
    bool compact, identical;
    std::string ouput;

    try {
        cxxopts::ParseResult result = options.parse(argc, argv);
   
        //read options
        size = result["s"].as<int>();
        max = result["m"].as<int>();
        min = result["n"].as<int>();
        progress = 0;//TODO (PR) progress reports
        compact = result["c"].as<bool>();
        identical = result["i"].as<bool>();
        std::string output = "";//TODO file output

    } catch (cxxopts::OptionException e) {
        std::cout << e.what();
        exit(EXIT_FAILURE);
    }

    //check arg ranges
    bool rangeError = false;
    if (size < 1) {
        std::cout << "Size must be greater than 0" << std::endl;
        rangeError = true;
    }

    if (max < pow(size,2)) {
        std::cout << "Max must be >=size^2" << std::endl;
        rangeError = true;
    }
    if (min >= max) {
        std::cout << "Max must be greater than min" << std::endl;
        rangeError = true;
    }

    if (rangeError) {
        exit(EXIT_FAILURE);
    }
    
    //start timer
    time_t start;
    time(&start);

    //calc squares
    SquareTemplate sqt = SquareTemplate(compact, size, min, max, identical);
    sqt.startCheck();

    //end timer
    time_t end;
    time(&end);

    //print completion
    int calcTime = std::difftime(end,start);
    std::cout << "done in " << calcTime << " second" << (calcTime==1 ? "" : "s") << "." << std::endl;
}

void print_vector(const std::vector<std::string>& s) {
    for (std::vector<std::string>::const_iterator it = s.begin(); it != s.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

bool inRange(int input, int min, int max) {
    return input <= max && input >= min;
}
