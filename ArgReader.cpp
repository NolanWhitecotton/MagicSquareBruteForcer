#include "MagicSquareHeader.h"

ArgReader::ArgReader(int argc, char** argv) {
	this->argc = argc;
	this->argv = argv;
	this->curArg = 0;
	this->parseArgs();
}

void ArgReader::parseArgs() {
	for (int i = 1; i < this->argc; i++) {
		if (this->argv[i][0] == '-') {
			this->argPositions.push_back(i);
		}
	}
}

bool ArgReader::hasMoreArgs() {
	return curArg < argPositions.size();
}

void ArgReader::next(std::vector<std::string> &s) {
	//get the number of options following curArg
	int optCount = curArg < argPositions.size() - 1 ?
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
	return this->argPositions.size();
}

int ArgReader::getCurrentArgNum() {
	return curArg;
}
