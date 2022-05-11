#include <stdio.h>
#include "aux.h"
#include <stdlib.h>

// TODO: Secção de testes (para não estar a testar no main.c)

int main() {
    /*
        * NÃO PEDIR SALDO INICIAL 
        * NÃO PEDIR DESPESAS INICIAIS
        ! Logo em baixo são apenas os testes das funções por isso não apagar!
    */
    lista l;
    inicializa_lista(&l);
    ALUNO aluno1 = {
        "Joao Anibal",
        {20, 11, 2003},
        {1, "A1"},
        2021218054,
        100.0,
        NULL
    };
    inserir_aluno(&l, &aluno1);
    ALUNO aluno2 = {
        "Filipe",
        {10, 2, 2005},
        {1, "A1"},
        2021218124,
        103.24,
        NULL
    };
    inserir_aluno(&l, &aluno2);
    ALUNO aluno3 = {
        "Joao Animal",
        {30, 1, 2010},
        {1, "A1"},
        2021219958,
        23.64,
        NULL
    };
    inserir_aluno(&l, &aluno3);

    /* TESTE PARA ELIMINAR ALUNO */
    // imprime_lista(&l);
    // eliminar_aluno(&l, 2021218124);
    // imprime_lista(&l);

    /* TESTE PARA ORDENAR LISTA */
    // imprime_lista(&l);
    // printf("\n-----------\n");
    // ordena_alfabeticamente(&l);
    // imprime_lista(&l);

    /* TESTE PARA PROCURAR ALUNO */
    procurar_aluno(&l, 2021218054);

    return 0;
}
