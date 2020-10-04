msbf.exe: MagicSquareHeader.h MagicSquare.cpp Square.cpp ArgReader.cpp
	g++ -std=c++11 -Wall -Wextra -pedantic -o msbf.exe MagicSquare.cpp Square.cpp ArgReader.cpp

clean:
	rm *.exe