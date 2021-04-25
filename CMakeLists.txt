cmake_minimum_required(VERSION 3.10)

# set the project name
project(msbf)

# add the source files
add_executable(msbf 
	# add the dependencies
	"Dependencies/cxxopts.hpp"
	
	# add src
	"src/MagicSquareBruteForcer.cpp"	
	"src/Args.cpp" "src/Args.h" 
	"src/ThreadManager.cpp" "src/ThreadManager.h"
	"src/Square.cpp" "src/Square.h"
	"src/SquareTemplate.cpp" "src/SquareTemplate.h"
)
