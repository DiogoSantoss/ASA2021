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
int** fluxes; 
int n;

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

    residual = vector<vertex>(n+2);
    fluxes = (int**)malloc(sizeof(int*)*(n+2));
    for(int i = 0; i < n+2; ++i){
        fluxes[i]=(int*)calloc(n+2, sizeof(int));
    }

    int x, y;
    for (int i = 1; i <= n; ++i){
        if (scanf("%d %d", &x, &y) < 0){
            cout << "Vertice invalido. Tente de novo!" << endl;
            exit(EXIT_FAILURE);
        }

        residual[0].edges.push_back(i);     //Aresta do processador X para processo i
        residual[i].edges.push_back(0);
        residual[i].edges.push_back(n+1);   //Aresta do processo i para processador Y
        residual[n+1].edges.push_back(i);
        fluxes[0][i] = x;
        fluxes[i][0] = x;
        fluxes[i][n+1] = y;
        fluxes[n+1][i] = y;
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
/*
int findIndex(vector<edge> v, int x){
    
      Finds the index of x in the vector v
     
    for (unsigned int i = 0; i < v.size(); ++i){
        if (v[i].id == x){
            return i;
        }
    }
    return -1;
}
*/

bool BFS(int s, int t){
    /**
     * Breadth-First Search
     */
    for(unsigned int i = 0; i < residual.size(); ++i){
        residual[i].parent = -1;
        residual[i].visited = false;
    }
    residual[s].visited = true;

    queue<int> Q;
    Q.push(s);
    
    while(!Q.empty()){
        int w = Q.front();    
        Q.pop();
        for(unsigned int i = 0; i < residual[w].edges.size(); ++i){
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

    stack<int> path = stack<int>();
    int child, parent, minimum, cur, next, total = 0;
    while(BFS(0,n+1)){
        child = residual.size()-1;         // Y
        parent = residual[child].parent; 
        minimum = INF;
        while (parent >= 0){                   
            minimum = min(minimum,fluxes[parent][child]);
            path.push(child);                 
            child = parent;
            parent = residual[child].parent;
        }
        path.push(0);
        total += minimum;
        
        while(path.size() > 1){
            cur = path.top();
            path.pop();
            next = path.top();
            fluxes[cur][next] -= minimum;
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

/*************************************************************************************************************************************/
/*                                                             PRINTS                                                                */
/*************************************************************************************************************************************/


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