#include "principal.h"
#include "auxiliar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    ! Pede alunos
    * Return ponteiro para lista de alunos se tudo correu bem
    * Return NULL se algum dos dados foi inserido incorretamente
*/
ALUNO * pede_aluno() {
    int erro = 0;
    // Pede Nome
    char nome[100];
    printf("Nome do aluno: ");
    scanf("%s", nome); // TODO: Lembrar de segurança

    // Pede Data de Nascimento
    DATA nascimento;
    printf("Data nascimento (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &nascimento.dia, &nascimento.mes, &nascimento.ano);
    /*
        * Verifica se a data é válida
        Inclui todas as excepções
    */
    if (nascimento.dia < 1 || nascimento.dia > 31 || nascimento.mes < 1 || nascimento.mes > 12 ||
        (nascimento.mes == 2 && nascimento.dia > 29) || (nascimento.mes == 2 && nascimento.dia > 28 &&
        nascimento.ano % 4 != 0 && (nascimento.ano % 100 == 0) && nascimento.ano % 400 != 0) ||
        (nascimento.mes == 4 && nascimento.dia > 30) || (nascimento.mes == 6 && nascimento.dia > 30) ||
        (nascimento.mes == 9 && nascimento.dia > 30) || (nascimento.mes == 11 && nascimento.dia > 30))
    {
        printf("Data inválida\n");
        erro = 1;
    }

    // Pede Numero
    int numero;
    printf("Número de estudante: ");
    scanf("%d", &numero);
    if (len(numero) != 10) {
        printf("Número inválido\n");
        erro = 1;
    }

    // Pede turma
    TURMA turma;
    printf("Turma (12º 3A): ");
    scanf("%dº %s", &turma.ano, turma.sigla);

    // Handle erros
    if (erro) { // erro = 1
        printf("Algum dos parâmetros não é válido.\n");
        return NULL;
    }

    ALUNO * a = malloc(sizeof(ALUNO));
    if (a == NULL) return NULL;
    strcpy(a->nome, nome);
    a->data_nascismento = nascimento;
    a->turma = turma;
    a->numero = numero;
    a->saldo = 0.00;
    a->despesas = NULL;
    return a;
}
