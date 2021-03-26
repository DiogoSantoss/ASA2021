/**
 * Ficheiro: proj.cpp
 * Realizado por: David Belchior (95550) e Diogo Santos (95562)
 * Instituto Superior Tecnico - LEIC-A - Analise e Sintese de Algoritmos
 * Para compilar: g++ -std=c++11 -O3 -Wall proj.cpp -lm
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define WHITE 1
#define GREY 0
#define BLACK -1

using namespace std;

typedef struct{
    int colour = WHITE;
    int end;
    vector<int> adj;
} vertex;

vector<vertex> graph;
vector<vector<int>> graph_trans;

void readInput(){
    /**
     * Reads input from stdin and inicializes graph and graph_trans
    */
    int n, m;
    if (scanf("%d %d", &n, &m) < 0)
        exit(EXIT_FAILURE);
    if (n < 2 || m < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }

    graph = vector<vertex>(n);
    graph_trans = vector<vector<int>>(n, vector<int>());
    
    int u, v;
    for (int i = 0; i < m; ++i){
        if (scanf("%d %d", &u, &v) < 0)
            exit(EXIT_FAILURE);
        graph[u-1].adj.push_back(v-1);
        graph_trans[v-1].push_back(u-1);
    }
}

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

vector<int> findSources(){
    /**
     * Finds all sources of graph_trans
    */
    vector<int> res = vector<int>();
    for (unsigned int i = 0; i < graph_trans.size(); ++i)
        if (graph_trans[i].size() == 0)
            res.push_back(i);
    return res;
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

/******************************************************************************TESTING AREA******************************************************************************/

/**
 * Executa BFS para cada Source do grafo.
 * A BFS coloca a Source na queue, de seguida tira e coloca os adjacentes na queue atualizando os streaks dos adj
 * Retira um adjacente da queue e coloca os seus adjacentes e atualiza os streaks
*/

int executeBFS(int source){
    for (unsigned int i = 0; i < graph.size(); ++i){
        graph[i].streak = 0;
    }
        
    graph[source].streak = 1;

    queue<int> q = queue<int>();
    q.push(source);

    int u, index, streak = 0, maxStreak = 0;

    while (!q.empty()){
        u = q.front();
        q.pop();
        cout << u;
        for (unsigned int i = 0; i < graph[u].adj.size(); ++i){
            streak = graph[u].streak;
            index = graph[u].adj[i];
            if (streak >= graph[index].streak){
                graph[index].streak = streak + 1;
                if (graph[index].streak > maxStreak)
                    maxStreak = graph[index].streak;
            }
            q.push(index);
        }
    }
    return maxStreak;
}

/*
int executeDFS(int source){

    for(unsigned int i = 0; i < graph.size(); i++){
        graph[i].colour = WHITE;
        graph[i].end = 0;
    }

    int time = 0;

    stack<int> s = stack<int>();
    graph[source].colour = GREY;
    s.push(source);

    while(!q.empty()){
        u = s.top();
        s.pop();

        for(unsigned int i = 0; i<graph[u].size(); i++){
            if(graph[u].adj[i].colour == WHITE){
                graph[u].adj[i].colour = GREY
            }
        }
        graph[u].colour = BLACK;
        //graph[u].end = time+1;
    }


}
*/
int main(){

    readInput();
    //printGraph();
    //printTransGraph();
    int streak, max = 0;
    vector<int> sources = findSources();
    //printSources(sources);

    for (unsigned int i = 0; i < sources.size(); ++i)
        if ((streak = executeBFS(sources[i])) > max)
            max = streak;

    cout << sources.size() << " " << max << endl;
    exit(EXIT_SUCCESS);
    
}