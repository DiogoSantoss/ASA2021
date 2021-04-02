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
    bool visited;
    int streak = 1;
    int in = 0;
    vector<int> adj;
} vertex;

vector<vertex> graph;

void printGraph();
void printTransGraph();
void printSources(vector<int> sources);
void printVector(vector<int> v);

void readInput(){
    /**
     * Reads input from stdin and inicializes the correspondent graph
    */
    int n, m;
    if (scanf("%d %d", &n, &m) < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }
    if (n < 2 || m < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }

    graph = vector<vertex>(n);
    
    int u, v;
    for (int i = 0; i < m; ++i){
        if (scanf("%d %d", &u, &v) < 0){
            cout << "Vertice invalido. Tente de novo!" << endl;
            exit(EXIT_FAILURE);
        }
        graph[u-1].adj.push_back(v-1);
        graph[v-1].in++;
    }
}

bool isSource(int i){
    return graph[i].in == 0;
}

vector<int> findSources(){
    /**
     * Finds all sources of graph
    */
    vector<int> res = vector<int>();
    for (unsigned int i = 0; i < graph.size(); ++i)
        if (isSource(i))
            res.push_back(i);
    return res;
}

int findLongestStreak(vector<int> sources){
    /**
     * Finds the longest sequence of connected nodes in the graph.
    */

    queue<int> q = queue<int>();
    for(unsigned int i = 0; i<sources.size(); i++){
        q.push(sources[i]);
    }

    int maxStreak = 1, u, adj;

    while(!q.empty()){
        u = q.front();
        q.pop();

        for(unsigned int i = 0; i<graph[u].adj.size(); ++i){

            adj = graph[u].adj[i];

            if (graph[u].streak >= graph[adj].streak){
                graph[adj].streak = graph[u].streak + 1;
                if (graph[adj].streak > maxStreak)
                    maxStreak = graph[adj].streak;
            }

            if(graph[adj].in > 0)
                graph[adj].in--;

            if(isSource(adj))
                q.push(adj);
        }
    }
    return maxStreak;
}

/*************************************************************************************************************************************/
/*                                                             MAIN                                                                  */
/*************************************************************************************************************************************/

int main(){
    readInput();

    vector<int> sources = findSources();
    int streak = findLongestStreak(sources);

    cout << sources.size() << " " << streak << endl;

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
        for(unsigned int j = 0; j < graph[i].adj.size(); ++j){
            cout << graph[i].adj[j]+1 << " ";
        }
        cout << endl;
    }
}

void printSources(vector<int> sources){
    /**
     * Prints sources
    */
    cout << "Sources: ";
    for (unsigned int i = 0; i < sources.size(); ++i)
        cout << sources[i] + 1 << " ";
    cout << endl;
}

void printVector(vector<int> v){
    /**
     * Prints vector of int
    */
    for (unsigned int i = 0; i < v.size(); ++i)
        cout << v[i] + 1 << " ";
    cout << endl;
}