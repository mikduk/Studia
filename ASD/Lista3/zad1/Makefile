zad1: main.o Heap.o Element.o
	g++ -o zad1 main.o Heap.o Element.o

main.o: main.cpp Element.h
	g++ -c main.cpp -Wall -ansi -pedantic 

Heap.o: Heap.cpp Heap.h Element.h
	g++ -c Heap.cpp -Wall -ansi -pedantic

Element.o: Element.cpp Element.h
	g++ -c Element.cpp -Wall -ansi -pedantic

clean:
	rm -f *.o zad1
