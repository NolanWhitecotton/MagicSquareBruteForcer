#include "Args.h"
#include "../Dependencies/cxxopts.hpp"
#include <thread>//hardware concurency

Args::Args(int argc, char* argv[]) {
    //read args with cxxopts 2.2.0
    cxxopts::Options options("MSBF", "Find all the possible magic squares of size n using number n-m");

    options.add_options()
        ("s,size", "The size of the square", cxxopts::value<int>())
        ("m,max", "The max number to search with inclusive", cxxopts::value<int>())
        ("n,min", "The minimum number to search with inclusive", cxxopts::value<int>()->default_value("1"))
        ("c,compact", "Weather or not to use compact output", cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
        ("i,identical", "Weather or not to include mirrors and rotations", cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
        ("o,output", "Weather or not to include mirrors and rotations", cxxopts::value<std::string>())
        ("t,threads", "The number of threads to try and run on", cxxopts::value<int>()->default_value(std::to_string(std::thread::hardware_concurrency())))
        ;

    try {
        cxxopts::ParseResult result = options.parse(argc, argv);

        //read options
        size = result["s"].as<int>();
        max = result["m"].as<int>();
        min = result["n"].as<int>();
        progressReportFrequency = 0;//TODO (PR) progress reports
        compactOutput = result["c"].as<bool>();
        outputIdentical = result["i"].as<bool>();
        outpuDir = "";//TODO file output
        threadCount = result["t"].as<int>();
    }
    catch (...) {
        std::cout << "Error parsing arguments, size and max are required." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (checkArgRanges()) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
}

//used for tests
Args::Args(int asize, int amax, int amin, bool comp, bool identical, int threads):
    size(asize), max(amax), min(amin), threadCount(threads), compactOutput(comp), outputIdentical(identical) {}

//checks the ranges on the arguments and returns weather there was an error or not
bool Args::checkArgRanges() {
    //check arg ranges
    bool rangeError = false;
    if (size < 1) {
        std::cout << "Size must be greater than 0" << std::endl;
        rangeError = true;
    }
    if (max-min+1 < size * size) {
        std::cout << "Not enough values in range" << std::endl;
        rangeError = true;
    }
    if (min >= max) {
        std::cout << "Max must be greater than min" << std::endl;
        rangeError = true;
    }
    if (threadCount < 1) {
        std::cout << "Must use at least one thread" << std::endl;
        rangeError = true;
    }

    return rangeError;
}
