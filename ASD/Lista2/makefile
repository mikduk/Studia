a.out: main.o HeapSort.o QuickSortModyfikacja.o QuickSort.o InsertSort.o SelectSort.o funkcjePomocnicze.o
	g++ main.o HeapSort.o QuickSortModyfikacja.o QuickSort.o InsertSort.o SelectSort.o funkcjePomocnicze.o

main.o: main.cpp algorytmy.h
	g++ -c -Wall -pedantic main.cpp

HeapSort.o: HeapSort.cpp HeapSort.h funkcjePomocnicze.h algorytmy.h
	g++ -c -Wall -pedantic HeapSort.cpp

QuickSortModyfikacja.o: QuickSortModyfikacja.cpp QuickSort.h funkcjePomocnicze.h algorytmy.h
	g++ -c -Wall -pedantic QuickSortModyfikacja.cpp

QuickSort.o: QuickSort.cpp QuickSort.h funkcjePomocnicze.h algorytmy.h
	g++ -c -Wall -pedantic QuickSort.cpp

InsertSort.o: InsertSort.cpp InsertSort.h funkcjePomocnicze.h algorytmy.h
	g++ -c -Wall -pedantic InsertSort.cpp

SelectSort.o: SelectSort.cpp funkcjePomocnicze.h algorytmy.h
	g++ -c -Wall -pedantic SelectSort.cpp

funkcjePomocnicze.o: funkcjePomocnicze.cpp funkcjePomocnicze.h
	g++ -c -Wall -pedantic funkcjePomocnicze.cpp
