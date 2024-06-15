#include "ops_avl.h"
#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void operacoes_avl(){
    avl *arv;
    int i, j, elem, qtd = 10000, rot_ins, rot_rem, num_testes = 10;
    double t_total_ins = 0, t_total_rem = 0, t_total_busca = 0, t_medio_ins, t_medio_rem, t_medio_busca;
    clock_t t_ini_ins, t_fim_ins, t_ini_rem, t_fim_rem, t_ini_busca, t_fim_busca;

    for (i = 0; i < num_testes; i++) {
        arv = criaArvore();

        // INSERÇÃO
        t_ini_ins = clock();
        for (j = 1; j <= qtd; j++) {
            insereNo(arv, j);
        }
        t_fim_ins = clock();
        t_total_ins += (double) (t_fim_ins - t_ini_ins) * 1000 / CLOCKS_PER_SEC;
        rot_ins = qtde_Rotacoes(arv);

        arv->rotacoes = 0;
        // BUSCA
        t_ini_busca = clock();
        for (j = 0; j < 1000; j++) {
            elem = 1 + (rand() % qtd);
            encontraNo(arv, elem);
        }
        t_fim_busca = clock();
        t_total_busca += (double) (t_fim_busca - t_ini_busca) * 1000 / CLOCKS_PER_SEC;

        // REMOÇÃO
        t_ini_rem = clock();
        for (j = 1; j <= qtd; j++) {
            removeNo(arv, j);
        }
        t_fim_rem = clock();
        t_total_rem += (double) (t_fim_rem - t_ini_rem) * 1000 / CLOCKS_PER_SEC;
        rot_rem = qtde_Rotacoes(arv);

        t_medio_ins = t_total_ins / num_testes;
        t_medio_busca = t_total_busca / num_testes;
        t_medio_rem = t_total_rem / num_testes;
    }

    printf("\nRESULTADOS AVL");
    printf("\na) Insercao de 10.000 valores ordenados\n\tTempo medio: %.2f ms\n", t_medio_ins);
    printf("\tQuantidade de rotacoes: %d\n", rot_ins);
    printf("\nb) Remocao de 10.000 valores ordenados\n\tTempo medio: %.2f ms\n", t_medio_rem);
    printf("\tQuantidade de rotacoes: %d\n", rot_rem);
    printf("\nc) Busca de 1.000 elementos aleatorios \n\tTempo medio: %.2f ms\n", t_medio_busca);

    free(arv);
}
