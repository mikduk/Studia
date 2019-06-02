
zad2: main.o MyGraph.o MyGraphTest.o
	g++ -o zad2 main.o MyGraph.o MyGraphTest.o

Main.o: main.cpp MyGraph.h MyGraphTest.h
	g++ -c main.cpp -Wall -pedantic

MyGraph.o: MyGraph.cpp MyGraph.h
	g++ -c MyGraph.cpp -Wall -pedantic

MyGraphTest.o: MyGraphTest.cpp MyGraphTest.h
	g++ -c MyGraphTest.cpp -Wall -pedantic

clean:
	rm -f *.o zad2
