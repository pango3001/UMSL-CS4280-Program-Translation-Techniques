CXX = g++
CXXFLAGS = -std=c++0x -Wall -g

scanner: main.cpp scanner.cpp testScanner.cpp
	$(CXX) $(CXXFLAGS) -o scanner main.cpp testScanner.cpp scanner.cpp
	
clean:
	rm -f P1 *.temp *.o keyboard_input.txt