/**
 * Ficheiro: proj.cpp
 * Realizado por: David Belchior (95550) e Diogo Santos (95562)
 * Instituto Superior Tecnico - LEIC-A - Analise e Sintese de Algoritmos
 * Para compilar: g++ -std=c++11 -O3 -Wall proj.cpp -lm
*/

#include <iostream>
#include <vector>
#define WHITE 1
#define GREY 0
#define BLACK -1

using namespace std;

typedef struct{
    int colour;
    vector<int> adj;
} vertex;

vector<vertex> graph;

void initializeGraph(int n){
    graph = vector<vertex>(n);
    for(int i = 0; i<n; i++){
        graph[i].colour = WHITE;
        graph[i].adj = vector<int>();
    }
        
}

void readInput(){
    int n, m;
    if (scanf("%d %d", &n, &m) < 0)
        exit(EXIT_FAILURE);
    if (n < 2 || m < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }

    initializeGraph(n);
    
    int u, v;
    for (int i = 0; i < m; ++i){
        if (scanf("%d %d", &u, &v) < 0)
            exit(EXIT_FAILURE);
        graph[u-1].adj.push_back(v-1);
    }
}

void printGraph(){
    cout << "Graph:" << endl;
    for(unsigned int i = 0; i < graph.size(); i++){
        cout << i+1 << " -> ";
        for(unsigned int j = 0; j < graph[i].adj.size(); j++){
            cout << graph[i].adj[j]+1 << " ";
        }
        cout << endl;
    }
}

void repaintGraph();

void checkIfHighest(){
    //Para cada vertice no grafo, iniciar um conjunto de BFS que esgotem todos os vertices
        //Para cada BFS feita, se o numero de arvores for menor que o minimo atual, substituir esse valor
        //e a profundidade da maior arvore encontrada (usar uma variavel que guarde a profundidade maxima)
        //Ao acabar o conjunto de BFS, repaintGraph() e passar para o proximo vertice inicial
}

int main(){
    readInput();
    printGraph();
    exit(EXIT_SUCCESS);
}