#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include<stdlib.h>



typedef void* TElem;

typedef struct fila{int tam; //tam
                    int n; //n elementos
                    int ini; //ini fila
                    TElem vet; // vet é um array implementado como void *vet

                    }TFila;

TFila *fila_criar(int tam, size_t tam_elem);

int fila_verificar_vazia(TFila *fila);

void fila_inserir(TFila *fila, TElem e, size_t tam_elem);

void fila_retirar(TFila *fila, TElem e, size_t tam_elem);

TFila *fila_liberar(TFila *fila);


#endif

