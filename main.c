#include <stdio.h>
#include "aux.h"
#include <stdlib.h>

int main() {
    /*
        * NÃO PEDIR SALDO INICIAL 
        * NÃO PEDIR DESPESAS INICIAIS
        ! Logo em baixo são apenas os testes das funções por isso não apagar!
    */
    lista l;
    inicializa_lista(&l);
    ALUNO aluno1 = {
        "Mariana",
        {20, 11, 2003},
        {1, "A1"},
        2021218054,
        100.0,
        NULL
    };
    inserir_aluno(&l, &aluno1);
    ALUNO aluno2 = {
        "Joao",
        {10, 2, 2005},
        {1, "A1"},
        2021218124,
        103.24,
        NULL
    };
    inserir_aluno(&l, &aluno2);
    ALUNO aluno3 = {
        "Filipe",
        {30, 1, 2010},
        {1, "A1"},
        2021219958,
        23.64,
        NULL
    };
    inserir_aluno(&l, &aluno3);

    // imprime_lista(&l);
    // eliminar_aluno(&l, 2021218124);
    printf("\n----\n");
    imprime_lista(&l);
    printf("\n----\n");
    ordena_alfabetica(&l);
    imprime_lista(&l);
    return 0;
}
