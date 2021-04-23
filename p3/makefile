CXX = g++
CXXFLAGS = -std=c++0x -Wall -g -w

P2: main.cpp scanner.cpp parser.cpp
	$(CXX) $(CXXFLAGS) -o statSem main.cpp parser.cpp scanner.cpp semantics.cpp

clean:
	rm -f statSem *.o stdin.temp keyboard_input.txt