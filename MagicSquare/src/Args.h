#pragma once

#include "../Dependencies/cxxopts.hpp"
#include <thread>

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