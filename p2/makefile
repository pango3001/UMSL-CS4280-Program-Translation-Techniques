CXX = g++
CXXFLAGS = -std=c++0x -Wall -g

frontEnd: main.cpp scanner.cpp testScanner.cpp
	$(CXX) $(CXXFLAGS) -o frontEnd main.cpp testScanner.cpp scanner.cpp
	
clean:
	rm -f scanner *.o stdin.temp