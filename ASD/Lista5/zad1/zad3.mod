/* MAXFLOW, Maximum Flow Problem */

/* The Maximum Flow Problem in a network G = (V, E), where V is a set
   of nodes, E within V x V is a set of arcs, is to maximize the flow
   from one given node s (source) to another given node t (sink) subject
   to conservation of flow constraints at each node and flow capacities
   on each arc. */

param n, integer, >= 2;
/* number of nodes */

set V, default {1..n};
/* set of nodes */

set E, within V cross V;
/* set of arcs */

param a{(i,j) in E}, > 0;
/* a[i,j] is capacity of arc (i,j) */

param s, symbolic, in V, default 1;
/* source node */

param t, symbolic, in V, != s, default n;
/* sink node */

var x{(i,j) in E}, >= 0, <= a[i,j];
/* x[i,j] is elementary flow through arc (i,j) to be found */

var flow, >= 0;
/* total flow from s to t */

s.t. node{i in V}:
/* node[i] is conservation constraint for node i */

   sum{(j,i) in E} x[j,i] + (if i = s then flow)
   /* summary flow into node i through all ingoing arcs */

   = /* must be equal to */

   sum{(i,j) in E} x[i,j] + (if i = t then flow);
   /* summary flow from node i through all outgoing arcs */

maximize obj: flow;
/* objective is to maximize the total flow through the network */

solve;

printf{1..56} "="; printf "\n";
printf "Maximum flow from node %s to node %s is %g\n\n", s, t, flow;
printf "Starting node   Ending node   Arc capacity   Flow in arc\n";
printf "-------------   -----------   ------------   -----------\n";
printf{(i,j) in E: x[i,j] != 0}: "%13s   %11s   %12g   %11g\n", i, j,
   a[i,j], x[i,j];
printf{1..56} "="; printf "\n";

data;


/* Optimal solution PASTE data.txt */

param n := 4;
param : E :   a :=
1 1	2
1 2	2
1 3	2
1 4	5
2 1	2
2 2	2
2 3	2
2 4	5
3 1	2
3 2	2
3 3	2
3 4	5
4 1	5
4 2	5
4 3	5
4 4	5
;

/* END PASTE */

end;
