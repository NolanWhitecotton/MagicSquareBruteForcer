cmake_minimum_required(VERSION 3.10)

# set the project name
project(msbf)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

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
	"src/Validators.cpp" "src/Validators.h"
)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
