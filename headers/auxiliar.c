#include "principal.h"
#include "auxiliar.h"
#include "alunos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>

void clean() {
    #if defined(_WIN32) // se for windows
        system("cls"); /* Nao está disponivel para o CLion -> rodar no Terminal */
    #else
        system("clear");
    #endif
}

int len(int n) {
    if(n == 0) return 1;
    int count = 0;
    for (; n != 0; n /= 10) count++;
    return count;
}

void opcoes() {
    printf("1 - Introduzir um novo aluno\n");
    printf("2 - Eliminar um aluno existente\n");
    printf("3 - Listar os alunos por ordem alfabetica\n");
    printf("4 - Listar os alunos com saldo abaixo de um determinado valor\n");
    printf("5 - Apresentar toda a informacao de um aluno\n");
    printf("6 - Efectuar uma despesa para um aluno\n");
    printf("7 - Listar as despesas de um aluno\n");
    printf("8 - Carregar a conta de um aluno\n");
    printf("0 - Sair\n");
}

void separador() {
    printf("----------------------------------------------------\n");
}

int confirmar() {
    char confirma[3];
    printf("Confirmar? (S/N): ");
    fgets(confirma, 3, stdin);
    if(toupper(confirma[0]) == 'S') return 1;
    printf("Operacao cancelada\n");
    return 0;
}

int verifica_input(int input) {
    return (input >= 0 && input <= 7);
}

int pede_numero() {
    char num[11];
    while (getchar() != '\n'); // Apanha o ultimo '\n' para que nao interfira o input
    fgets(num, 11, stdin);
    return (int) strtol(num, NULL, 10);
}

double pede_montante() {
    char num[11];
    while (getchar() != '\n'); // Apanha o ultimo '\n' para que nao interfira o input
    fgets(num, 11, stdin);
    return strtod(num, NULL);
}

void imprime_aluno(ALUNO *aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Data de nascimento: %d/%d/%d\n", aluno->data_nascimento.dia, aluno->data_nascimento.mes,
            aluno->data_nascimento.ano);
    printf("Turma: %dº %s\n", aluno->turma.ano, aluno->turma.sigla);
    printf("Numero: %d\n", aluno->numero);
    printf("Saldo: %.2lf\n", aluno->saldo);
}

int imprime_nomes(lista *l) {
    no_lista *a = l->inicio;
    if (a == NULL) return 0;
    for (; a != NULL; a = a->prox) printf("%s (%d)\n", a->aluno.nome, a->aluno.numero);
    return 1;
}

void listar_alunos_saldo(lista *l, double saldo) {
    no_lista *a = l->inicio;
    if (a == NULL) return;
    ordena_saldo(l);
    for (; a != NULL; a = a->prox) {
        if (a->aluno.saldo < saldo) printf("%s (%d)\n", a->aluno.nome, a->aluno.numero);
    }
}

int compara_data(DATA *dp, DATA *dc){
    if (!verifica_data(dp) || !verifica_data(dc)) return -1;
    if (dc->ano > dp->ano) return 0;
    if ((dc->ano == dp->ano) && (dc->mes >= dp->mes) && (dc->dia > dp->dia)) return 0;
    return 1;
}

int mostrar_despesas(lista *l, int numero) {
    ALUNO *aluno = procurar_aluno(l, numero);
    if (aluno == NULL) return -1;
    NO_DESPESAS *desp = aluno->despesas->inicio;
    if (desp == NULL) return 0;
    printf("Despesas de %s (%d):\n", aluno->nome, aluno->numero);
    for (; desp != NULL; desp = desp->proximo) {
        printf("%s: %.02lf | %d/%d/%d\n", desp->despesa.descricao, desp->despesa.valor, desp->despesa.data.dia, desp->despesa.data.mes, desp->despesa.data.ano);
    }
    return 1;
}

int verifica_nome(char *nome) {
    if (nome == NULL) return 0;
    for (int i = 0; nome[i] != '\0'; i++) { // vai ate o caracter da string que e '\0'
        if (toupper((nome[i]) < 'A' || toupper(nome[i]) > 'Z') && nome[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

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
        return 0;
    }
    return 1;
}

int verifica_numero(int numero) {
    return (numero > 0) && (len(numero) == 10); 
}

int verifica_turma(TURMA *t) {
    for (int i = 0; t->sigla[i] != '\0'; i++) {
        if (toupper(t->sigla[i]) >= 'A' || toupper(t->sigla[i]) <= 'Z') {
            t->sigla[i] = toupper(t->sigla[i]);
        } else if (t->sigla[i] >= '0' || t->sigla[i] <= '9') {
            continue;
        } else {
            return 0;
        }
    }
    // Se a verificacao em cima nao der return a 0, entao a vericidade da turma fica pelo ano
    return (t->ano < 1 || t->ano > 12);
}

int verifica_saldo(double saldo) {
    return saldo >= 0; // pode ser de graca
}
