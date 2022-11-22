#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include"fila.h"
#include"grafo.h"

/* Basea do no código obtido do curso da Prof. Vanessa Braganholo */


TGrafo *grafo_inicializa(){
    return NULL;
}

void grafo_imprime(TGrafo *g){
    while(g != NULL){
        printf("Vertice %d\n", g->id_vertice);
        printf("Vizinhos: ");
        TVizinho *v = g->prim_vizinho;
        while(v != NULL){
            printf("%d ", v->id_vizinho);
            v = v->prox;
        }
        printf("\n\n");
        g = g->prox;
    }
}

void grafo_libera_vizinho(TVizinho *v){
    if(v != NULL) {
        grafo_libera_vizinho(v->prox);
        free(v);
    }
}

void grafo_libera(TGrafo *g){
    if(g != NULL){
        grafo_libera_vizinho(g->prim_vizinho);
        grafo_libera(g ->prox);
        free(g);
    }
}

TGrafo* grafo_busca_vertice(TGrafo* g, int x){
    while((g != NULL) && (g->id_vertice != x)) {
        g = g->prox;
    }
    return g;
}

TVizinho* grafo_busca_aresta(TGrafo *g, int v1, int v2){
    TGrafo *pv1 = grafo_busca_vertice(g,v1);
    TGrafo *pv2 = grafo_busca_vertice(g,v2);
    TVizinho *resp = NULL;
    //checa se ambos os vértices existem
    if((pv1 != NULL) && (pv2 != NULL)) {
        //percorre a lista de vizinhos de v1 procurando por v2
        resp = pv1->prim_vizinho;
        while ((resp != NULL) && (resp->id_vizinho != v2)) {
            resp = resp->prox;
        }
    }
    return resp;
}

TGrafo *grafo_insere_vertice(TGrafo *g, int x){
    TGrafo *p = grafo_busca_vertice(g, x);
    if(p == NULL){
        p = (TGrafo*) malloc(sizeof(TGrafo));
        p->id_vertice = x;
        p->prox = g;
        p->prim_vizinho = NULL;
        g = p;
    }
    return g;
}

void grafo_insere_um_sentido(TGrafo *g, int v1, int v2){
    TGrafo *p = grafo_busca_vertice(g, v1);
    TVizinho *nova = (TVizinho *) malloc(sizeof(TVizinho));
    nova->id_vizinho = v2;
    nova->prox = p->prim_vizinho;
    p->prim_vizinho = nova;
}

void grafo_insere_aresta(TGrafo *g, int v1, int v2){
    TVizinho *v = grafo_busca_aresta(g, v1, v2);
    if(v == NULL) {
        grafo_insere_um_sentido(g, v1, v2);
        grafo_insere_um_sentido(g, v2, v1);
    }
}

void grafo_retira_um_sentido(TGrafo *g, int v1, int v2){
    TGrafo *p = grafo_busca_vertice(g, v1);
    if(p != NULL) {
        TVizinho *ant = NULL;
        TVizinho *atual = p->prim_vizinho;
        while ((atual) && (atual->id_vizinho != v2)) {
            ant = atual;
            atual = atual->prox;
        }
        if (ant == NULL) //v2 era o primeiro nó da lista de vizinhos
            p->prim_vizinho = atual->prox;
        else
            ant->prox = atual->prox;
        free(atual);
    }
}



void imprimir_int(TElem x){
    int * i = (int*)x;
    printf("%d ",*i);
}

void grafo_percurso_em_largura(TGrafo *g, int x){

    TFila * f = fila_criar(1000,sizeof(int));
    int * visitados = (int *)malloc(1000*sizeof(int));
    memset(visitados,0,1000*sizeof(int));

    printf("Sequencia de visitas em largura:\n");

    TGrafo *v = grafo_busca_vertice(g,x);
    fila_inserir(f,&(v->id_vertice),sizeof(int));


    while (!fila_verificar_vazia(f)){
        int vertice_id;
        //fila_dump(f,sizeof(int),imprimir_int);
        fila_retirar(f,&vertice_id,sizeof(int));

        if (!visitados[vertice_id]){
            printf("%d ",vertice_id);
            visitados[vertice_id]=1;

            v = grafo_busca_vertice(g,vertice_id);
            TVizinho * viz = v->prim_vizinho;

            while (viz!=NULL){
                if (!visitados[viz->id_vizinho]){
                    fila_inserir(f,&(viz->id_vizinho),sizeof(int));
                }
                viz = viz->prox;
            }
        }
    }

    printf("\n\n");



}


