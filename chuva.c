#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph *Graph;
typedef struct lista *node;

struct lista{
    int x;
    node prox;
};
struct graph{
    int N; // linha
    int M;
    char **matriz; // matriz de adjacencia
};

Graph GRAPHinit(int linha, int coluna){ // onde v é a qtd de vertices
    Graph g = malloc(sizeof(struct graph));
    g->N = linha;
    g->M = coluna; 
    g->matriz = malloc(linha * sizeof(char *));
    for (int i = 0; i < linha; i++) {
        g->matriz[i] = malloc(coluna * sizeof(char));
    }
    return g;
}

char **MATRIZinit(int linha, int coluna){
    char **matriz = malloc(linha * sizeof(char*));
    for (int i = 0; i < linha; i++) {
        matriz[i] = calloc(coluna, sizeof(char));
    }
    return matriz;
}

/*
        Pseudo código pensando naa lógica da questão

onde j é a coluna e i a linha
função
    se i>= tam de colunas return;
    se i+1 for diferente de #    //desce as linhas
        matriz[i][j] = 'o'
        i++;
    se não:                      // verifica esquerda e direita
        matriz[i][j+1] = 'o'    função j + 1;
        matriz[i][j+1] = 'o'    função j - 1;

*/

// n como num de linha  e m como coluna
void chuva(Graph graph, int j, int i){
    // Verifica limites da matriz
    if(i >= graph->N || i < 0 || j >= graph->M || j < 0) 
        return; 
    
    // Marca a posição atual com gota
    graph->matriz[i][j] = 'o';

    // se n c
    if(i+1 < graph->N && graph->matriz[i+1][j] != '#'){ 
       
        chuva(graph, j, i+1);
    }
    
    else if ( i+1 < graph->N) {
        // Se não puder descer, tenta ir para a direita
        if(j+1 < graph->M && graph->matriz[i][j+1] != 'o' && graph->matriz[i][j+1] != '#'){
            chuva(graph, j+1, i);
        }
        
        // E para a esquerda
        if(j-1 >= 0 && graph->matriz[i][j-1] != 'o' && graph->matriz[i][j-1] != '#'){
            chuva(graph, j-1, i);
        }
    }
}

int main(){
    int linha, coluna;
    scanf("%d %d", &linha, &coluna);
    
    // Inicializa o grafo com a matriz
    Graph g = GRAPHinit(linha, coluna);
    
    // Lê a matriz de entrada
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            scanf(" %c", &g->matriz[i][j]);
        }
    }
    
    // Para cada coluna da primeira linha, inicia uma gota
    for(int j = 0; j < coluna; j++){
        if(g->matriz[0][j] =='o' ){
            chuva(g, j, 0);
        }
    }
    
    // Imprime a matriz resultante
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            printf("%c", g->matriz[i][j]);
        }
        printf("\n");
    }
    
    // Libera a memória
    for(int i = 0; i < linha; i++){
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g);
    
    return 0;
}