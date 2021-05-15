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
#include <unistd.h>

using namespace std;

/*BFS CONST*/
#define WHITE -1
#define GRAY 0
#define BLACK 1
#define INF 10000

typedef struct{
    int cap;
    int flux;
    int id;
} edge;

typedef struct{
    vector<edge> edges;
    //BFS
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

    graph = vector<vertex>(n+2);
    residual = vector<vertex>(n+2);
    int x, y;

    for (int i = 1; i <= n; ++i){
        if (scanf("%d %d", &x, &y) < 0){
            cout << "Vertice invalido. Tente de novo!" << endl;
            exit(EXIT_FAILURE);
        }

        /**
         * Vertices:
         * x -> custo de executar no processador X
         * y -> custo de executar no processador Y
         * Arestas:
         * eX1-> custo de x(processo) -> X(processador)        eY1-> custo de y(processo) -> Y(processador)                     
         * eX2-> custo de X(processador) -> x(processo)        eY2-> custo de Y(processador) -> y(processo) 
         * rX1->                                               rY1->                           
         * rX2->                                               rY2->
         */


        edge eX1, eX2, eY1, eY2, rX1, rX2, rY1, rY2;

        eX1.cap = x; eX2.cap = x; rX1.cap = x; rX2.cap = x;
        eX1.flux = 0; eX2.flux = 0; rX1.flux = x; rX2.flux = x;
        eX1.id = 0; eX2.id = i; rX1.id = 0; rX2.id = i;
        
        eY1.cap = y; eY2.cap = y; rY1.cap = y; rY2.cap = y;
        eY1.flux = 0; eY2.flux = 0; rY1.flux = y; rY2.flux = y;
        eY1.id = n+1; eY2.id = i; rY1.id = n+1; rY2.id = i;
        
        graph[i].edges.push_back(eX1);
        graph[0].edges.push_back(eX2);
        graph[i].edges.push_back(eY1);
        graph[n+1].edges.push_back(eY2);

        residual[i].edges.push_back(rX1);
        residual[0].edges.push_back(rX2);
        residual[i].edges.push_back(rY1);
        residual[n+1].edges.push_back(rY2);
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

        e1.cap = c; e2.cap = c; r1.cap = c; r2.cap = c;
        e1.flux = 0; e2.flux = 0; r1.flux = c; r1.flux = c;
        e1.id = v; e2.id = u; r1.id = v; r2.id = u;

        graph[u].edges.push_back(e1);
        graph[v].edges.push_back(e2);

        residual[u].edges.push_back(r1);
        residual[v].edges.push_back(r2);
    }
}

void BFS(int s){
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
        for(unsigned int i = 0; i < residual[w].edges.size(); ++i){
            int id = residual[w].edges[i].id;
            if(residual[w].edges[i].flux > 0 && residual[id].colour == WHITE){
                Q.push(id);
                residual[id].colour = GRAY;
                residual[id].parent = w;
            }
        }
        residual[w].colour = BLACK;
    }
}

stack<int> findPath(int s){
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
    int min = INF;
    while(path.size() > 1){
        int cur = path.top();
        path.pop();
        int next = path.top();
        int next_index = -1;
        for (unsigned int i = 0; i < residual[cur].edges.size(); ++i){
            if (residual[cur].edges[i].id == next){
                next_index = i;
                break;
            }
        }
        if (next_index >= 0 && min > residual[cur].edges[next_index].flux){
            min = residual[cur].edges[next_index].flux;
        }
    }
    return min;
}


void EdmondsKarp(){
    stack<int> path;
    int min, cur, next, cur_index = -1, next_index = -1;
    while((path = findPath(0)).size() > 1){
        min = calculateMinAugPath(path);
        while(path.size() > 1){
            cur = path.top();
            path.pop();
            next = path.top();
            for (unsigned int i = 0; i < residual[cur].edges.size(); ++i){
                if (residual[cur].edges[i].id == next){
                    next_index = i;
                    break;
                }
            }
            for (unsigned int i = 0; i < residual[next].edges.size(); ++i){
                if (residual[next].edges[i].id == cur){
                    cur_index = i;
                    break;
                }
            }
            if (cur_index >= 0 && next_index >= 0){
                graph[cur].edges[next_index].flux += min;
                residual[cur].edges[next_index].flux -= min;
                graph[next].edges[cur_index].flux += min;
                residual[next].edges[cur_index].flux -= min;
            }
        }
    }
}

int findMaxFlux(int s){
    int total = 0;
    for (unsigned int i = 0; i < graph[s].edges.size(); ++i){
        total += graph[s].edges[i].flux;
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
        cout << i << " -> ";
        for(unsigned int j = 0; j < g[i].edges.size(); ++j){
            cout << "(" << g[i].edges[j].id << ", " << g[i].edges[j].flux << ", " << g[i].edges[j].cap << ") ";
        }
        cout << endl;
    }
}

void printStack(stack<int> st){
    stack<int> s = st;
    while(!s.empty()){
        cout << s.top() << ",";
        s.pop();
    }
    cout << endl;
}