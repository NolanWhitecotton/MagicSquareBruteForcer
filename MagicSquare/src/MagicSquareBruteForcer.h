#pragma once

//std includes
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

//dependency includes
#include "../Dependencies/cxxopts.hpp"

//stores the commandline arguments
struct Args {
	int size = 0;
	int max = 0;
	int min = 0;
	bool compactOutput = false;
	bool outputIdentical = false;
	int progressReportFrequency = 100;
	std::string outpuDir = "c:/";
    int threadCount = 1;

	Args(int argc, char* argv[]);
	bool checkArgRanges();
};

//class includes
#include "SquareTemplate.h"
#include "Square.h"
