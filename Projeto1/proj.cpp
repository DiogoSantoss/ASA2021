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
    vector<int> adj;
} vertex;

vector<vertex> graph;
vector<vector<int>> graph_trans;

void printGraph();
void printTransGraph();
void printSources(vector<int> sources);
void printVector(vector<int> v);

void readInput(){
    /**
     * Reads input from stdin and inicializes graph and graph_trans
    */
    int n, m;
    scanf("%d %d", &n, &m);
    if (n < 2 || m < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }

    graph = vector<vertex>(n);
    graph_trans = vector<vector<int>>(n, vector<int>());
    
    int u, v;
    for (int i = 0; i < m; ++i){
        scanf("%d %d", &u, &v);
        graph[u-1].adj.push_back(v-1);
        graph_trans[v-1].push_back(u-1);
    }
}

bool isSource(int i){
    return graph_trans[i].size() == 0;
}

vector<int> findSources(){
    /**
     * Finds all sources of graph
    */
    vector<int> res = vector<int>();
    for (unsigned int i = 0; i < graph_trans.size(); ++i)
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

    int u,adj,pos;

    while(!q.empty()){
        u = q.front();
        q.pop();
        sorted.push_back(u);

        for(unsigned int i = 0; i<graph[u].adj.size(); ++i){
            adj = graph[u].adj[i];

            pos = findValue(graph_trans[adj],u);
            graph_trans[adj].erase(graph_trans[adj].begin()+pos);

            if(isSource(adj))
                q.push(adj);
        }
    }
    return sorted;
}

int findLongestStreak(vector<int> sources, vector<int> sorted){
    int max = 0, streak = 0;

    for(unsigned int i = 0; i<sources.size(); ++i){
        for(unsigned int n = findValue(sorted,i); n<sorted.size();++n){
            if(findValue(graph[sorted[n]].adj, sorted[n+1]) != -1)
                streak++;
        }
        if (streak > max)
            max = streak;
    }
    return max;
}

/*************************************************************************************************************************************/
/*                                                             MAIN                                                                  */
/*************************************************************************************************************************************/

int main(){
    readInput();

    vector<int> sources = findSources();
    vector<int> topo = topologicalSort(sources);

    printf("%ld %d\n", sources.size(), findLongestStreak(sources,topo));

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

void printTransGraph(){
    /**
     * Prints graph_trans
    */
    cout << "Transposed graph:" << endl;
    for (unsigned int i = 0; i < graph_trans.size(); ++i){
        cout << i+1 << " -> ";
        for (unsigned int j = 0; j < graph_trans[i].size(); ++j){
            cout << graph_trans[i][j]+1 << " ";
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