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

using namespace std;

/*BFS CONST*/
#define WHITE -1
#define GREY 0
#define BLACK 1
#define INF 10000

// Each vertex has an array of edges and necessary params for BFS
typedef struct{
    vector<int> edges;
    int parent;
    bool visited;
} vertex;

//Residual Graph
vector<vertex> residual;
int ** fluxes; 
int n, s, t;

void printGraph(vector<vertex> g);
void printStack(stack<int> s);

void readInput(){
    /**
     * Reads input from stdin and initialises the correspondent graph
    */
    int k;
    if (scanf("%d %d", &n, &k) < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }
    if (n < 2 || k < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }
    s = 0; t = n+1;
    residual = vector<vertex>(n+2);
    fluxes = new int*[n+2];
    for (int i = 0; i < n+2; ++i){
        fluxes[i]=new int[n+2];
    }

    int x, y;
    for (int i = 1; i <= n; ++i){
        if (scanf("%d %d", &x, &y) < 0){
            cout << "Vertice invalido. Tente de novo!" << endl;
            exit(EXIT_FAILURE);
        }

        residual[s].edges.push_back(i);     //Aresta do processador X para processo i
        residual[i].edges.push_back(s);
        residual[i].edges.push_back(t);   //Aresta do processo i para processador Y
        residual[t].edges.push_back(i);
        fluxes[s][i] = x;
        fluxes[i][t] = y;
    }
    
    int u, v, c;
    for (int i = 0; i < k; ++i){
        if (scanf("%d %d %d", &u, &v, &c) < 0){
            cout << "Vertice invalido. Tente de novo!" << endl;
            exit(EXIT_FAILURE);
        }
        if (u > n || v > n){
            cout << "Vertice invalido. Tente de novo!" << endl;
            exit(EXIT_FAILURE);
        }

        residual[u].edges.push_back(v);  //Aresta do processo u para o processo v
        residual[v].edges.push_back(u);  //Aresta do processo v para o processo u
        fluxes[u][v] = c;
        fluxes[v][u] = c;
    }
}

bool BFS(int s, int t){
    /**
     * Breadth-First Search
     */
    for(size_t i = 0; i < residual.size(); ++i){
        residual[i].parent = -1;
        residual[i].visited = false;
    }
    residual[s].visited = true;

    queue<int> Q;
    Q.push(s);
    
    while(!Q.empty()){
        int w = Q.front(); Q.pop();
        for(size_t i = 0; i < residual[w].edges.size(); ++i){
            int id = residual[w].edges[i];                            //index of edge i of w in residual graph
            if(fluxes[w][id] > 0 && !(residual[id].visited)){
                residual[id].parent = w;
                if (id == t)
                    return true;
                Q.push(id);
                residual[id].visited = true;
            }
        }
    }
    return false;
}

int EdmondsKarp(){

    int u, minimum, total = 0;
    while(BFS(s, t)) {
        minimum = INF;
        for (int v = t; v != s; v = residual[v].parent){
            u = residual[v].parent;
            minimum = min(minimum,fluxes[u][v]);
        }
        for (int v = t; v != s; v = residual[v].parent){
            u = residual[v].parent;
            fluxes[u][v] -= minimum;
            fluxes[v][u] += minimum;
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
    //printGraph(graph);
    //printGraph(residual);
    cout << EdmondsKarp() << endl;
    for(int i = 0; i < n+2; ++i){
        delete[] fluxes[i];
    }
    delete[] fluxes;
    exit(EXIT_SUCCESS);  
}

/*************************************************************************************************************************************/
/*                                                             PRINTS                                                                */
/*************************************************************************************************************************************/

/*void printGraph(vector<vertex> g){
    
      Prints graph

    cout << "Graph:" << endl;
    for(unsigned int i = 0; i < g.size(); ++i){
        cout << i << " _> ";
        for(unsigned int j = 0; j < g[i].edges.size(); ++j){
            cout << "(" << g[i].edges[j].id << ", " << g[i].edges[j].flux << ") ";
        }
        cout << endl;
    }
}*/

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