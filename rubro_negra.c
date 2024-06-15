#include <stdio.h>
#include <stdlib.h>
#include "rubro_negra.h"

#define RUBRO 0
#define NEGRO 1

arv *criar_arv_RN() {
    arv *T;

    T = malloc(sizeof(arv));
    T->nulo = malloc(sizeof(no));

    T->nulo->cor = NEGRO;

    T->sentinela = malloc(sizeof(no));
    T->sentinela->dir = T->nulo;
    T->sentinela->esq = NULL;
    T->sentinela->cor = NEGRO;
    T->sentinela->pai = T->nulo;
    T->sentinela->chave = -1000;
    T->rotacoes = 0;

    return T;
}

void inserir_no_RN(arv *T, int k) {
    no *z, *x, *y;

    z = malloc(sizeof(no));
    z->chave = k;

    y = T->nulo;
    x = T->sentinela->dir;

    while (x != T->nulo) {
        y = x;
        if (k < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }

    z->pai = y;
    if (y == T->nulo)
        T->sentinela->dir = z;
    else if (k < y->chave)
        y->esq = z;
    else
        y->dir = z;

    z->esq = z->dir = T->nulo;
    z->cor = RUBRO;
    bal_inclusao_RN(T, z);

    // Atualização do pai da raiz
    T->sentinela->dir->pai = T->sentinela;
}

void remover_no_RN(arv *T, no *z) {
    no *x, *y;
    char cor_origem;

    y = z;
    cor_origem = y->cor;

    if (z->esq == T->nulo) {
        x = z->dir;
        transp_RN(T, z, x);
    } else if (z->dir == T->nulo) {
        x = z->esq;
        transp_RN(T, z, x);
    } else {
        y = z->esq;
        while (y->dir != T->nulo)
            y = y->dir;
        x = y->esq;
        cor_origem = y->cor;
        transp_RN(T, y, x);

        y->dir = z->dir;
        z->dir->pai = y;
        y->esq = z->esq;
        z->esq->pai = y;
        transp_RN(T, z, y);
        y->cor = z->cor;
    }
    if (cor_origem == NEGRO)
        bal_remocao_RN(T, x);
}

no *encontrar_no_RN(arv *T, int k) {
    no *x = T->sentinela->dir;

    while (x != T->nulo) {
        if (k == x->chave)
            return x;
        if (k < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    return T->nulo;
}

void rotacao_esq_RN(arv *T, no *x) {
    no *y;
    y = x->dir;

    x->dir = y->esq;
    if (y->esq != T->nulo)
        y->esq->pai = x;

    y->pai = x->pai;
    if (x->pai == T->nulo)
        T->sentinela->dir = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;
    T->rotacoes++;
}

void rotacao_dir_RN(arv *T, no *y) {
    no *x;
    x = y->esq;

    y->esq = x->dir;
    if (x->dir != T->nulo)
        x->dir->pai = y;

    x->pai = y->pai;
    if (y->pai == T->nulo)
        T->sentinela->dir = x;
    else if (y == y->pai->esq)
        y->pai->esq = x;
    else
        y->pai->dir = x;

    x->dir = y;
    y->pai = x;
    T->rotacoes++;
}

void bal_inclusao_RN(arv *T, no *z) {
    no *y;

    while (z->pai->cor == RUBRO) {
        if (z->pai == z->pai->pai->esq) { // 3 casos
            y = z->pai->pai->dir;
            if (y->cor == RUBRO) { // Caso 1
                z->pai->cor = NEGRO;
                y->cor = NEGRO;
                z = y->pai;
                z->cor = RUBRO;
            } else {
                if (z == z->pai->dir) { // Caso 2
                    z = z->pai;
                    rotacao_esq_RN(T, z);
                }
                // Caso 3
                z->pai->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                rotacao_dir_RN(T, z->pai->pai);
            }
        } else { // 3 casos simétricos
            y = z->pai->pai->esq;
            if (y->cor == RUBRO) { // Caso 1 simétrico
                z->pai->cor = NEGRO;
                y->cor = NEGRO;
                z = y->pai;
                z->cor = RUBRO;
            } else {
                if (z == z->pai->esq) { // Caso 2 simétrico
                    z = z->pai;
                    rotacao_dir_RN(T, z);
                }
                // Caso 3 simétrico
                z->pai->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                rotacao_esq_RN(T, z->pai->pai);
            }
        }
    }
    T->sentinela->dir->cor = NEGRO;
}

void bal_remocao_RN(arv *T, no *x) {
    no *w;

    while (x != T->sentinela->dir && x->cor == NEGRO) {
        if (x == x->pai->esq) { // 4 casos
            w = x->pai->dir;
            if (w->cor == RUBRO) { // Caso 1
                w->cor = NEGRO;
                x->pai->cor = RUBRO;
                rotacao_esq_RN(T, x->pai);
                w = x->pai->dir;
            }
            if (w->esq->cor == NEGRO && w->dir->cor == NEGRO) { // Caso 2
                w->cor = RUBRO;
                x = x->pai;
            } else {
                if (w->dir->cor == NEGRO) { // Caso 3
                    w->esq->cor = NEGRO;
                    w->cor = RUBRO;
                    rotacao_dir_RN(T, x->pai);
                    w = x->pai->dir;
                }
                // Caso 4
                w->cor = x->pai->cor;
                x->pai->cor = NEGRO;
                w->dir->cor = NEGRO;
                rotacao_esq_RN(T, x->pai);
                x = T->sentinela->dir;
            }
        } else { // 4 casos simétricos
            w = x->pai->esq;
            if (w->cor == RUBRO) { // Caso 1 simétrico
                w->cor = NEGRO;
                x->pai->cor = RUBRO;
                rotacao_dir_RN(T, x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == NEGRO && w->esq->cor == NEGRO) { // Caso 2 simétrico
                w->cor = RUBRO;
                x = x->pai;
            } else {
                if (w->esq->cor == NEGRO) { // Caso 3 simétrico
                    w->dir->cor = NEGRO;
                    w->cor = RUBRO;
                    rotacao_esq_RN(T, x->pai);
                    w = x->pai->esq;
                }
                // Caso 4 simétrico
                w->cor = x->pai->cor;
                x->pai->cor = NEGRO;
                w->esq->cor = NEGRO;
                rotacao_dir_RN(T, x->pai);
                x = T->sentinela->dir;
            }
        }
    }
    x->cor = NEGRO;
}

void transp_RN(arv *T, no *u, no *v) {
    if (u->pai == T->nulo)
        T->sentinela->dir = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    v->pai = u->pai;
}

int qtd_rotacoes_RN(arv *T){
    return T->rotacoes;
}

void imprime_pre_ordem(arv *T, no *x) {
    if (x != T->nulo) {
        printf("%d - %d - %s\n", x->chave, x->pai->chave, x->cor == RUBRO ? "R" : "N");
        imprime_pre_ordem(T, x->esq);
        imprime_pre_ordem(T, x->dir);
    }
}
