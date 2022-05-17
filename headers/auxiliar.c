#include "principal.h"
#include "auxiliar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>

/*
    ! Imprime a lista
*/
void imprime_lista(lista *l) {
    if (l == NULL) return;
    no_lista *aux = l->inicio;
    while (aux != NULL) { // percorre a lista
        printf("Nome: %s\n", aux->aluno.nome);
        printf("Data de nascimento: %d/%d/%d\n", aux->aluno.data_nascismento.dia, aux->aluno.data_nascismento.mes, aux->aluno.data_nascismento.ano);
        printf("Turma: %dº %s\n", aux->aluno.turma.ano, aux->aluno.turma.sigla);
        printf("Numero: %d\n", aux->aluno.numero);
        printf("Saldo: %.2f\n", (aux->aluno.saldo));
        printf("\n");
        aux = aux->prox; // proximo aluno da lista
    }
}

/*
    ! Imprime dados do aluno
*/
void imprime_aluno(ALUNO *aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Data de nascimento: %d/%d/%d\n", aluno->data_nascismento.dia, aluno->data_nascismento.mes,
            aluno->data_nascismento.ano);
    printf("Turma: %dº %s\n", aluno->turma.ano, aluno->turma.sigla);
    printf("Numero: %d\n", aluno->numero);
    printf("Saldo: %.2f\n", aluno->saldo);
    printf("\n");
}

/*
    ! Procura aluno e mostra a sua informação toda
    * Return ponteiro para aluno se encontrou
    * Return NULL se não encontrou
    Usa o número de estudante para procurar
*/
ALUNO * procurar_aluno(lista *l, int numero) {
    no_lista *atual = l->inicio;
    while (atual != NULL) { // percorre a lista toda
        if (atual->aluno.numero == numero) {
            return &(atual->aluno);
        }
        atual = atual->prox; // atual agora é o próximo
    }
    return NULL; // não teve successo
}

/*
    ! Mostra as despesas de um aluno
    Chama a função de procurar o aluno
*/
void mostrar_despesas(lista *l, int numero) {
    if (l == NULL) return;
    ALUNO *aluno = procurar_aluno(l, numero);
    if (aluno == NULL) return;
    NO_DESPESAS *desp = aluno->despesas->inicio;
    while (desp != NULL) {
        printf("%s: %lf\n%d/%d/%d\n", desp->despesa.descricao, desp->despesa.valor, desp->despesa.data.dia,
                desp->despesa.data.mes, desp->despesa.data.ano);
        desp = desp->proximo;
    }
}

/* 
    ! Auxiliar para o menu
*/
void opcoes() {
    printf("1 - Introduzir um novo aluno\n");
    printf("2 - Eliminar um aluno existente\n");
    printf("3 - Listar os alunos por ordem alfabética\n");
    printf("4 - Listar os alunos com saldo abaixo de um determinado valor\n");
    printf("5 - Apresentar toda a informação de um aluno\n");
    printf("6 - Efectuar uma despesa para um aluno\n");
    printf("7 - Carregar a conta de um aluno\n");
    printf("0 - Sair\n");
}

/*
    ! Número de digitos de um inteiro
*/
int len(int n) {
    if(n == 0) return 1;
    int count = 0;
    for (; n != 0; n /= 10) count++;
    return count;
}

/*
    ! Verifica data
    * Return 1 se for inválida
    * Return 0 se for válida
*/
int verifica_data(DATA * d) {
    // Vê o ano atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_atual = tm.tm_year + 1900;

    if (d->dia < 1 || d->dia > 31 || d->mes < 1 || d->mes > 12 ||
        (d->mes == 2 && d->dia > 29) || (d->mes == 2 && d->dia > 28 &&
        d->ano % 4 != 0 && (d->ano % 100 == 0) && d->ano % 400 != 0) ||
        (d->mes == 4 && d->dia > 30) || (d->mes == 6 && d->dia > 30) ||
        (d->mes == 9 && d->dia > 30) || (d->mes == 11 && d->dia > 30) ||
        (d->ano >  ano_atual || d->ano < 1980)) 
    {
        return  1;
    }
    return 0;
}

/*
    ! Verifica Numero de estudante
    * Return 1 se for inválida
    * Return 0 se for válida
*/
int verifica_numero(int numero) {
    if (len(numero) != 10) return 1;
    return 0;
}

/*
    ! Verifica turma
    * Return 1 se for inválida
    * Return 0 se for válida
*/
int verifica_turma(TURMA *t) {
    const char p[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (t->ano < 1 || t->ano > 12) return 1;
    for (int i = 0; i < 27; i++) if (t->sigla[1] == p[i]) return 0;
    return 1;
}

/*
    TODO: PERGUNTAR AO PROFESSOR SE A MELHOR MANEIRA DE LER CARACTER É ASSIM
    ! Confirmar passo
    * Return 1 se confirmar
    * Return 0 se não confirmar
    Só confirma se for 's' ou 'S'
    Nega todos os outros inputs
*/
int confirmar() {
    char c;
    printf("Confirmar? (S/N): ");
    scanf(" %c", &c);
    if (toupper(c) == 'S') return 1;
    printf("Operação cancelada\n");
    return 0;
}
