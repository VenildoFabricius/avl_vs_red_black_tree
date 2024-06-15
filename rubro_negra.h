#ifndef ATIVIDADE___COMPARACAO_AVL_E_RUBRO_NEGRA_RUBRO_NEGRA_H
#define ATIVIDADE___COMPARACAO_AVL_E_RUBRO_NEGRA_RUBRO_NEGRA_H

typedef struct no {
    int chave;
    struct no *pai, *esq, *dir;
    char cor;
} no;

typedef struct arv {
    no *sentinela;
    no *nulo;
    int rotacoes;
} arv;

arv *criar_arv_RN();

void inserir_no_RN(arv *T, int k);

void remover_no_RN(arv *T, no *z);

no *encontrar_no_RN(arv *T, int k);

void rotacao_esq_RN(arv *T, no *x);

void rotacao_dir_RN(arv *T, no *y);

void bal_inclusao_RN(arv *T, no *z);

void bal_remocao_RN(arv *T, no *x);

void transp_RN(arv *T, no *u, no *v);

int qtd_rotacoes_RN(arv *T);

void imprime_pre_ordem(arv *T, no *x);

#endif //ATIVIDADE___COMPARACAO_AVL_E_RUBRO_NEGRA_RUBRO_NEGRA_H
