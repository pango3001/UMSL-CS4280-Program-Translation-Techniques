CXX = g++
FLAGS = -std=c++0x -Wall -g

P0: main.o tree.o
	$(CXX) $(FLAGS) -o P0 main.o tree.o
	
main.o: main.cpp
	$(CXX) $(FLAGS) -c main.cpp

tree.o: tree.cpp tree.h node.h
	$(CXX) $(FLAGS) -c tree.cpp
	
clean:
	rm -f P0 file.temp *.o *.inorder *.preorder *.postorder 