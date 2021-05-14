/**
 * Ficheiro: Projeto1.cpp
 * Realizado por: David Belchior (95550) e Diogo Santos (95562)
 * Instituto Superior Tecnico - LEIC-A - Analise e Sintese de Algoritmos
 * Para compilar: g++ -std=c++11 -O3 -Wall proj.cpp -lm
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct{
    int cost;
    int id;
} edge;

typedef struct{
    vector<edge> edges;
} vertex;

vector<vertex> graph;

void printGraph();

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
    int x, y;

    for (int i = 0; i < n; ++i){
        if (scanf("%d %d", &x, &y) < 0){
            cout << "Vertice invalido. Tente de novo!" << endl;
            exit(EXIT_FAILURE);
        }
        edge eX1, eX2, eY1, eY2;
        eX1.cost = x;
        eX2.cost = x;
        eX1.id = n;
        eX2.id = i;
        eY1.cost = y;
        eY2.cost = y;
        eY1.id = n+1;
        eY2.id = i;
        graph[i].edges.push_back(eX1);
        graph[n].edges.push_back(eX2);
        graph[i].edges.push_back(eY1);
        graph[n+1].edges.push_back(eY2);
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
        edge e1, e2;
        e1.cost = c;
        e2.cost = c;
        e1.id = v-1;
        e2.id = u-1;
        graph[u-1].edges.push_back(e1);
        graph[v-1].edges.push_back(e2);
    }
}

/*************************************************************************************************************************************/
/*                                                             MAIN                                                                  */
/*************************************************************************************************************************************/

int main(){
    readInput();
    printGraph();
    exit(EXIT_SUCCESS);  
}

/*************************************************************************************************************************************/
/*                                                             PRINTS                                                                */
/*************************************************************************************************************************************/
void printGraph(){
    /**
     * Prints graph
    */
    cout << "Graph:" << endl;
    for(unsigned int i = 0; i < graph.size(); ++i){
        cout << i+1 << " -> ";
        for(unsigned int j = 0; j < graph[i].edges.size(); ++j){
            cout << "(" << graph[i].edges[j].id+1 << ", " << graph[i].edges[j].cost << ") ";
        }
        cout << endl;
    }
}