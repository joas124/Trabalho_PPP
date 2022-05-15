#include "auxiliar.h"
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
    return 1;
}

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
        printf("Saldo: %.2f\n", aux->aluno.saldo);
        printf("\n");
        aux = aux->prox; // proximo aluno da lista
    }
}


/*
    ! Inserir um novo aluno
    * Return 1 se inseriu com sucesso
    * Return 0 se não inseriu
*/
int inserir_aluno(lista *l, ALUNO *aluno) {
    if (l == NULL) return 0;
    no_lista *novo = malloc(sizeof(no_lista)); // reserva espaço para o novo aluno
    if (novo == NULL) return 0; // se não conseguir reservar acaba a função
    novo->aluno = *aluno; // novo aluno é o aluno passado por parâmetro
    novo->prox = l->inicio; // o aluno asseguir ao novo agora é o inicio da lista
    l->inicio = novo; // o inicio é o novo aluno
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
    while (atual != NULL) { // percorre a lista toda
        if (atual->aluno.numero == numero) {
            if (ant == NULL) l->inicio = atual->prox; // no caso de ser o primeiro aluno da lista: o inicio passa a ser o segundo aluno
            else ant->prox = atual->prox; // nos outros casos: anterior aponta para o proximo
            free(atual); // liberta a memoria do aluno
            return 1; // retorna 1 porque já foi eliminado
        }
        ant = atual; // atualiza o anterior para o atual
        atual = atual->prox; // atual agora é o próximo
    }
    return 0; // não teve successo
}


/*
    ! Ordenar por ordem alfabética
    TODO: implementar usando dois whiles ou for's
    (CASO SEJA POSSIVEL)
    * Return 1 se ordenou com sucesso
    * Return 0 se não ordenou
*/
int ordena_alfabeticamente(lista *l) {
    if (l == NULL) return 0;
    no_lista *atual = l->inicio;
    while (atual != NULL) {
        no_lista *prox = atual->prox; // proximo é o proximo do atual
        while (prox != NULL) {
            if (strcmp(atual->aluno.nome, prox->aluno.nome) > 0) {
                ALUNO aux = atual->aluno; // guarda o aluno atual
                atual->aluno = prox->aluno; // troca o aluno atual com o proximo
                prox->aluno = aux; // troca o proximo com o aluno atual
            }
            prox = prox->prox; // continua em frente
        }
        atual = atual->prox; // continua em frente
    }
    return 1; // Sucesso
}

/*
    ! Mostrar os alunos com saldo abaixo de um determinado valor (decrescente)
    TODO
*/
void listar_alunos_saldo(lista * l, double saldo);

/*
    ! Imprime dados do aluno
    ? Função auxiliar
*/
void imprime_aluno(ALUNO *aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Data de nascimento: %d/%d/%d\n", aluno->data_nascismento.dia, aluno->data_nascismento.mes, aluno->data_nascismento.ano);
    printf("Turma: %dº %s\n", aluno->turma.ano, aluno->turma.sigla);
    printf("Numero: %d\n", aluno->numero);
    printf("Saldo: %.2f\n", aluno->saldo);
    printf("\n");
}

/*
    ! Procura aluno e mostra a sua informação toda
    ? Função auxiliar
    * Return ponteiro para aluno se encontrou
    * Return NULL se não encontrou
    Usa o número de estudante para procurar
*/
ALUNO * procurar_aluno(lista *l, int numero) {
    no_lista *atual = l->inicio;
    while (atual != NULL) { // percorre a lista toda
        if (atual->aluno.numero == numero) {
            // imprime_aluno(&(atual->aluno));
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
void mostrar_despesas(lista *l, int numero){
    if (l == NULL) return;
    ALUNO * aluno = procurar_aluno(l, numero);
    if (aluno == NULL) return;
    NO_DESPESAS *desp = aluno->despesas->inicio;
    while (desp != NULL){
        printf("%s: %lf\n%d/%d/%d\n",desp->despesa.descricao, desp->despesa.valor, desp->despesa.data.dia,desp->despesa.data.mes,desp->despesa.data.ano);
        desp = desp->proximo;
    }
}

/*
    ! Carregar conta de um aluno
    * Return 1 se carregou com sucesso
    * Return 0 se não carregou
    Chama a função de procurar o aluno
*/
int carregar_conta(lista *l, int numero, double montante) {
    if (l == NULL) return 0;
    ALUNO * aluno = procurar_aluno(l, numero);
    if (aluno == NULL) return 0;
    aluno->saldo = aluno->saldo + montante;
    return 1;
}
