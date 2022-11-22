#include <stdio.h>
#include <stdlib.h>

#define AlterouProf 1
#define NaoAlterouProf 0
#define NaoFez -1

typedef struct Tarv{
    int chave;
    void *esq;
    void *dir;
    int bal;
} Tarvore;

Tarvore *CriaArvore();
int ArvoreVazia(Tarvore **arv);
//Tarvore *BuscaMenorArvore(Tarvore **arv);
//Tarvore *BuscaMaiorArvore(Tarvore **arv);
Tarvore *BuscaArvore(Tarvore **arv, int x);
void RotacaoEsq(Tarvore **arv);
void RotacaoDir(Tarvore **arv);
void RotacaoEsqDir(Tarvore **arv);
void RotacaoDirEsq(Tarvore **arv);
int InsereArvore(Tarvore **arv, int x);
int RemoveArvore(Tarvore **arv, int x);
int MenorProfArvore(Tarvore **arv);
int MaiorProfArvore(Tarvore **arv);
void ImprimeArvore(Tarvore **arv);
void ImprimeArvorePos(Tarvore **arv);

