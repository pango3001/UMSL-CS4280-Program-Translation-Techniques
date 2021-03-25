CXX = g++
FLAGS = -std=c++0x -Wall -g

testing: main.o
	$(CXX) $(FLAGS) -o testing main.o
	
main.o: main.cpp
	$(CXX) $(FLAGS) -c main.cpp
	
clean:
	rm -f testing *.temp *.o *.inorder *.preorder *.postorder 