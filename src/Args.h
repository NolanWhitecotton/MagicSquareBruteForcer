#pragma once
#include <string>

//stores the commandline arguments
struct Args {
	std::string outpuDir = "c:/";
	int size = 0;
	int max = 0;
	int min = 0;
	int progressReportFrequency = 100;
	int threadCount = 1;
	bool compactOutput = false;
	bool outputIdentical = false;

	Args(int argc, char* argv[]);
	Args(int size, int max, int min, bool comp, bool identical, int threads);

	bool checkArgRanges();
};
