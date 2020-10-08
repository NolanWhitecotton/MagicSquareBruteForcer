#include "MagicSquareHeader.h"

int main(int argc, char *argv[]) {
    //arg defaults
    int size = 0, max = 0,
        min = 1, progress = 0;
    bool compact = false, identical = false;
    std::string output = "";
    
    //read args
    readArgs(argc, argv, &size, &max, 
        &min, &progress, 
        &compact, &identical, 
        &output);

    //start timer
    time_t start;
    time(&start);

    //calc squares
    SquareManager sqm = SquareManager(compact, size, min, max, identical);
    sqm.startCheck();

    //end timer
    time_t end;
    time(&end);

    //print completion
    int calcTime = std::difftime(end,start);
    std::cout << "done in " << calcTime << " second" << (calcTime==1 ? "" : "s") << "." << std::endl;;
}

int convert2dtoLinear(int x, int y, int size) {return x * size + y;}
int getLinearX(int pos, int size) {return pos / size;}
int getLinearY(int pos, int size) {return pos % size;}

void print_vector(const std::vector<std::string>& s) {
    for (auto it = s.begin(); it != s.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

//read the arguments and store them in variables
void readArgs(int argc, char* argv[], int* size, int* max,
    int* min, int* progress,
    bool* compact, bool* identical,
    std::string* output) {

    ArgReader ar = ArgReader(argc, argv);
    while (ar.hasMoreArgs()) {
        std::vector<std::string> s;
        ar.next(s);

        std::string a = s.at(0);
        int optionCount = s.size();
        if (a == "-m" || a == "--max") {
            if (optionCount == 2) {
                *max = std::stoi(s.at(1));
            } else {
                std::cout << a << " requires 2 arguments." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (a == "-s" || a == "--size") {
            if (optionCount == 2) {
                *size = std::stoi(s.at(1));
            }
            else {
                std::cout << a << " requires 2 arguments." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (a == "-n" || a == "--min") {
            if (optionCount == 2) {
               *min = std::stoi(s.at(1));
            }
            else {
                std::cout << a << " requires 2 arguments." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (a == "-o" || a == "--output") {
            if (optionCount == 2) {
                *output = s.at(1);
            }
            else {
                std::cout << a << " requires 2 arguments." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (a == "-p" || a == "--progress") {
            if (optionCount == 2) {
                *progress = stoi(s.at(1));
            }
            else {
                *progress = 60;
            }
        }
        else if (a == "-i" || a == "--identical") {
            *identical = true;
        }
        else if (a == "-c" || a == "--compact") {
            *compact = true;
        }
        else {
            std::cout << "Unknown argument: " << a << std::endl;
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

int getLineSum(const Square& s, int startR, int startC, int incR, int incC) {
    //check ranges
    if (!(inRange(incR, -1, 1) && inRange(incC, -1, 1) && 
        inRange(startR, 0, s.getSize()-1) && inRange(startC, 0, s.getSize() - 1))) {
        std::cout << "invalid getLineSum ranges";
        exit(EXIT_FAILURE);
    }

    //get sum
    int sum = 0, r = startR, c = startC;
    bool atEnd = false;
    while (!atEnd) {
        //add sum
        int toAdd = s.getNum(r, c);
        if (toAdd == 0) {
            return -1;
        }
        sum += toAdd;

        //check atEnd
        atEnd = (r == s.getSize() - 1 && incR > 0) || //TODO (EF1) allow for this to flag at 0 if nessacary for reverse checking
                (c == s.getSize() - 1 && incC > 0);

        //inc r and c
        r += incR;
        c += incC;
    }
    return sum;
}

bool inRange(int input, int min, int max) {
    return input <= max && input >= min;
}

//get an aproximation for how much of the square is calculated
double Square::getCompletion() const {
    int numC = pow(this->getSize(), 2);
    
    double total = 0;
    for (int i = 1; i <= numC; i++) {
        double port = pow(((double)1 / (getRecurMax())), i);
        total += port;
    }

    double percent = 0;
    
    for (int i = 0; i < numC; i++) {
        double adding = ((double)this->getNum(i) / getRecurMax());
        double port = pow(((double)1 / getRecurMax()), i + 1) / total;
        percent += adding * port;
    }
    return percent*100;
}
