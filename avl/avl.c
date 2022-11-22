#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

Tarvore *CriaArvore(){
    return NULL;
}

int ArvoreVazia(Tarvore **arv){
    if(*arv == NULL) return 1;
    else return 0;
}

Tarvore *BuscaMenorArvore(Tarvore **arv){
    if(ArvoreVazia(arv)) return NULL;
    if(!ArvoreVazia((Tarvore **)&((*arv)->esq)))
        return BuscaMenorArvore((Tarvore **)&((*arv)->esq));
    else return (*arv);
}
//Tarvore *BuscaMaiorArvore(Tarvore **arv){}

Tarvore *BuscaArvore(Tarvore **arv, int x){
    if(ArvoreVazia(arv)) return NULL;
    if(x < (*arv)->chave) return BuscaArvore((Tarvore **)&((*arv)->esq),x);
    if(x > (*arv)->chave) return BuscaArvore((Tarvore **)&((*arv)->dir),x);
    if(x == (*arv)->chave) return (*arv);
}
void RotacaoEsq(Tarvore **arv){
    Tarvore *aux1, *aux2;
    aux1 = *arv;
    aux2 = (Tarvore *)((*arv)->dir);
    (*arv) = aux2;
    aux1->dir = aux2->esq;
    aux2->esq = (void *)aux1;
    if(aux2->bal== -1) aux1->bal += 2;
    if(aux2->bal== 0) aux1->bal += 1;
    aux2->bal += 1;
}

void RotacaoDir(Tarvore **arv){
    Tarvore *aux1, *aux2;
    aux1 = *arv;
    aux2 = (Tarvore *)((*arv)->esq);
    (*arv) = aux2;
    aux1->esq = aux2->dir;
    aux2->dir = (void *)aux1;
    if(aux2->bal== 1) aux1->bal -= 2;
    if(aux2->bal== 0) aux1->bal -= 1;
    aux2->bal -= 1;
}

void RotacaoEsqDir(Tarvore **arv){
    RotacaoEsq((Tarvore **)&((*arv)->esq) );
    RotacaoDir(arv);
}

void RotacaoDirEsq(Tarvore **arv){
    RotacaoDir((Tarvore **)&((*arv)->dir));
    RotacaoEsq(arv);
}

int InsereArvore(Tarvore **arv, int x){
    Tarvore *novo, *esq, *dir;
    int resultado;
    if(ArvoreVazia(arv)) {
        novo = (Tarvore *) malloc(sizeof(Tarvore));
        if(novo == NULL) return NaoFez;
        novo->chave = x;
        novo->bal = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *arv = novo;
        return AlterouProf;
    }

    if(x < (*arv)->chave){
        resultado = InsereArvore((Tarvore **)&((*arv)->esq),x);
        if(resultado == NaoFez || resultado == NaoAlterouProf) return resultado;
        if(resultado == AlterouProf) {
            (*arv)->bal += 1;
            if((*arv)->bal == 2){
                //Rebalanceia a arvore
                esq = (Tarvore *)((*arv)->esq);
                if(esq->bal == 1) {//Caso LL
                    RotacaoDir(arv);
                    return NaoAlterouProf;
                }
                if(esq->bal == -1){//Caso LR
                    RotacaoEsqDir(arv);
                    return NaoAlterouProf;
                }
            }
            if((*arv)->bal == 1) return AlterouProf;
            if((*arv)->bal == 0) return NaoAlterouProf;

        }
    }
    if(x > (*arv)->chave){
        resultado = InsereArvore((Tarvore **)&((*arv)->dir),x);
        if(resultado == NaoFez || resultado == NaoAlterouProf) return resultado;
        if(resultado == AlterouProf) {
            (*arv)->bal -= 1;
            if((*arv)->bal == -2){
                //Rebalanceia a arvore
                dir = (Tarvore *)((*arv)->dir);
                if(dir->bal == 1) {//Caso RL
                    RotacaoDirEsq(arv);
                    return NaoAlterouProf;
                }
                if(dir->bal == -1){//Caso RR
                    RotacaoEsq(arv);
                    return NaoAlterouProf;
                }
            }
            if((*arv)->bal == -1) return AlterouProf;
            if((*arv)->bal == 0) return NaoAlterouProf;
        }
    }

    if(x == (*arv)->chave) return NaoFez;
}

int RemoveArvore(Tarvore **arv, int x){
    Tarvore *aux, *aux2,*esq, *dir;
    int resultado, novox;
    if(ArvoreVazia(arv)) return NaoFez;
    if(x < (*arv)->chave){
        resultado = RemoveArvore((Tarvore **)&((*arv)->esq),x);
        if(resultado == NaoFez || resultado == NaoAlterouProf) return resultado;
        if(resultado == AlterouProf){
            (*arv)->bal -= 1;
            if((*arv)->bal == -2){
                //Rebalanceia a arvore
                dir = (Tarvore *)((*arv)->dir);
                if(dir->bal == 1) {//Caso RL
                    RotacaoDirEsq(arv);
                    return AlterouProf; //verificar
                } else {//Caso RR
                    RotacaoEsq(arv);
                    return AlterouProf;//verificar
                }
            }
            if((*arv)->bal == -1) return NaoAlterouProf;
            if((*arv)->bal == 0) return AlterouProf;
        }
    }
    if(x > (*arv)->chave){
        resultado = RemoveArvore((Tarvore **)&((*arv)->dir),x);
        if(resultado == NaoFez || resultado == NaoAlterouProf) return resultado;
        if(resultado == AlterouProf) {
            (*arv)->bal += 1;
            if((*arv)->bal == 2){
                //Rebalanceia a arvore
                esq = (Tarvore *)((*arv)->esq);
                if(esq->bal == -1){//Caso LR
                    RotacaoEsqDir(arv);
                    return AlterouProf;//verificar
                } else {//Caso LL
                    RotacaoDir(arv);
                    return AlterouProf;//verificar
                }
            }
            if((*arv)->bal == 1) return NaoAlterouProf;
            if((*arv)->bal == 0) return AlterouProf;
        }
    }

    if(x == (*arv)->chave){
        //Remove a chave
        if((*arv)->esq == NULL && (*arv)->dir == NULL){
            free(*arv);
            (*arv) = NULL;
            return AlterouProf;
        }
        aux = (*arv);
        if((*arv)->esq == NULL || (*arv)->dir == NULL){
            if(aux->esq != NULL) (*arv) = aux->esq;
            if(aux->dir != NULL) (*arv) = aux->dir;
            free(aux);
            return AlterouProf;
        }
        if((*arv)->esq != NULL && (*arv)->dir != NULL){
            aux2 = BuscaMenorArvore((Tarvore **)&(*arv)->dir);
            novox = aux2->chave;
            resultado = RemoveArvore(arv, aux2->chave);
            (*arv)->chave = novox;
            return NaoAlterouProf;
        }
    }
}

void ImprimeArvore(Tarvore **arv){
    printf("|\n");
    printf("Arvore pos-ordem: ");
    ImprimeArvorePos(arv);
    printf("|\n");
}

void ImprimeArvorePos(Tarvore **arv){
    if(ArvoreVazia(arv)) return;
    ImprimeArvorePos((Tarvore **)&((*arv)->esq));
    ImprimeArvorePos((Tarvore **)&((*arv)->dir));
    printf("| %3d (%2d) ",(*arv)->chave, (*arv)->bal);
}

