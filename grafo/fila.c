#include<stdio.h>
#include<memory.h>
#include"fila.h"


int incr (int ind, int n){
  return (ind + 1) % n;
}


TFila *fila_criar(int tam, size_t tam_elem){
    TFila * fila = (TFila*)malloc(sizeof(TFila));
    fila->tam = tam;
    fila->vet = calloc(fila->tam,tam_elem);
    fila->n = fila->ini = 0; 
    return fila;
}

int fila_verificar_vazia(TFila *fila){
    return (fila->n==0);
}



void fila_inserir(TFila *fila, TElem e, size_t tam_elem){
    if (fila->n == fila->tam){
        unsigned char * vet_dest = (unsigned char*)calloc(tam_elem * fila->n * 2, sizeof(unsigned char));
        unsigned char * vet_orig = fila->vet;

        int i = fila->ini*tam_elem, j = 0;
        while(j < fila->n*tam_elem){
            vet_dest[j++] = vet_orig[i];
            i = incr(i, fila->tam*tam_elem);
        }
        fila->ini = 0;
        fila->tam *= 2;
        TElem aux = fila->vet;
        fila->vet = (void*)vet_dest;
        free(aux);
    }
    unsigned char *v = fila->vet; //base da pilha
    int fim = (fila->ini + fila->n++) % fila->tam;
    int offset = fim*tam_elem; //o que precisamos somar para alcançar o topo
    memcpy(v+offset,e,tam_elem);

}

void fila_retirar(TFila *fila, TElem e, size_t tam_elem){
    if (fila_verificar_vazia(fila)){
      printf("\nFila vazia\n");
      exit(1);
    };

    unsigned char * v = fila->vet;
    int offset = (fila->ini)*(tam_elem);
    memcpy(e,v+offset,tam_elem);
    fila->ini = incr(fila->ini,fila->tam);
    fila->n--;
}

TFila * fila_liberar(TFila *fila){
    free(fila->vet);
    free(fila);
    return NULL;
}

