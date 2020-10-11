msbf.exe: *.h *.cpp
	g++ -std=c++11 -Wall -Wextra -pedantic -o msbf.exe *.cpp

clean:
	rm *.exe
