    #include "MyGraph.h"
    #include <iostream>
    #include <queue>
    #include <algorithm>

    int HammingCode::errorCorrection(int x){
		    std::string binary = "";
		    int numberOfZeros = 0;
		    int numberOfOnes = 0;
		    int temp;

		    if(x == 0 || x == 1)
			     return 1;

		    while(x > 0) {
			     temp = x % 2;
			     if(temp == 1)
				       numberOfOnes++;
			     else
				       numberOfZeros++;

			     binary += std::to_string(temp);
			     x = x / 2;
		     }

		     if(numberOfOnes >= numberOfZeros) {
			        return numberOfOnes;
		     }
		     else {
			        return numberOfZeros;
		     }
	  }

    MyGraph::MyGraph(int numOfVertices, int numOfEdges) {
        n = numOfVertices;
        m = numOfEdges;

        flow = new long * [n];
        capacity = new long * [n];
        parent = new int[n];
        visited = new bool[n];
        for (int x = 0; x < n; x++){
          flow[x] = new long [n];
          capacity[x] = new long [n];
        }
    }

    MyGraph::~MyGraph(){
        for (int x = 0; x < n; x++){
          delete flow[x];
          delete capacity[x];
        }
        delete [] flow;
        delete [] capacity;
        delete [] parent;
        delete [] visited;
    }

    void MyGraph::addEdge(int from, int to, long cap) {
        if (cap >= 0)
          capacity[from][to] += cap;
    }

    /**
     * Get maximum flow.
     *
     * @param s source
     * @param t target
     * @return maximum flow
     */
  long MyGraph::getMaxFlow(int s, int t) {
        while (true) {
            std::queue <int> Q;
            Q.push(s);

            for (int i = 0; i < n; ++i)
                visited[i] = false;
            visited[s] = true;

            bool check = false;
            int current;
            while (!Q.empty()) {
                current = Q.front();
                if (current == t) {
                    check = true;
                    break;
                }
                Q.pop();
                for (int i = 0; i < n; ++i) {
                    if (!visited[i] && capacity[current][i] > flow[current][i]) {
                        visited[i] = true;
                        Q.push(i);
                        parent[i] = current;
                    }
                }
            }
            if (check == false)
                break;

            long temp = capacity[parent[t]][t] - flow[parent[t]][t];
            for (int i = t; i != s; i = parent[i])
                temp = std::min(temp, (capacity[parent[i]][i] - flow[parent[i]][i]));

            for (int i = t; i != s; i = parent[i]) {
                flow[parent[i]][i] += temp;
                flow[i][parent[i]] -= temp;
            }
        }

        long result = 0;
        for (int i = 0; i < n; ++i)
            result += flow[s][i];
        return result;
    }

    void MyGraph::showGraph(int numOfVerticles){

		std::cout << "param n := " << numOfVerticles << ";" << std::endl;
		//bw.write("param n := " + numOfVerticles + ";");
		//bw.newLine();
		std::cout << "param : E :   a :=" << std::endl;
		//bw.write("param : E :   a :=");
		//bw.newLine();
		for(int i = 0; i < numOfVerticles; i++) {
			for(int j = 0; j < numOfVerticles; j++) {
				 std::cout << (i+1) << " " << (j+1) << "\t" << capacity[i][j] << std::endl;
				//bw.write((i+1) +" " + (j+1) + "    " + capacity[i][j]);
				//bw.newLine();
			}
		}
		std::cout << ";" << std::endl;
		//bw.write(";");
		//bw.newLine();
		//bw.close();
}
