/**
 * Temos um grafo com pessoas
 * 
 * 3,4  (numero de nos, numero de arcos)
 * 1 2
 * 2 1
 * 2 3
 * 1 3
 * 
 * P1 <---> P2
 *  |    
 *  | --->  P3
 * 
 * 
 * 
 * histograma 1 -> histograma dos arcos de saida (setas a apontar para fora)
 * 0: 1    quantas pessoas sao amigas de zero pessoas
 * 1: 0
 * 2: 2
 * histograma 2 -> histograma dos arcos de entrada (setas a apontar para dentro)
 * 0: 0   quantas pessoas é que tem zero amigos (quantas pessoas é que são meus amigos)
 * 1: 2
 * 2: 1
 * 
 * 
 * Representacao interna:
 * Vector com n (numero de nos) espacos em que cada espaco guardamos o numero para o qual ele aponta
 * -------------------
 * |  1  |  2  |  3  |
 * -------------------
 *     v    v     v
 *    1,2  1,3    
 * 
 * Na verdade guardamos u-1 ou seja se for 1 2 --> 0 1  
*/

//g++ -o main <nome> -std=c++11

#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> graph;
vector<vector<int>> graph_trans;

void readGraph(){
    int n,m;
    scanf("%d,%d", &n, &m);
    // Alocar o espaco para o grafo
    graph = vector<vector<int>>(n, vector<int>());
    graph_trans = vector<vector<int>>(n, vector<int>());
    for(int i=0; i<m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        graph[u-1].push_back(v-1);
        graph_trans[v-1].push_back(u-1);
    }

}

void printGraph(vector<vector<int>> graph){
    for(int i=0; i<graph.size(); i++){
        for(int j=0; j<graph[i].size(); j++){
            printf("%d %d\n", i+1, graph[i][j]+1);
        }
    }
}

int computeMaxOut(vector<vector<int>> graph){
    int max = 0;
    for(int i=0; i<graph.size(); i++){
        if(graph[i].size() > max){
            max = graph[i].size();
        }
    }
    return max;
}

// O(V) em que V eh o numero de nos assumindo que .size() eh constante
vector<int> computeOutHistogram(vector<vector<int>> graph){
    int max = computeMaxOut(graph);
    vector<int> hist = vector<int>(max+1, 0);
    for(int i=0; i<graph.size(); i++){
        hist[graph[i].size()]++;
    }
    return hist;
}

void printHistogram(vector<int> hist){
    for(int i=0; i<hist.size(); i++){
        printf("%d: %d\n",i,hist[i]);
    }
}

//Outra forma de resolver o problema seria calcular o grafo transposto em vez de cria-lo na altura da leitura
vector<vector<int>> compute(vector<vector<int>> graph){
    vector<vector<int>> trans_graph = vector<vector<int>>(graph.size(),vector<int>());
    for(int i=0; i<graph.size(); i++){
        for(int j=0; j<graph[i].size(); j++){
            trans_graph[graph[i][j]].push_back(i);
        }
    }
    return trans_graph;
}

int main(){
    readGraph();
    vector<int> hist1 = computeOutHistogram(graph);
    printf("Histograma 1\n");
    printHistogram(hist1);
    vector<int> hist2 = computeOutHistogram(graph_trans);
    printf("Histograma 2\n");
    printHistogram(hist2);
    return 0;
}