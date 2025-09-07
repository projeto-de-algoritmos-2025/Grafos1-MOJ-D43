#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph *Graph;
struct graph{
    int N; // Número de candidatos
    char **matriz; // matriz de adjacencia
};

Graph GRAPHinit(int tamanho){
    Graph g = malloc(sizeof(struct graph));
    g->N = tamanho;
    g->matriz = malloc((tamanho + 1) * sizeof(char *));
    for (int i = 0; i <= tamanho; i++) {
        g->matriz[i] = malloc((tamanho + 1) * sizeof(char));
    }
    return g;
}

void GRAPHfree(Graph g) {
    for (int i = 0; i <= g->N; i++) {
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g);
}

// Array para guardar o id do grupo de amigos de cada candidato
int grupo[2501];

// Função DFS para marcar todos os amigos conectados
void dfs(int n, char** amizade, int* grupo, int u, int id_grupo) {
    grupo[u] = id_grupo;

    for (int v = 1; v <= n; v++) {
        if (amizade[u][v] == '1' && grupo[v] == 0) {
            dfs(n, amizade, grupo, v, id_grupo);
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);

    // matriz de amizade
    Graph g_amizade = GRAPHinit(N);

    // lendo as amizades e preenchendo a tabela; 1 = amigos, 0 = não amigos
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf(" %c", &g_amizade->matriz[i][j]);
        }
    }

    // alocando e inicializando o array de grupos
    int* grupo = calloc(N + 1, sizeof(int));
    
    // pré-processamento com DFS para mapear os grupos
    int id_grupo_atual = 1;
    for (int i = 1; i <= N; i++) {
        if (grupo[i] == 0) {
            dfs(N, g_amizade->matriz, grupo, i, id_grupo_atual);
            id_grupo_atual++;
        }
    }

    // processamento das entrevistas
    int E;
    scanf("%d", &E);

    // array para marcar os grupos que apareceram na entrevista atual
    bool* grupos_na_entrevista = malloc(sizeof(bool) * (id_grupo_atual));

    for (int i = 0; i < E; i++) {
        int K;
        scanf("%d", &K);

        // resetando o array de marcação
        for (int j = 1; j < id_grupo_atual; j++) {
            grupos_na_entrevista[j] = false;
        }

        // diz se tem amigos no mesmo grupo
        bool conflito_encontrado = false;

        // lendo os candidatos da entrevista
        for (int j = 0; j < K; j++) {
            int candidato_id;
            scanf("%d", &candidato_id);
            
            if (conflito_encontrado) continue; // amigos no mesmo grupo

            int grupo_do_candidato = grupo[candidato_id];
            if (grupos_na_entrevista[grupo_do_candidato]) {
                conflito_encontrado = true;
            } else {
                grupos_na_entrevista[grupo_do_candidato] = true;
            }
        }
        
        if (conflito_encontrado) {
            printf("S\n");
        } else {
            printf("N\n");
        }
    }

    GRAPHfree(g_amizade);
    free(grupo);
    free(grupos_na_entrevista);

    return 0;
}