#include <iostream>
#include <cstdio>


int** createMatrix(int N){
    /**
     * Cria matriz
    */

    int** matrix = new int*[N];
    
    for(int i = 0; i<N; i++)
        matrix[i] = new int[N];
    
    return matrix;
}


void printMatrix(int** matrix,int N){
    /**
     * Mostra matriz
    */

    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
}


void histograma1(int** matrix){
    /**
     * O primeiro histograma deve mapear cada 
     * inteiro i no número de pessoas com i amigas.
     * 
     * 3,3                3,2
     * 1 2                1 2
     * 1 3                1 3
     * 2 3
     * 
     * Histograma 1     Histograma 1
     * i = 0 -> 1           -> 2
     * i = 1 -> 1           -> 0
     * i = 2 -> 1           -> 1
    */
    
    std::cout << "Histograma 1";

}


void histograma2(int** matrix){
    /**
     * O segundo histograma deve mapear cada 
     * inteiro i no número de pessoas que têm i pessoas como amigas.
     * 
     * 3,3                3,2
     * 1 2                1 2
     * 1 3                1 3
     * 2 3
     * 
     * Histograma 2     Histograma 2
     * i = 0 -> 1           -> 2
     * i = 1 -> 1           -> 0
     * i = 2 -> 1           -> 1
    */



    std::cout << "Histograma 2";

}


int main(){
    /**
     * Uma linha:
     * N -> Numero de pessoas na rede de contactos
     * M -> Numero de relacoes de amizade entre pessoas
     * Multiplas Linhas:
     * Cada linha indica que u tem como amiga a pessoa v
    */

    int N,M;
    scanf("%d,%d", &N, &M);

    int** matrix = createMatrix(N);

    int u,v;
    for(int i = 0; i<M; i++){
        scanf("%d %d",&u,&v);
        matrix[u-1][v-1] = 1;
    }

    printMatrix(matrix,N);

    histograma1(matrix);
    histograma2(matrix);

    return 0;
}