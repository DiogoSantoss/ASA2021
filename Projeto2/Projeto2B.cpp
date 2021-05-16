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
#include <unistd.h>
#include <algorithm>

using namespace std;

/*BFS CONST*/
#define WHITE -1
#define GREY 0
#define BLACK 1
#define INF 1000

// Each vertex has an array of edges and necessary params for BFS
typedef struct{
    vector<int> edges;
    int parent;
    int size;
} vertex;

//Residual Graph
vector<vertex> residual;
int** fluxes; 
int n;

void readInput(){
    /**
     * Reads input from stdin and initialises the correspondent graph
    */
    int k;
    scanf("%d %d", &n, &k);

    residual = vector<vertex>(n+2);
    fluxes = (int**)malloc(sizeof(int*)*(n+2));
    for(int i = 0; i < n+2; ++i){
        fluxes[i]=(int*)calloc(n+2, sizeof(int));
    }

    int x, y;
    for (int i = 1; i <= n; ++i){
        scanf("%d %d", &x, &y);

        residual[0].edges.push_back(i);     //Aresta do processador X para processo i
        residual[i].edges.push_back(n+1);   //Aresta do processo i para processador Y
        fluxes[0][i] = x;
        fluxes[i][n+1] = y;
    }
    
    int u, v, c;
    for (int i = 0; i < k; ++i){
        scanf("%d %d %d", &u, &v, &c);
        residual[u].edges.push_back(v);  //Aresta do processo u para o processo v
        residual[v].edges.push_back(u);  //Aresta do processo v para o processo u
        fluxes[u][v] = c;
        fluxes[v][u] = c;
    }
}

int BFS(int s, int t){
    /**
     * Breadth-First Search
     */
    for(unsigned int i = 0; i < residual.size(); ++i){
        residual[i].parent = -1;
        residual[i].size = 0;
    }
    residual[s].size = 1;

    queue<int> Q;
    Q.push(s);
    
    while(!Q.empty()){
        int w = Q.front();    
        Q.pop();
        for(unsigned int i = 0; i < residual[w].edges.size(); ++i){
            int id = residual[w].edges[i];                            //index of edge i of w in residual graph
            if(fluxes[w][id] > 0 && residual[id].size == 0){
                residual[id].parent = w;
                residual[id].size = residual[w].size + 1;
                if (id == t){
                    return residual[id].size;
                }
                Q.push(id);
            }
        }
    }
    return 0;
}

int EdmondsKarp(){

    stack<int> path = stack<int>();
    int child, parent, minimum, cur, next, m, size, total = 0;
    while((size = BFS(0,n+1)) > 0){
        int path[n];
        m = size;
        child = residual.size()-1;         // Y
        parent = residual[child].parent;
        minimum = INF;

        while (parent >= 0){                   
            minimum = min(minimum,fluxes[parent][child]);
            path[--m] = child;                 
            child = parent;
            parent = residual[child].parent;
        }

        path[--m] = 0;
        total += minimum;

        for (int i = 0; i < size-1;){
            cur = path[i];
            next = path[++i];
            fluxes[cur][next] -= minimum;
            if (cur != 0 && next != n+1)
                fluxes[next][cur] -= minimum;
        }
    }
    return total;
}

/*************************************************************************************************************************************/
/*                                                             MAIN                                                                  */
/*************************************************************************************************************************************/

int main(){
    readInput();
    //printGraph(graph);
    //printGraph(residual);
    cout << EdmondsKarp() << endl;
    for(int i = 0; i < n+2; ++i){
        free(fluxes[i]);
    }
    free(fluxes);
    exit(EXIT_SUCCESS);  
}