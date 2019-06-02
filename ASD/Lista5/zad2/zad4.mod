param n, integer, >= 2; /*liczba wierzchołków */

/*zbiór wierzchołków V i zbiów krawędzi E*/

set V, default {0..n};

set E, within V cross V;

/*parametr selekcjonujący krawędzie*/
param w{(i,j) in E} > 0;

var a{(i,j) in E}, >= 0;

var m, >=0;

maximize match: sum{(i,j) in E} a[i,j];


/* gdy krawędź należy do skoajarzenia ma wartość 1 w przeciwnym przypadku 0
 wierzchołek może być końcem co najwyzej jednej krawędzi należącej do skojarzenia więc suma dla wszystkich krawędzi których jest końcem może być co najwyżej równa 1*/
s.t. node{i in V}:
		sum{(j,i) in E} a[j,i] + sum{(i,j) in E} a[i,j] <= 1;

solve;
	
	printf{0..56} "="; printf "\n";
	printf "Maximum bipartite matching: %g\n", match;
	printf{0..56} "="; printf "\n";

data;

/* wklejony kod */
param n := 31;
param : E : w :=
0 9 1
0 10 1
1 11 1
1 14 1
2 6 1
2 12 1
3 10 1
3 14 1
4 1 1
4 9 1
5 1 1
5 13 1
6 4 1
6 13 1
7 1 1
7 11 1
8 2 1
8 15 1
9 6 1
9 15 1
10 0 1
10 4 1
11 9 1
11 12 1
12 11 1
12 15 1
13 9 1
13 14 1
14 4 1
14 10 1
15 11 1
15 14 1
;
end;
