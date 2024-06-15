#include "ops_rn.h"
#include "rubro_negra.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void operacoes_rn(){
    arv *arv;
    int i, j, elem, qtd = 10000, rot_ins, rot_rem, num_testes = 10;
    double t_total_ins = 0, t_total_rem = 0, t_total_busca = 0, t_medio_ins, t_medio_rem, t_medio_busca;
    clock_t t_ini_ins, t_fim_ins, t_ini_rem, t_fim_rem, t_ini_busca, t_fim_busca;

    for (i = 0; i < num_testes; i++) {
        arv = criar_arv_RN();

        // INSERÇÃO
        t_ini_ins = clock();
        for (j = 1; j <= qtd; j++) {
            inserir_no_RN(arv, j);
        }
        t_fim_ins = clock();
        t_total_ins += (double) (t_fim_ins - t_ini_ins) * 1000 / CLOCKS_PER_SEC;
        rot_ins = qtd_rotacoes_RN(arv);

        // BUSCA
        t_ini_busca = clock();
        for (j = 0; j < 1000; j++) {
            elem = 1 + (rand() % qtd);
            encontrar_no_RN(arv, elem);
        }
        t_fim_busca = clock();
        t_total_busca += (double) (t_fim_busca - t_ini_busca) * 1000 / CLOCKS_PER_SEC;

        arv->rotacoes = 0;
        // REMOÇÃO
        t_ini_rem = clock();
        for (j = 1; j <= qtd; j++) {
            no *z = encontrar_no_RN(arv, j);
            if (z)
                remover_no_RN(arv, z);
        }
        t_fim_rem = clock();
        t_total_rem += (double) (t_fim_rem - t_ini_rem) * 1000 / CLOCKS_PER_SEC;
        rot_rem = qtd_rotacoes_RN(arv);

        t_medio_ins = t_total_ins / num_testes;
        t_medio_busca = t_total_busca / num_testes;
        t_medio_rem = t_total_rem / num_testes;
    }

    printf("\nRESULTADOS RUBRO NEGRA");
    printf("\na) Insercao de 10.000 valores ordenados\n\tTempo medio: %.2f ms\n", t_medio_ins);
    printf("\tQuantidade de rotacoes: %d\n", rot_ins);
    printf("\nb) Remocao de 10.000 valores ordenados\n\tTempo medio: %.2f ms\n", t_medio_rem);
    printf("\tQuantidade de rotacoes: %d\n", rot_rem);
    printf("\nc) Busca de 1.000 elementos aleatorios \n\tTempo medio: %.2f ms\n", t_medio_busca);

    free(arv);
}

