msbf.exe: MagicSquareHeader.h MagicSquare.cpp Square.cpp
	g++ -std=c++11 -Wall -Wextra -pedantic -o msbf.exe MagicSquare.cpp Square.cpp

clean:
	rm *.exe