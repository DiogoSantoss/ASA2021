/**
 * Ficheiro: proj.cpp
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
     * Reads input from stdin and inicializes graph and graph_trans
    */
    int n, m;
    if (scanf("%d %d", &n, &m) < 0){
            cout << "Vértice inválido!" << endl;
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
            cout << "Vértice inválido!" << endl;
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

int findValue(vector<int> v, int n){
    /**
     * Finds values in vector of int
    */
    for(unsigned int i = 0; i<v.size();++i){
        if(v[i] == n)
            return i;
    }
    return -1;
}

vector<int> topologicalSort(vector<int> sources){
    /**
     * Sorts graph in Topological Order.
    */

    vector<int> sorted = vector<int>();

    queue<int> q = queue<int>();
    for(unsigned int i = 0; i<sources.size(); i++){
        q.push(sources[i]);
    }

    int u,adj;

    while(!q.empty()){
        u = q.front();
        q.pop();
        sorted.push_back(u);

        for(unsigned int i = 0; i<graph[u].adj.size(); ++i){

            adj = graph[u].adj[i];

            if(graph[adj].in>0)
                graph[adj].in--;

            if(isSource(adj))
                q.push(adj);
        }
    }
    return sorted;
}

int findLongestStreak(vector<int> sorted){
    int maxStreak = 1;
    for (unsigned int i = 0; i < sorted.size(); ++i){
        int father = sorted[i];
        for (unsigned int j = 0; j < graph[father].adj.size(); ++j){
            int son = graph[father].adj[j];
            if (graph[father].streak >= graph[son].streak){
                graph[son].streak = graph[father].streak + 1;
                if (graph[son].streak > maxStreak)
                    maxStreak = graph[son].streak;
            }
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
    vector<int> topo = topologicalSort(sources);

    printf("%ld %d\n", sources.size(), findLongestStreak(topo));

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