
zad2: main.o MyGraph.o
	g++ -o zad2 main.o MyGraph.o

Main.o: main.cpp MyGraph.h
	g++ -c main.cpp -Wall -pedantic

MyGraph.o: MyGraph.cpp MyGraph.h
	g++ -c MyGraph.cpp -Wall -pedantic

clean:
	rm -f *.o zad2
