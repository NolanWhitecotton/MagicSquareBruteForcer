cmake_minimum_required(VERSION 3.10)

# set the project name
project(msbf CXX)

# add the source files
add_executable(msbf 
	# add the dependencies
	"src/Dependencies/cxxopts.hpp"
	
	# add src
	"src/MagicSquareBruteForcer.cpp"	
	"src/Args.cpp" "src/Args.h" 
	"src/ThreadManager.cpp" "src/ThreadManager.h"
	"src/Square.cpp" "src/Square.h"
	"src/SquareTemplate.cpp" "src/SquareTemplate.h"
	"src/Validators.cpp" "src/Validators.h"
	"src/Ranges.cpp" "src/Ranges.h"
)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(msbf PRIVATE Threads::Threads)
