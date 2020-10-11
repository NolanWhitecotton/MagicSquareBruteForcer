#include "MagicSquareBruteForcer.h"

ArgReader::ArgReader(int argc, char** argv) {
	this->argc = argc;
	this->argv = argv;
	curArg = 0;
	parseArgs();
}

void ArgReader::parseArgs() {
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			argPositions.push_back(i);
		}
	}
}

bool ArgReader::hasMoreArgs() {
	return curArg < (int)argPositions.size();
}

void ArgReader::next(std::vector<std::string> &s) {
	//get the number of options following curArg
	int optCount = curArg < (int)argPositions.size() - 1 ?
		argPositions[curArg + 1]- argPositions[curArg] :
		argc - argPositions[curArg];

	//add arguments to v
	for (int i = 0; i < optCount; i++) {
		s.push_back(argv[argPositions[curArg] + i]);
	}

	//inc curArg
	curArg++;
}

int ArgReader::getArgumentCount() {
	return argPositions.size();
}

int ArgReader::getCurrentArgNum() {
	return curArg;
}
