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
#include <unistd.h>

using namespace std;

/*BFS CONST*/
#define WHITE -1
#define GREY 0
#define BLACK 1
#define INF 10000

// Each edge has a flux and an id (position in original graph)
typedef struct{
    int flux;
    int id;
} edge;

// Each vertex has an array of edges and necessary params for BFS
typedef struct{
    vector<edge> edges;
    int parentEdge;
} vertex;

//Residual Graph
vector<vertex> residual;
int* parents;
int* parentEdges;
int* visited;
int n;

void printGraph(vector<vertex> g);
void printStack(stack<int> s);

void readInput(){
    /**
     * Reads input from stdin and initialises the correspondent graph
    */
    int k;
    scanf("%d %d", &n, &k);

    residual = vector<vertex>(n+2);
    parents = (int*)malloc(sizeof(int)*(n+2));
    parentEdges = (int*)malloc(sizeof(int)*(n+2));
    visited = (int*)malloc(sizeof(int)*(n+2));

    int x, y;
    for (int i = 1; i <= n; ++i){
        scanf("%d %d", &x, &y);

        edge rX1, rX2, rY1, rY2;

        rX1.flux = x;   rX2.flux = x;
        rX1.id = 0;     rX2.id = i;
        
        rY1.flux = y;   rY2.flux = y;
        rY1.id = n+1;   rY2.id = i;

        residual[i].edges.push_back(rX1);   //Aresta do processo i para processador X
        residual[0].edges.push_back(rX2);   //Aresta do processador X para processo i
        residual[i].edges.push_back(rY1);   //Aresta do processo i para processador Y
        residual[n+1].edges.push_back(rY2); //Aresta do processador Y para processo i
    }
    
    int u, v, c;
    for (int i = 0; i < k; ++i){
        scanf("%d %d %d", &u, &v, &c);

        edge r1, r2;

        r1.flux = c; r2.flux = c;
        r1.id = v;   r2.id = u;

        residual[u].edges.push_back(r1);  //Aresta do processo u para o processo v
        residual[v].edges.push_back(r2);  //Aresta do processo v para o processo u
    }
}

int findIndex(vector<edge> v, int x){
    /**
     * Finds the index of x in the vector v
     */
    for (unsigned int i = 0; i < v.size(); ++i){
        if (v[i].id == x){
            return i;
        }
    }
    return -1;
}

bool BFS(int s, int t){
    /**
     * Breadth-First Search
     */
    memset(visited, 0,(n+2)*sizeof(int));
    memset(parents, -1,(n+2)*sizeof(int));
    memset(parentEdges, -1,(n+2)*sizeof(int));
    visited[s] = true;

    queue<int> Q;
    Q.push(s);
    
    while(!Q.empty()){
        int w = Q.front();    
        Q.pop();
        for(unsigned int i = 0; i < residual[w].edges.size(); ++i){
            int id = residual[w].edges[i].id;
            if(residual[w].edges[i].flux > 0 && !(visited[id])){
                parents[id] = w;
                parentEdges[id] = i;
                if (id == t){
                    return true;                
                }
                visited[id] = true;
                Q.push(id);
            }
        }
    }
    return false;
}

int EdmondsKarp(){

    stack<int> path = stack<int>();
    int child, parent, parentEdge, minimum, cur, curEdge, next, nextEdge, total = 0;
    while(BFS(0,n+1)){
        child = residual.size()-1;         // Y
        parent = parents[child];
        parentEdge = parentEdges[child];  
        minimum = INF;
        while (parent >= 0){                  
            minimum = min(minimum,residual[parent].edges[parentEdge].flux);
            path.push(child);                 
            child = parent;
            parent = parents[child];
            parentEdge = parentEdges[child];
        }

        path.push(0);
        total += minimum;
        
        while(path.size() > 1){
            cur = path.top();
            path.pop();
            next = path.top();
            nextEdge = parentEdges[next];
            residual[cur].edges[nextEdge].flux -= minimum;
            if ((curEdge = findIndex(residual[next].edges, cur)) >= 0)
                residual[next].edges[curEdge].flux += minimum;
        }
    }
    return total;
}

/*************************************************************************************************************************************/
/*                                                             MAIN                                                                  */
/*************************************************************************************************************************************/

int main(){
    readInput();
    //printGraph(residual);
    cout << EdmondsKarp() << endl;
    free(parents);
    free(parentEdges);
    free(visited);
    exit(EXIT_SUCCESS);  
}

/*************************************************************************************************************************************/
/*                                                             PRINTS                                                                */
/*************************************************************************************************************************************/
void printGraph(vector<vertex> g){
    /**
     * Prints graph
    */
    cout << "Graph:" << endl;
    for(unsigned int i = 0; i < g.size(); ++i){
        cout << i << " _> ";
        for(unsigned int j = 0; j < g[i].edges.size(); ++j){
            cout << "(" << g[i].edges[j].id << ", " << g[i].edges[j].flux << ") ";
        }
        cout << endl;
    }
}

void printStack(stack<int> st){
    /**
     * Prints stack
     */
    stack<int> s = st;
    while(!s.empty()){
        cout << s.top() << ",";
        s.pop();
    }
    cout << endl;
}