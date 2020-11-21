#pragma once

//std includes
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <vector>
#include "time.h"

//class includes
#include "SquareTemplate.h"
#include "Square.h"

//dependency includes
#include "../Dependencies/cxxopts.hpp"

/// <summary>
/// return if a value is within a range
/// </summary>
/// <param name="input">the input to test</param>
/// <param name="min">the maximum value for input</param>
/// <param name="max">the minimum value for input</param>
/// <returns></returns>
bool inRange(int input, int min, int max);

/// <summary>
/// prints a formatted version of a vector
/// </summary>
/// <param name="s">the vector to print</param>
void print_vector(const std::vector<std::string>& s);

/// <summary>
/// stores the commandline arguments
/// </summary>
struct Args {
	int size;
	int max;
	int min;
	bool compactOutput;
	bool outputIdentical;
	int progressReportFrequency;
	std::string outpuDir;

	void loadArgs(int argc, char* argv[]){
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

        try {
            cxxopts::ParseResult result = options.parse(argc, argv);

            //read options
            size = result["s"].as<int>();
            max = result["m"].as<int>();
            min = result["n"].as<int>();
            progressReportFrequency = 0;//TODO (PR) progress reports
            compactOutput = result["c"].as<bool>();
            outputIdentical = result["i"].as<bool>();
            std::string outpuDir = "";//TODO file output

        }
        catch (cxxopts::OptionException e) {
            std::cout << e.what();
            exit(EXIT_FAILURE);
        }
	}

	/// <summary>
	/// checks the ranges on the arguments and returns weather there was an error or not
	/// </summary>
	/// <returns></returns>
	bool checkArgRanges() {
        //check arg ranges
        bool rangeError = false;
        if (size < 1) {
            std::cout << "Size must be greater than 0" << std::endl;
            rangeError = true;
        }

        if (max < pow(size, 2)) {
            std::cout << "Max must be >=size^2" << std::endl;
            rangeError = true;
        }
        if (min >= max) {
            std::cout << "Max must be greater than min" << std::endl;
            rangeError = true;
        }

		return rangeError;
	}
};
