zad1: main.o PriorityQueue.o Heap.o Element.o
	g++ -o zad1 main.o PriorityQueue.o Heap.o Element.o

main.o: main.cpp PriorityQueue.h Heap.h Element.h
	g++ -c main.cpp -Wall -pedantic

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h Heap.h Element.h
	g++ -c PriorityQueue.cpp -Wall -pedantic

Heap.o: Heap.cpp Heap.h Element.h
	g++ -c Heap.cpp -Wall -pedantic

Element.o: Element.cpp Element.h
	g++ -c Element.cpp -Wall -pedantic

clean:
	rm -f *.o zad1
