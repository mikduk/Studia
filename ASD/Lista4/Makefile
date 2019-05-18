list4: Main.o Splay.o RBT.o BST.o Element.o
	g++ -o list4 Main.o Splay.o RBT.o BST.o Element.o

Main.o: Main.cpp Trees.h
	g++ -c Main.cpp -Wall -pedantic

Splay.o: Splay.cpp Trees.h
			g++ -c Splay.cpp -Wall -pedantic

RBT.o: RBT.cpp Trees.h
		g++ -c RBT.cpp -Wall -pedantic

BST.o: BST.cpp Trees.h
		g++ -c BST.cpp -Wall -pedantic

Element.o: Element.cpp Element.h
	g++ -c Element.cpp -Wall -pedantic

clean:
	rm -f *.o list4
