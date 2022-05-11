#include "aux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    ! Inicializa a lista
    * Return 1 se inicializou com sucesso
    * Return 0 se não conseguiu inicializar
*/
int inicializa_lista(lista *l) {
    if (l == NULL) return 0;
    l->inicio = NULL;
    printf("Lista inicializada com sucesso!\n");
    return 1;
}

/*
    ! Imprime a lista
*/
void imprime_lista(lista *l) {
    if (l == NULL) return;
    no_lista *aux = l->inicio;
    while (aux != NULL) {
        printf("Nome: %s\n", aux->aluno.nome);
        printf("Data de nascimento: %d/%d/%d\n", aux->aluno.data_nascismento.dia, aux->aluno.data_nascismento.mes, aux->aluno.data_nascismento.ano);
        printf("Turma: %dº %s\n", aux->aluno.turma.ano, aux->aluno.turma.sigla);
        printf("Numero: %d\n", aux->aluno.numero);
        printf("Saldo: %.2f\n", aux->aluno.saldo);
        printf("\n");
        aux = aux->prox;
    }
}

/*
    ! Inserir um novo aluno
    * Return 1 se inseriu com sucesso
    * Return 0 se não inseriu
*/
int inserir_aluno(lista *l, ALUNO *aluno) {
    printf("Inserindo aluno...\n");
    if (l == NULL) return 0;
    no_lista *no = malloc(sizeof(no_lista));
    if (no == NULL) return 0;
    no->aluno = *aluno;
    no->prox = l->inicio;
    l->inicio = no;
    return 1;
}

/*
    ! Eliminar um aluno
    * Return 1 se eliminou com sucesso
    * Return 0 se não eliminou
    Usa o número de estudante para procurar pelo aluno
*/
int eliminar_aluno(lista *l, int numero) {
    no_lista *atual = l->inicio;
    no_lista *ant = NULL;
    while (atual != NULL) {
        if (atual->aluno.numero == numero) {
            if (ant == NULL) l->inicio = atual->prox;
            else ant->prox = atual->prox;
            free(atual);
            printf("Aluno eliminado com sucesso!\n\n");
            return 1;
        }
        ant = atual;
        atual = atual->prox;
    }
    return 0;
}


/*
    ! Ordenar por ordem alfabética
    TODO: implementar usando dois whiles ou for's
*/
void ordena_alfabetica(lista *l);

/*
    ! Listar os alunos com saldo abaixo de um determinado valor (decrescente)
*/
void listar_alunos_saldo(lista * l, double saldo);

/*
    ! Procura aluno e mostra a sua informação toda
    Usa o número de estudante para procurar
*/
void procurar_aluno(lista *l, int numero);

/*
    ! Mostra as despesas de um aluno
    Usa o número de estudante para procurar
*/
void mostrar_despesas(lista *l, int numero);

/*
    ! Carregar conta de um aluno
    * Return 1 se carregou com sucesso
    * Return 0 se não carregou
    Usa o número de estudante
*/
int carregar_conta(lista *l, double montante);
