#include <stdio.h>
#include <string.h>
#define N 5

//DISCLAIMER: ISTO ESTA ABSOLUTAMENTE CAOTICO, MAL PROGRAMADO, E ALEM DISSO NAO ENTENDEMOS O QUE NOS ERA PEDIDO. - FUNKY

int matrix[N][N];
int friendsNumbers[N];

void printMatrix(int max){
    for (int i = 0; i < max; ++i){
        for (int j = 0; j < max; ++j)
            printf("%d ",matrix[i][j]);
        printf("\n");
    }
}

int amountFriends(int line[], int x){
    int total = 0;
    for (int i = 0; i < x; ++i)
        total += line[i];
    return total;
}

int main(){
    int n, m, start, finish;
    scanf("%d,%d", &n, &m);

    for (int i = 0; i < m; ++i){
        scanf("%d %d", &start, &finish);
        matrix[start-1][finish-1] = 1;
    }
    //printMatrix(n);
    puts("Histograma 1");
    for (int i = 0; i < n; ++i)
        friendsNumbers[amountFriends(matrix[i], n)]++;
    for (int i = 0; i < n; ++i)
        printf("%d\n", friendsNumbers[i]);
    return 0;
}