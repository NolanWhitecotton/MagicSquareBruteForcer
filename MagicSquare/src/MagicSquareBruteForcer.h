#pragma once

//std includes
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <vector>
#include "time.h"

//class includes
#include "SquareTemplate.h"
#include "Square.h"

//read the arguments and store them in the given variables
void readArgs(int argc, char  *argv[], int *size, int *max,
    int *min, int *progress,
    bool *compact, bool *identical,
    std::string *output);

/// <summary>
/// return if a value is within a range
/// </summary>
/// <param name="input">the input to test</param>
/// <param name="min">the maximum value for input</param>
/// <param name="max">the minimum value for input</param>
/// <returns></returns>
bool inRange(int input, int min, int max);

/// <summary>
/// prints a formatted version of a vector
/// </summary>
/// <param name="s">the vector to print</param>
void print_vector(const std::vector<std::string>& s);
