#ifndef TRABALHO_H_HEADERS_PRINCIPAL_H
#define TRABALHO_H_HEADERS_PRINCIPAL_H

#define ALUNOS_FILE "alunos.txt"

typedef struct data {
    int dia, mes, ano;
} DATA;

typedef struct turma {
    int ano;       // ex: 1
    char sigla[10]; // ex: A1BCD
} TURMA; // 1º ano de turma A1

typedef struct despesas {
    double valor;
    char descricao[101];
    DATA data;
} DESPESAS;

typedef struct no_despesas {
    DESPESAS despesa;
    struct no_despesas *proximo;
} NO_DESPESAS;

typedef struct lista_despesas{
    struct no_despesas *inicio;
} LISTA_DESPESAS;

typedef struct aluno {
    char nome[101];
    DATA data_nascimento;
    TURMA turma;
    int numero; // numero de estudante
    double saldo; // só numeros positivos
    int num_despesas; // Dá puta jeito guardar o número de despesas de um aluno
    LISTA_DESPESAS *despesas; // antes era um pointer para uma só despesa, agora é para a lista ligada de despesas
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
    nome: dia/mes/ano | ano | sigla | numero | saldo | num_despesas
    despesa: valor | dia/mes/ano
*/
int inicializa_lista(lista *l);

/*
    ! Inicializa as depesas de um aluno
    * Retorna 1 caso consiga inicializar
    * Retorna 0 caso contrário
*/
int inicializa_despesa(ALUNO *a);

/*
    ! Cria a despesa para um aluno
    * Se conseguir criar da return a 1
    * Caso contrário, da return a 0
    * Se o aluno não tiver saldo suficiente, dá return a "-1"
*/
int criar_despesa(lista *l, DATA data, int numero, double montante, const char descricao[]);

/*
    ! Reescreve o ficheiro dos alunos
    * Return 1 se conseguiu
    * Return 0 se não conseguiu
*/
int reescreve_ficheiro(lista *l);

/*
    ! Inserir aluno no ficheiro
    * Return 1 se inseriu com sucesso
    * Return 0 se não conseguiu inserir
*/
int inserir_aluno_ficheiro(ALUNO *aluno);

/*
    ! Ordenar por ordem alfabética
    * Return 1 se ordenou com sucesso
    * Return 0 se não ordenou
*/
int ordena_alfabeticamente(lista *l);

/*
    ! Ordenar por saldo decrescente
    * Return 1 se ordenou com sucesso
    * Return 0 se não ordenou
*/
int ordena_saldo(lista *l);

/*
    ! Mostra o menu completo
    * Return 1 se o utilizador quiser continuar
    * Return 0 se o utilizador quiser sair
*/
int menu(lista *l);

#endif //TRABALHO_H_HEADERS_PRINCIPAL_H