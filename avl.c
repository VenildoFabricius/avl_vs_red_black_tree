#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

avl *criaArvore() {
    avl *arv;

    arv = (avl *)malloc(sizeof(avl));
    if(!arv) {
        printf("Erro ao criar a arvore\n");
        return NULL;
    }

    arv->sentinela = (no *)malloc(sizeof(no));
    arv->numElementos = 0;
    arv->sentinela->Fdir = NULL;
    arv->sentinela->Fesq = NULL;
    arv->sentinela->pai = NULL;
    arv->sentinela->chave = -1000;
    arv->rotacoes = 0;

    return arv;
}

int insereNo(avl *arv, int valor) {
    arv->numElementos++;

    no *atual = arv->sentinela->Fdir;

    if (!atual) {
        atual = (no *)malloc(sizeof(no));
        if(!atual) {
            printf("\nErro ao alocar no");
            return 0;
        }
        arv->sentinela->Fdir = atual;
        atual->fb = 0;
        atual->Fdir = NULL;
        atual->Fesq = NULL;
        atual->pai = arv->sentinela;
        atual->chave = valor;
        return 1;
    }

    no *ant;

    while (atual) {
        if (valor >= atual->chave) {
            ant = atual;
            atual = atual->Fdir;
        } else {
            ant = atual;
            atual = atual->Fesq;
        }
    }

    atual = (no *)malloc(sizeof(no));
    if(!atual) {
        printf("\nErro ao alocar no");
        return 0;
    }
    atual->fb = 0;
    atual->Fdir = NULL;
    atual->Fesq = NULL;
    atual->pai = ant;
    atual->chave = valor;

    if (valor >= ant->chave)
        ant->Fdir = atual;
    else
        ant->Fesq = atual;

    atualizaFB_insercao(arv, atual);

    return 1;
}

void atualizaFB_insercao(avl *arv, no *novoNo) {
    no *aux = (no *)malloc(sizeof(no));
    aux = novoNo;
    do {
        if (aux->chave < aux->pai->chave) {
            aux->pai->fb = aux->pai->fb - 1;
        } else {
            aux->pai->fb = aux->pai->fb + 1;
        }
        aux = aux->pai;
    } while (aux != arv->sentinela->Fdir && (aux->fb == 1 || aux->fb == -1));
    if (aux->fb == -2 || aux->fb == 2) {
        balanceamento(arv, aux);
    }
}

void balanceamento(avl *arv, no *noDesbalanceado) {
    arv = arv;
    no *filho;
    if (noDesbalanceado->fb == -2) {
        filho = noDesbalanceado->Fesq;
        if (filho->fb == 1) {
            // Rotação dupla
            int fbNeto = filho->Fdir->fb;
            rotacaoEsq(arv, filho);
            rotacaoDir(arv, noDesbalanceado);
            // ajustar fb
            if (fbNeto == 0) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            } else if (fbNeto == -1) {
                noDesbalanceado->fb = 1;
                filho->fb = 0;
                noDesbalanceado->pai->fb = 0;
            } else {
                noDesbalanceado->fb = 0;
                filho->fb = -1;
                noDesbalanceado->pai->fb = 0;
            }
        } else {
            // rotação simples
            int fbFilho = filho->fb;
            rotacaoDir(arv, noDesbalanceado);
            filho->fb = 0;
            noDesbalanceado->fb = 0;
            if (fbFilho == 0) {
                // só acontece na remoção
                // Ajustar o fb
                filho->fb = 1;
                noDesbalanceado->fb = -1;
            }
        }
    }

    if (noDesbalanceado->fb == 2) {
        filho = noDesbalanceado->Fdir;
        if (filho->fb == -1) {
            // Rotação dupla
            int fbNeto = filho->Fesq->fb;
            rotacaoDir(arv, filho);
            rotacaoEsq(arv, noDesbalanceado);
            // ajustar fb
            if (fbNeto == 0) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            } else if (fbNeto == -1) {
                noDesbalanceado->fb = 0;
                filho->fb = 1;
                noDesbalanceado->pai->fb = 0;
            } else {
                noDesbalanceado->fb = -1;
                filho->fb = 0;
                noDesbalanceado->pai->fb = 0;
            }
        } else {
            // rotação simples
            int fbFilho = filho->fb;
            rotacaoEsq(arv, noDesbalanceado);
            filho->fb = 0;
            noDesbalanceado->fb = 0;
            if (fbFilho == 0) {
                // só acontece na remoção
                // Ajustar o fb
                filho->fb = -1;
                noDesbalanceado->fb = 1;
            }
        }
    }
}

