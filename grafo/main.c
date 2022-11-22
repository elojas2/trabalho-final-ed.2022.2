#include<stdio.h>
#include<stdlib.h>
#include"grafo.h"
#include <conio.h>
#include <time.h>

/*

     1-------------2
    / \           /|\
   /    \       /  | \
  /       \   /    |  \
 4----------7------|---3-------8
  \       /   \    |  /     .´
   \    /       \  | /   .´
    \ /           \|/ .´
     5-------------6´

*/

int main(){
    TGrafo *g = grafo_inicializa();

    float tempo;
    time_t t_ini, t_fim;
    t_ini = time(NULL);

    //insere números de 1 a x
    for(int i = 1; i <= 10;i++){
        g = grafo_insere_vertice(g, i); //1
    }
    //insere arestas com números aleatorios
    for(int j = 1; j <= 10; j++){

        int x = 1 + (rand() % 10);
        int y = 1 + (rand() % 10);
        grafo_insere_aresta(g, x, y);
    }
    /*
     * teste com apenas dois números
       g = grafo_insere_vertice(g, 1);
       g = grafo_insere_vertice(g, 2);
       grafo_insere_aresta(g, 1, 2);
   */

    grafo_imprime(g);
    grafo_percurso_em_largura(g, 2);

    //tempo de execucao
    t_fim = time(NULL);
    tempo = difftime(t_fim, t_ini);
    printf("=====================================================================\n");
    printf("tempo de execucao: %f\n", tempo);
    printf("=====================================================================");

}



