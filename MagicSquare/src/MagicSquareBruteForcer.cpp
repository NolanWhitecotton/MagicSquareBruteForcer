#include "MagicSquareBruteForcer.h"
//#include "../Dependencies/cxxopts.hpp"

int main(int argc, char *argv[]) {
    //test cxxopts
    /*cxxopts::Options options("MyProgram", "One line description of MyProgram");

    options.add_options()
        ("d,debug", "Enable debugging") // a bool parameter
        ("i,integer", "Int param", cxxopts::value<int>())
        ("f,file", "File name", cxxopts::value<std::string>())
        ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
        ;
    try {
        auto result = options.parse(argc, argv);
        std::cout << result["file"].as<std::string>() << " is the sdpecificifed file";
    }
    catch (cxxopts::OptionException e) {
        std::cout << e.what();
    }
    */

    //arg defaults
    int size = 0, max = 0,
        min = 1, progress = 0;
    bool compact = false, identical = false;
    std::string output = "";
    
    //read args
    readArgs(argc, argv, &size, &max, 
        &min, &progress, 
        &compact, &identical, 
        &output);

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

//read the arguments and store them in variables
void readArgs(int argc, char* argv[], int* size, int* max,
    int* min, int* progress,
    bool* compact, bool* identical,
    std::string* output) {

    ArgReader ar = ArgReader(argc, argv);
    while (ar.hasMoreArgs()) {
        std::vector<std::string> s;
        ar.next(s);

        std::string a = s.at(0);
        int optionCount = s.size();
        if (a == "-m" || a == "--max") {
            if (optionCount == 2) {
                *max = std::stoi(s.at(1));
            } else {
                std::cout << a << " requires 2 arguments." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (a == "-s" || a == "--size") {
            if (optionCount == 2) {
                *size = std::stoi(s.at(1));
            }
            else {
                std::cout << a << " requires 2 arguments." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (a == "-n" || a == "--min") {
            if (optionCount == 2) {
               *min = std::stoi(s.at(1));
            }
            else {
                std::cout << a << " requires 2 arguments." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (a == "-o" || a == "--output") {
            if (optionCount == 2) {
                *output = s.at(1);
            }
            else {
                std::cout << a << " requires 2 arguments." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (a == "-p" || a == "--progress") {
            if (optionCount == 2) {
                *progress = stoi(s.at(1));
            }
            else {
                *progress = 60;
            }
        }
        else if (a == "-i" || a == "--identical") {
            *identical = true;
        }
        else if (a == "-c" || a == "--compact") {
            *compact = true;
        }
        else {
            std::cout << "Unknown argument: " << a << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    //check bounds on args
    if (*size <= 0) {
        std::cout << "invalid size: " << *size << std::endl;
        exit(EXIT_FAILURE);
    }
    if (*max <= 0) {
        std::cout << "invalid max: " << *max << std::endl;
        exit(EXIT_FAILURE);
    }
    if (*min >= *max) {
        std::cout << "max must be greater than min" << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool inRange(int input, int min, int max) {
    return input <= max && input >= min;
}
