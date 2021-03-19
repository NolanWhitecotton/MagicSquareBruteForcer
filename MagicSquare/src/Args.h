#pragma once
#include <string>

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
	Args(int size, int max, int min, bool comp, bool identical, int threads);

	bool checkArgRanges();
};
