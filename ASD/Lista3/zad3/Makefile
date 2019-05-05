zad1: main.o ExtendedGraph.o Graph.o PriorityQueue.o Heap.o Element.o
	g++ -o zad3 main.o ExtendedGraph.o Graph.o PriorityQueue.o Heap.o Element.o

main.o: main.cpp ExtendedGraph.h Graph.h PriorityQueue.h Heap.h Element.h
	g++ -c main.cpp -Wall -pedantic

ExtendedGraph.o: ExtendedGraph.cpp ExtendedGraph.h Graph.h PriorityQueue.h Heap.h Element.h
		g++ -c ExtendedGraph.cpp -Wall -pedantic

Graph.o: Graph.cpp Graph.h PriorityQueue.h Heap.h Element.h
	g++ -c Graph.cpp -Wall -pedantic

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h Heap.h Element.h
	g++ -c PriorityQueue.cpp -Wall -pedantic

Heap.o: Heap.cpp Heap.h Element.h
	g++ -c Heap.cpp -Wall -pedantic

Element.o: Element.cpp Element.h
	g++ -c Element.cpp -Wall -pedantic

clean:
	rm -f *.o zad3
