#include "principal.h"
#include "auxiliar.h"
#include "alunos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_TURMA 10
#define MAX_LINE 300

ALUNO * pede_aluno() {
    int erro = 0; // quando erro = 1 a função return NULL

    // Pede Nome
    char nome[MAX_NOME];
    printf("Nome do aluno: ");
    while (getchar() != '\n'); // Apanha o ultimo '\n' para que não interfira o input
    fgets(nome, MAX_NOME, stdin);
    nome[strlen(nome) - 1] = '\0'; // Troca o '\n' do fim da string

    // Pede Data de Nascimento
    DATA nascimento;
    printf("Data nascimento (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &nascimento.dia, &nascimento.mes, &nascimento.ano);

    // Pede Numero
    printf("Número de estudante: ");
    int numero = pede_numero();

    // Pede Turma
    TURMA turma;
    char t[MAX_TURMA];
    while (getchar() != '\n');
    printf("Ano e Turma (10-12): ");
    fgets(t, MAX_TURMA, stdin);
    t[strlen(t) - 1] = '\0'; // Troca o '\n' do fim da string
    turma.ano = (int) strtol(t, NULL, MAX_TURMA);
    strcpy(turma.sigla, t + 3);

    // Handle erros
    erro = !(verifica_nome(nome) && verifica_data(&nascimento) && verifica_numero(numero)) || verifica_turma(&turma);
    if (erro) { // erro = 1
        printf("Algum dos parâmetros não é válido.\n");
        return NULL;
    }

    // Confirma dados
    if (confirmar() == 0) return NULL; // Utilizador não confirmou
    ALUNO * a = malloc(sizeof(ALUNO));
    if (a == NULL) {
        free(a);
        return NULL;
    };

    // Passa os dados para a struct
    strcpy(a->nome, nome);
    a->data_nascimento = nascimento;
    a->numero = numero;
    a->turma = turma;
    a->saldo = 0.00;
    a->num_despesas = 0;
    inicializa_despesa(a);

    return a; // Retorna o aluno
}

int inserir_aluno(lista *l, ALUNO *aluno, int toggler) {
    if (procurar_aluno(l, aluno->numero) != NULL) {
        printf("Já existe um aluno com o número inserido\n");
        return 0;
    }
    no_lista *novo = malloc(sizeof(no_lista)); // reserva espaço para o novo aluno
    if (novo == NULL) return 0;                // se não conseguir reservar acaba a função
    novo->aluno = *aluno;                      // novo aluno é o aluno passado por parâmetro
    novo->prox = l->inicio;                    // o aluno asseguir ao novo agora é o inicio da lista
    l->inicio = novo;                          // o inicio é o novo aluno

    if (toggler == 1) inserir_aluno_ficheiro(aluno);

    return 1;
}

int eliminar_aluno(lista *l, int numero) {
    no_lista *aux = l->inicio;
    no_lista *ant = NULL;
    while (aux != NULL) {
        if (aux->aluno.numero == numero) {
            if (ant == NULL) l->inicio = aux->prox;
            else ant->prox = aux->prox;
            NO_DESPESAS *desp_ant = aux->aluno.despesas->inicio;
            if (desp_ant != NULL) {
                NO_DESPESAS *desp_aux = aux->aluno.despesas->inicio->proximo;
                while (desp_aux != NULL) {
                    free(desp_ant);
                    desp_ant = desp_aux;
                    desp_aux = desp_aux->proximo;
                }
            }
            free(aux);
            return 1;
        }
        ant = aux;
        aux = aux->prox;
    }
    return 0;
}

ALUNO * procurar_aluno(lista *l, int numero) {
    no_lista *atual = l->inicio;
    while (atual != NULL) { // percorre a lista toda
        if (atual->aluno.numero == numero) return &(atual->aluno);
        atual = atual->prox; // atual agora é o próximo
    }
    return NULL; // não teve successo
}

int carregar_conta(lista *l, int numero, double montante) {
    ALUNO *aluno = procurar_aluno(l, numero);
    if (aluno == NULL) {
        printf("Aluno não encontrado\n");
        return 0;
    }
    unsigned int saldo = (aluno->saldo * 100); // converte o saldo para centimos
    saldo += (montante * 100);                 // adiciona saldo em centimos
    aluno->saldo = saldo / 100.0;              // transforma de centimos para euros again
    return 1;
}