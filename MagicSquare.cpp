#include "MagicSquareHeader.h"

int main(int argc, char *argv[]) {
    //get args
    int size = 0, max = 0,
        min = 1, progress = 0;
    bool compact = false, identical = false;
    std::string output = "";
    
    //read args
    readArgs(argc, argv, &size, &max, 
        &min, &progress, 
        &compact, &identical, 
        &output);

    //calc squares
    Square sq = Square(size);

    sq.setMinimized(compact);
    sq.setRecurRange(min, max);

    sq.checkNextRecur();
}

int convert2dtoLinear(int x, int y, int size) {return x * size + y;}
int getLinearX(int pos, int size) {return pos / size;}
int getLinearY(int pos, int size) {return pos % size;}

//determines the format the square is printed
void Square::setMinimized(bool minimized) {
    isMinimized = minimized;
}

void readArgs(int argc, char* argv[], int* size, int* max,
    int* min, int* progress,
    bool* compact, bool* identical,
    std::string* output) {

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        //max
        if (arg == "-m" || arg == "--max") {
            *max = std::stoi(argv[i + 1]);
            i++;//TODO make this not horrible
        }else

        //size
        if (arg == "-s" || arg == "--size") {
            *size = std::stoi(argv[i + 1]);
            i++;//TODO make this not horrible
        }else

        //min
        if (arg == "-n" || arg == "--min") {
            *min = std::stoi(argv[i + 1]);
            i++;//TODO make this not horrible
        }else

        //output
        if (arg == "-o" || arg == "--output") {
            *output = ""; //TODO output file
        }else

        //progress
        if (arg == "-p" || arg == "--progress") {
            *progress = 1; //TODO progress, with optional next
        } else

        //flags
        if (arg[0] == '-') {
            for (int o = 1; o < arg.length(); o++) {
                if (arg[o] == 'c') {
                    *compact = true;
                } else if (arg[o] == 'i'){
                    *identical = true;
                }else{
                    std::cout << "Unknown flag '" << arg[o] << "'" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        } else {
            std::cout << "Unknown argument '" << arg << "'" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    //check bounds on args
    if (*size <= 0) {
        std::cout << "invalid size: " << *size << std::endl;
        exit(EXIT_FAILURE);
    }
    if (*max <= 0) {
        std::cout << "invalid max: " << *max << std::endl;
        exit(EXIT_FAILURE);
    }
    if (min >= max) {
        std::cout << "max must be greater than min" << std::endl;
        exit(EXIT_FAILURE);
    }
}
