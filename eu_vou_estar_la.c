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


int main (){

    // ler os n - numero de cidade - ; m - numero de locais qeu juliano esteve - j - qtd de locais qeu qeur saber se juliano esteve
    int n,m,j;
    scanf("%d%d%d", &n, &m, &j);

    // adaptação - guardo em um vetor todos marcados como 0
    // se juliano estiver lá, marco como 1 e para todos os vizinhos dele de forma instantânea, então quando for pegar a resposta 
    // só vejo no vetor se  foi visitado ou n

    Graph grafo = GRAPHinit(n);

    for(int i = 0; i <n ; i++){
        int k;
        scanf("%d", &k);

        while (k){
            int w;
            scanf("%d", &w);
            INSERTarc(grafo, i, w);
            k--;
        }
        
    }

    int visitado[n];

    for ( int i = 0; i <n; i ++){
        visitado[i] = 0 ;
    }

    for ( int i = 0; i <m; i ++){
        int k;
        scanf("%d", k);
        visitado[k] = 1;
        for(link a = grafo->adj[k]; a!=NULL; a = a->prox){
            visitado[a->v] =1;
        }
    }

    for (int i = 0; i<j; i++){
        int k;
        scanf("%d", &k);
        if(visitado[k]){
            printf("Eu vou estar la\n");
        }
        else printf("Nao vou estar la\n");
    }

    return 0;
}