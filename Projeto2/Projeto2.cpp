/**
 * Ficheiro: Projeto1.cpp
 * Realizado por: David Belchior (95550) e Diogo Santos (95562)
 * Instituto Superior Tecnico - LEIC-A - Analise e Sintese de Algoritmos
 * Para compilar: g++ -std=c++11 -O3 -Wall Projeto2.cpp -lm
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <string.h>

using namespace std;

typedef struct{
    int flux;
    int id;
    int revEdgeIndex;
} edge;

//Residual Graph
vector<vector<edge>> residual;

//Global Single Variables
int n, s, t;

//Secondary Arrays
int* parents;
int* visited;
int* parentEdges;

void readInput(){
    /**
     * Reads input from stdin and initialises the correspondent graph
    */
    int k;
    scanf("%d %d", &n, &k);

    s = 0; t = n+1;

    residual = vector<vector<edge>>(n+1);
    parentEdges = new int[n+2];
    parents = new int[n+2];
    visited = new int[n+1];

    int x, y;
    for (int i = 1; i <= n; ++i){
        scanf("%d %d", &x, &y);
 
        edge rX2, rY1;

        rX2.flux = x;   rY1.flux = y;
        rX2.id = i;     rY1.id = n+1;
        
        residual[0].push_back(rX2);   //Aresta do processador X para processo i
        residual[i].push_back(rY1);   //Aresta do processo i para processador Y
    }
    
    int u, v, c;
    for (int i = 0; i < k; ++i){
        scanf("%d %d %d", &u, &v, &c);
 
        edge r1, r2;

        r1.flux = c; r2.flux = c;
        r1.id = v;   r2.id = u;
        r1.revEdgeIndex = residual[v].size();
        r2.revEdgeIndex = residual[u].size();


        residual[u].push_back(r1);  //Aresta do processo u para o processo v
        residual[v].push_back(r2);  //Aresta do processo v para o processo u
    }
}

bool BFS(int s, int t){
    /**
     * Breadth-First Search
     */
    memset(visited, 0,(n+1)*sizeof(int));
    memset(parents, -1,(n+2)*sizeof(int));
    memset(parentEdges, -1,(n+2)*sizeof(int));

    visited[s] = true;

    queue<int> Q;
    Q.push(s);
    
    while(!Q.empty()){
        int w = Q.front(); Q.pop();
        for(size_t i = 0; i < residual[w].size(); ++i){
            int id = residual[w][i].id;                           
            if(residual[w][i].flux > 0 && !(visited[id])){
                parents[id] = w;
                parentEdges[id] = i;
                if (id == t)
                    return true;
                Q.push(id);
                visited[id] = true;
            }
        }
    }
    return false;
}

int EdmondsKarp(){

    int u, minimum, parentEdge,nextIndex, total = 0;
    while(BFS(s, t)) {
        minimum = __INT_MAX__;
        for (int v = t; v != s; v = parents[v]){
            parentEdge = parentEdges[v];                          //qual a aresta que leva a v
            u = parents[v];                                       //qual o pai de v
            minimum = min(minimum,residual[u][parentEdge].flux);  //aresta de u para v
        }
        for (int v = t; v != s; v = parents[v]){
            parentEdge = parentEdges[v];
            u = parents[v];
            residual[u][parentEdge].flux -= minimum;
            nextIndex = residual[u][parentEdge].revEdgeIndex;
            if(u != s && v != t)
                residual[v][nextIndex].flux += minimum;
        }
        total += minimum;
    }
    return total;
}

/*************************************************************************************************************************************/
/*                                                             MAIN                                                                  */
/*************************************************************************************************************************************/

int main(){
    readInput();
    cout << EdmondsKarp() << endl;
    exit(EXIT_SUCCESS);  
}