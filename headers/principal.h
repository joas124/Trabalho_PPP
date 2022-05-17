#ifndef TRABALHO_H_HEADERS_PRINCIPAL_H
#define TRABALHO_H_HEADERS_PRINCIPAL_H

typedef struct data {
    int dia, mes, ano;
} DATA;

typedef struct turma {
    int ano;       // ex: 1
    char sigla[3]; // ex: "A1"
} TURMA; // 1º ano de turma A1

typedef struct despesas {
    double valor;
    char descricao[100];
    DATA data;
} DESPESAS;

typedef struct no_despesas {
    DESPESAS despesa;
    struct no_despesas *proximo;
} NO_DESPESAS;

typedef struct lista_despesas
{
    struct no_despesas *inicio;
} LISTA_DESPESAS;


typedef struct aluno {
    char nome[101];
    DATA data_nascismento;
    TURMA turma;
    int numero; // numero de estudante
    double saldo; // só numeros positivos
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
    ! Apaga a consola
*/
void clean();

/*
    ! Inicializa a lista
    * Return 1 se inicializou com sucesso
    * Return 0 se não conseguiu inicializar
*/
int inicializa_lista(lista *l);

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
    ! Carregar conta de um aluno
    * Return 1 se carregou com sucesso
    * Return 0 se não carregou
    Chama a função de procurar o aluno
*/
int carregar_conta(lista *l, int numero, double montante);

/*
    ! Pede alunos
    * Return ponteiro para lista de alunos se tudo correu bem
    * Return NULL se algum dos dados foi inserido incorretamente
*/
ALUNO * pede_aluno();

/*
    ! Mostra o menu completo
    * Return 1 se o utilizador quiser continuar
    * Return 0 se o utilizador quiser sair
*/
int menu(lista *l);

#endif //TRABALHO_H_PRINCIPAL_H