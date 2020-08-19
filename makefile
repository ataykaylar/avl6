all: avlfreq

avlfreq: main.o AVLTree.o
	g++  main.o AVLTree.o -o avlfreq


main.o: main.cpp
	g++ -c main.cpp

AVLTree.o: AVLTree.cpp
	g++ -c AVLTree.cpp

clean: 
	rm -rf *o avlfreq