void rotacaoEsq(avl *arv, no *noDesbalanceado) {

    no *y = noDesbalanceado->pai;
    noDesbalanceado->pai = noDesbalanceado->Fdir;
    noDesbalanceado->Fdir = noDesbalanceado->pai->Fesq;
    if (noDesbalanceado->pai->Fesq != NULL) {
        noDesbalanceado->pai->Fesq->pai = noDesbalanceado;
    }
    noDesbalanceado->pai->Fesq = noDesbalanceado;
    noDesbalanceado->pai->pai = y;

    if (noDesbalanceado->chave >= y->chave) {
        y->Fdir = noDesbalanceado->pai;
    } else {
        y->Fesq = noDesbalanceado->pai;
    }

    arv->rotacoes++;
}

void rotacaoDir(avl *arv, no *noDesbalanceado) {

    no *y = noDesbalanceado->pai;

    noDesbalanceado->pai = noDesbalanceado->Fesq;
    noDesbalanceado->Fesq = noDesbalanceado->pai->Fdir;
    if (noDesbalanceado->Fesq != NULL) {
        noDesbalanceado->Fesq->pai = noDesbalanceado;
    }
    noDesbalanceado->pai->Fdir = noDesbalanceado;
    noDesbalanceado->pai->pai = y;

    if (noDesbalanceado->chave >= y->chave) {
        y->Fdir = noDesbalanceado->pai;
    } else {
        y->Fesq = noDesbalanceado->pai;
    }
    arv->rotacoes++;
}

no *getRaiz(avl *arv) { return arv->sentinela->Fdir; }

int getNumElementos(avl *arv) { return arv->numElementos; }

void imprimePreOrdem(no *raiz) {
    if (raiz != NULL) {
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        imprimePreOrdem(raiz->Fesq);
        imprimePreOrdem(raiz->Fdir);
    }
}

void imprimeOrdem(no *raiz) {
    if (raiz != NULL) {
        imprimeOrdem(raiz->Fesq);
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        imprimeOrdem(raiz->Fdir);
    }
}

int qtde_Rotacoes(avl *arv) {
    return arv->rotacoes;
}

int removeNo(avl *arv, int valor) {
    if (arv->numElementos == 0)
        return 0;

    no *atual = arv->sentinela->Fdir;

    while (atual != NULL && atual->chave != valor) {
        if (atual->chave <= valor)
            atual = atual->Fdir;
        else
            atual = atual->Fesq;
    }

    if (atual == NULL)
        return -1;

    arv->numElementos--;

    if (atual->Fdir == NULL && atual->Fesq == NULL) {
        if (atual->chave >= atual->pai->chave)
            atual->pai->Fdir = NULL;
        else
            atual->pai->Fesq = NULL;
        atualizaFB_remocao(arv, atual->pai, atual->chave);
        free(atual);
        return 1;
    }

    no *filho;
    if (atual->Fdir == NULL || atual->Fesq == NULL) {
        if (atual->Fesq != NULL)
            filho = atual->Fesq;
        else
            filho = atual->Fdir;

        if (atual->chave >= atual->pai->chave)
            atual->pai->Fdir = filho;
        else
            atual->pai->Fesq = filho;

        filho->pai = atual->pai;

        atualizaFB_remocao(arv, atual->pai, atual->chave);

        free(atual);

        return 1;
    }

    filho = atual->Fdir;
    while (filho->Fesq != NULL)
        filho = filho->Fesq;

    if (filho->Fdir != NULL) {
        filho->Fdir->pai = filho->pai;
    }

    if (filho->pai == atual) {
        filho->pai->Fdir = filho->Fdir;
    } else {
        filho->pai->Fesq = filho->Fdir;
    }

    atual->chave = filho->chave;

    atualizaFB_remocao(arv, filho->pai, filho->chave);

    free(filho);
    return 1;
}

void atualizaFB_remocao(avl *arv, no *paidoNo, int chave) {

    if (paidoNo == arv->sentinela)
        return;

    no *aux = paidoNo;

    if (chave >= aux->chave)
        aux->fb--;
    else
        aux->fb++;

    while (aux != arv->sentinela->Fdir && aux->fb == 0) {
        if (aux->chave >= aux->pai->chave) {
            aux->pai->fb--;
        } else {
            aux->pai->fb++;
        }

        aux = aux->pai;
    }

    if (aux->fb == 2 || aux->fb == -2) {
        balanceamento(arv, aux);
        if (aux->pai->fb == 0 && aux->pai->pai != arv->sentinela) {
            atualizaFB_remocao(arv, aux->pai->pai, aux->pai->chave);
        }
    }
}

no* encontraNo(avl *arv, int valor) {
    no *atual = arv->sentinela->Fdir;

    while (atual != NULL) {
        if (valor == atual->chave) {
            return atual;
        } else if (valor < atual->chave) {
            atual = atual->Fesq;
        } else {
            atual = atual->Fdir;
        }
    }

    printf("Elemento %d nao encontrado", valor);
    return NULL;
}

