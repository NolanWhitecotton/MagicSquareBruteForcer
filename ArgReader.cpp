#include "MagicSquareBruteForcer.h"

ArgReader::ArgReader(int argc, char** argv) {
	m_argc = argc;
	m_argv = argv;
	m_curArg = 0;
	m_parseArgs();
}

void ArgReader::m_parseArgs() {
	for (int i = 1; i < m_argc; i++) {
		if (m_argv[i][0] == '-') {
			argPositions.push_back(i);
		}
	}
}

bool ArgReader::hasMoreArgs() {
	return getCurrentArgNum() < (int)argPositions.size();
}

void ArgReader::next(std::vector<std::string> &s) {
	//get the number of options following curArg
	int optCount = getCurrentArgNum() < (int)argPositions.size() - 1 ?
		argPositions[getCurrentArgNum() + 1]- argPositions[getCurrentArgNum()] :
		m_argc - argPositions[getCurrentArgNum()];

	//add arguments to v
	for (int i = 0; i < optCount; i++) {
		s.push_back(m_argv[argPositions[getCurrentArgNum()] + i]);
	}

	//inc curArg
	m_curArg++;
}

int ArgReader::getArgumentCount() {
	return argPositions.size();
}

int ArgReader::getCurrentArgNum() {
	return m_curArg;
}
