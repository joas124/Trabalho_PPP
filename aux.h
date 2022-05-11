#ifndef TRABALHO_PPP_AUX_H
#define TRABALHO_PPP_AUX_H

typedef struct data {
    int dia;
    int mes;
    int ano;
} DATA;

typedef struct turma {
    int ano;       // ex: 1
    char sigla[3]; // ex: "A1"
} TURMA; // 1º ano de turma A1

typedef struct despesas {
    int valor;
    char descricao[100];
    DATA data;
} DESPESAS;

typedef struct no_despesas {
    DESPESAS despesa;
    struct no_despesas *proximo;
} NO_DESPESAS;

typedef struct aluno {
    char nome[101];
    DATA data_nascismento;
    TURMA turma;
    int numero; // numero de estudante
    double saldo; // só numeros positivos
    DESPESAS * despesas;
} ALUNO;

typedef struct no_lista {
    ALUNO aluno;
    struct no_lista *prox;
} no_lista;

typedef struct lista {
    struct no_lista *inicio;
} lista;

/*
    ! Inicializa a lista
    * Return 1 se inicializou com sucesso
    * Return 0 se não conseguiu inicializar
*/
int inicializa_lista(lista *l);

/*
    ! Imprime a lista
*/
void imprime_lista(lista *l);

/*
    ! Inserir um novo aluno
    * Return 1 se inseriu com sucesso
    * Return 0 se não inseriu
*/
int inserir_aluno(lista * l, ALUNO *aluno);

/*
    ! Eliminar um aluno
    * Return 1 se eliminou com sucesso
    * Return 0 se não eliminou
    Usa o número de estudante para procurar pelo aluno
*/
int eliminar_aluno(lista *l, int numero);

/*
    ! Ordenar por ordem alfabética
    * Return 1 se ordenou com sucesso
    * Return 0 se não ordenou
*/
int ordena_alfabeticamente(lista *l);

/*
    ! Listar os alunos com saldo abaixo de um determinado valor (decrescente)
*/
void listar_alunos_saldo(lista * l, double saldo);

/*
    ! Imprime dados do aluno
*/
void imprime_aluno(ALUNO *aluno);

/*
    ! Procura aluno e mostra a sua informação toda
    * Return 1 se encontrou
    * Return 0 se não encontrou
    Usa o número de estudante para procurar
*/
int procurar_aluno(lista *l, int numero);

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
int carregar_conta(lista *l, int numero, double montante);

#endif //TRABALHO_PPP_AUX_H