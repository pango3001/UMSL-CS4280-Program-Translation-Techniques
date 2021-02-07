CXX = g++
FLAGS = -g -Wall

P0: main.o tree.o
	$(CXX) $(FLAGS) -o P0 main.o tree.o
	
main.o: main.cpp
	$(CXX) $(FLAGS) -c main.cpp

tree.o: tree.cpp tree.h node.h
	$(CXX) $(FLAGS) -c tree.cpp
	
clean:
	rm -f P0 *.o *.inorder *.preorder *.postorder temp.txtvi