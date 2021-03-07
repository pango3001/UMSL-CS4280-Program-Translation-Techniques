CXX = g++
FLAGS = -std=c++0x -Wall -g

P0: main.o scanner.o
	$(CXX) $(FLAGS) -o P0 main.o scanner.o
	
main.o: main.cpp
	$(CXX) $(FLAGS) -c main.cpp

scanner.o: tree.cpp scanner.h token.h
	$(CXX) $(FLAGS) -c scanner.cpp
	
clean:
	rm -f P1 *.temp *.o 