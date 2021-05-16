/**
 * Ficheiro: Projeto1.cpp
 * Realizado por: David Belchior (95550) e Diogo Santos (95562)
 * Instituto Superior Tecnico - LEIC-A - Analise e Sintese de Algoritmos
 * Para compilar: g++ -std=c++11 -O3 -Wall proj.cpp -lm
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>

using namespace std;

/*BFS CONST*/
#define WHITE -1
#define GRAY 0
#define BLACK 1
#define INF 10000

// Each edge has a capacity, a flux and an id (position in original graph)
typedef struct{
    int cap;
    int flux;
} edge;

// Each vertex has an array of edges and necessary params for BFS
typedef struct{
    map<int,edge> edges;
    int parent;
    int colour;
} vertex;

vector<vertex> graph;
vector<vertex> residual;

void printGraph(vector<vertex> g);
void printStack(stack<int> s);

void readInput(){
    /**
     * Reads input from stdin and initialises the correspondent graph
    */
    int n, k;
    if (scanf("%d %d", &n, &k) < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }
    if (n < 2 || k < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }

    // Creates graph and residual graph
    graph = vector<vertex>(n+2);
    residual = vector<vertex>(n+2);

    int x, y;
    for (int i = 1; i <= n; ++i){
        if (scanf("%d %d", &x, &y) < 0){
            cout << "Vertice invalido. Tente de novo!" << endl;
            exit(EXIT_FAILURE);
        }

        edge eX1, eX2, eY1, eY2, rX1, rX2, rY1, rY2;

        eX1.cap = x;  eX2.cap = x;  rX1.cap = x;  rX2.cap = x;
        eX1.flux = 0; eX2.flux = 0; rX1.flux = x; rX2.flux = x;
        
        eY1.cap = y;  eY2.cap = y;  rY1.cap = y;  rY2.cap = y;
        eY1.flux = 0; eY2.flux = 0; rY1.flux = y; rY2.flux = y;

        graph[i].edges[0] = eX1;      //Aresta do processo i para processador X
        graph[0].edges[i] = eX2;      //Aresta do processador X para processo i
        graph[i].edges[n+1] = eY1;    //Aresta do processo i para processador Y
        graph[n+1].edges[i] = eY2;    //Aresta do processador Y para processo i

        residual[i].edges[0] = rX1;
        residual[0].edges[i] = rX2;
        residual[i].edges[n+1] = rY1;
        residual[n+1].edges[i] = rY2;
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

        edge e1, e2, r1, r2;

        e1.cap = c;  e2.cap = c;  r1.cap = c;  r2.cap = c;
        e1.flux = 0; e2.flux = 0; r1.flux = c; r2.flux = c;


        graph[u].edges[v] = e1; //Aresta do processo u para processo v
        graph[v].edges[u] = e2; //Aresta do processo v para processo u

        residual[u].edges[v] = r1;
        residual[v].edges[u] = r2;
    }
}

void BFS(int s){
    /**
     * Breadth-First Search
     */
    for(unsigned int i = 0; i < residual.size(); ++i){
        residual[i].parent = -1;
        residual[i].colour = WHITE;
    }
    residual[s].colour = GRAY;

    queue<int> Q;
    Q.push(s);
    
    while(!Q.empty()){
        int w = Q.front();    
        Q.pop();

        map<int,edge>::iterator itr;
        for(itr=residual[w].edges.begin(); itr !=residual[w].edges.end(); ++itr){
            int id = itr->first;
            if(residual[w].edges[id].flux > 0 && residual[id].colour == WHITE){
                Q.push(id);
                residual[id].colour = GRAY;
                residual[id].parent = w;
            }
        }
        residual[w].colour = BLACK;
    }
}

stack<int> findPath(int s){
    /**
     * Finds shortest path from X to Y
     */
    BFS(s);

    stack<int> path = stack<int>();
    int child = residual.size()-1;
    int parent = residual[child].parent;
    while (true){
        path.push(child);
        child = parent;
        if (child != -1)
            parent = residual[child].parent;
        else
            break;
    }
    return path;
}

int calculateMinAugPath(stack<int> path){
    /**
     * Finds minimal augmentating flux in the shortest path
     */
    int min = INF;
    while(path.size() > 1){
        int cur = path.top();
        path.pop();
        int next = path.top();
        
        if (min > residual[cur].edges[next].flux){
            min = residual[cur].edges[next].flux;
        }
    }
    return min;
}


void EdmondsKarp(){

    stack<int> path;
    int min, cur, next;
    while((path = findPath(0)).size() > 1){

        //printStack(path);

        min = calculateMinAugPath(path);
        while(path.size() > 1){
            cur = path.top();
            path.pop();
            next = path.top();

            graph[cur].edges[next].flux += min;
            residual[cur].edges[next].flux -= min;
            graph[next].edges[cur].flux += min;
            residual[next].edges[cur].flux -= min;
        }
        //printGraph(graph);
        //printGraph(residual);
    }
}

int findMaxFlux(int s){
    /**
     * MaxFlux is equal to the sum of flux coming out of X
     */
    int total = 0;
    map<int,edge>::iterator itr;
    for(itr=graph[s].edges.begin(); itr !=graph[s].edges.end(); ++itr){
        total += itr->second.flux;
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
    EdmondsKarp();
    //printGraph(graph);
    //printGraph(residual);
    cout << findMaxFlux(0) << endl;

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
        map<int,edge>::iterator itr;
        for(itr=g[i].edges.begin(); itr !=g[i].edges.end(); ++itr){
            cout << "(" << itr->first << ", " << itr->second.flux << ", " << itr->second.cap << ") ";
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