#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//definir os ponteiros para facilitar
typedef struct graph* Graph;
typedef struct node* link;

struct node{
    int vertice;
    link prox;
};

struct graph{
    int N;
    int M;
    link *adj;
};

// funções base vindas do arquivo do paulo feofillof
Graph GRAPHinit(int v){
    Graph g = malloc(sizeof(struct graph));
    g->N = v;
    g->M = 0;
    g->adj = malloc(v*sizeof(struct node));
    for (int i = 0; i < v; i++){
        g->adj[i] = NULL;
    }
    return g;
}

static link NEWnode(int x, link next){
    link a = malloc(sizeof(struct node));
    a->vertice = x;
    a->prox = next;
    return a;
}

void INSERTarc(Graph g, int x, int w){ // quer inserir arc de x até w 
    for(link a = g->adj[x]; a!=NULL; a = a->prox){
        if (a->vertice == w) return;
    }
    g->adj[x] = NEWnode( w, g->adj[x]); // crio o novo nó
    g->M++;
}

void freeGraph(Graph g) {
    for (int i = 0; i < g->N; i++) {
        link a = g->adj[i];
        while (a) {
            link tmp = a;
            a = a->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

int countInsatisfeito(Graph grafo, int x, int *salario){
    int count = 0;
    for(link a = grafo->adj[x]; a!=NULL; a = a->prox){
        if (salario[x]< salario[a->vertice] ) {
            return 1;
        }
    }
    return 0;
}



int main(){
    // numFunc é 1-based, tenho que tratar isso
    int numFunc, numAlt, numChefe, numSalario;

    scanf("%d", &numFunc);

    int *pa = calloc((numFunc+1), sizeof(int)); // armazenando o chefe
    int *salario = calloc((numFunc+1), sizeof(int)); // armazenando o salario
    // int *insatisfeito = calloc((numFunc+1), sizeof(int)); // armazenando o salario

    Graph grafo = GRAPHinit(numFunc+1);
        // printf("antes do loop\n");

    for(int i = 1 ; i < (numFunc+1) ; i ++){ 
        // printf("dentro do loop\n");
        scanf("%d%d", &pa[i], &salario[i]);
        INSERTarc(grafo, pa[i] , i);
    }
        // printf("depois do loop\n");

    int sum=0;
    for(int i = 1; i<(numFunc+1); i++){
        sum = sum +  countInsatisfeito(grafo, i, salario);
    }
    printf("%d\n", sum);


    
    
    return 0;
}