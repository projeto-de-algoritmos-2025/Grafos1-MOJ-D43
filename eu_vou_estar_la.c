#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph *Graph;
typedef struct node *link;


struct node{
    int v; // é o valor do nó vizinho
    link prox;
};

struct graph{
    int N; // qtd de no
    int M;
    link* adj; // lista com as listas encadeadas de cada nó
};

static link NEWnode(int x, link next){
    link a = malloc(sizeof(struct node));
    a->v = x;
    a->prox = next;
    return a;
}

Graph GRAPHinit(int v){ // onde v é a qtd de vertices
    Graph g = malloc(sizeof(struct graph));
    g->N = v;
    g->M = 0; 
    g->adj = malloc(v*sizeof(link));
    for (int i = 0; i<v; i++){
        g->adj[i] = NULL;
    }
    return g;
}

void INSERTarc(Graph g, int x, int w){ // quer inserir arc de x até w 
    for(link a = g->adj[x]; a!=NULL; a = a->prox){
        if (a->v == w) return;
    }
    g->adj[x] = NEWnode( w, g->adj[x]); // crio o novo nó
    g->M++;
}
