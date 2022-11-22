#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int DEBUG = 0;

int main(int argc, char **argv){
    Tarvore *arv = CriaArvore();
    Tarvore * aux;

    int opcao, elem;

    while(1){

        printf("  *****************************************  \n");
        printf("  ***********   Menu da Arvore   ********** \n");
        printf("  *****************************************  \n");
        printf("  *****************************************  \n");
        printf("  *         Digite a opcao desejada       *  \n");
        printf("  *****************************************  \n");
        printf("  *  1 - Inserir elemento                 *  \n");
        printf("  *  2 - Inserir elementos aleatorios     *  \n");
        printf("  *  3 - Remover elemento                 *  \n");
        printf("  *  4 - Buscar por elemento              *  \n");
        printf("  *  5 - imprimir em pos ordem            *  \n");
        printf("  *  6 - Sair do programa                 *  \n");
        printf("  ***************************************** \n");
        printf(" : ");
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
                printf("Digite o elemento a ser inserido.\n");
                scanf("%d", &elem);
                if(InsereArvore(&arv, elem)==NaoFez) printf("Elemento nao inserido, ja existe\n");
                else printf("Elemento inserido.\n");
            case 5:
                ImprimeArvore(&arv);
                break;
            case 3:
                printf("Digite o elemento a ser removido.\n");
                scanf("%d", &elem);

                if(RemoveArvore(&arv, elem)==NaoFez) printf("Elemento nao encontrado.\n");
                else printf("Elemento removido. Elem = %d\n", elem);
                ImprimeArvore(&arv);
                break;
            case 2:
                printf("Digite o elemento a quantidade de numeros a serem inseridos.\n");
                scanf("%d", &elem);
                for(int i = 0; i < elem; i++){
                    if(InsereArvore(&arv, rand() % elem)==NaoFez) printf("Elemento nao inserido. Elemento ja existe\n");
                    else printf("Elemento inserido.\n");
                }
                break;
            case 4:
                printf("Digite o elemento a ser buscado.\n");
                scanf("%d", &elem);
                aux = BuscaArvore(&arv, elem);
                if(aux == NULL) printf("Elemento nao encontrado.\n");
                else printf("Elemento encontrado. Elem = %d\n", aux->chave);
                break;

            case 6:
                return 1;

        }
    }
}