#ifndef TRABALHO_PPP_HEADERS_AUXILIAR_H
#define TRABALHO_PPP_HEADERS_AUXILIAR_H

#define MAX_NOME 100
#define MAX_TURMA 10
#define MAX_LINE 300

/*
    ! Apaga a consola
*/
void clean();

/*
    ! Número de digitos de um inteiro
*/
int len(int n);

/* 
    ! Auxiliar para o menu
*/
void opcoes();

/*
    ! Separador
*/
void separador();

/*
    ! Confirmar passo
    * Return 1 se confirmar
    * Return 0 se não confirmar
*/
int confirmar();

/*
    ! Verifica input
    * Return 1 se for válido
    * Return 0 se for inválido
*/
int verifica_input(int input);

/*
    ! Pede numero
    * Return numero
*/
int pede_numero();

/*
    ! Pede montante
    * Return montante
*/
double pede_montante();

/*
    ! Imprime dados do aluno
*/
void imprime_aluno(ALUNO *aluno);

/*
    ! Imprime nomes dos alunos ordem alfabetica
    * Return 1 se houver alguem na lista
    * Return 0 se lista estiver vazia
*/
int imprime_nomes(lista *l);

/*
    ! Mostrar os alunos com saldo abaixo de um determinado valor (decrescente)
*/
void listar_alunos_saldo(lista * l, double saldo);

/*
    ! Compara duas datas para ver qual a mais recente
    * Retorna 1 se a principal for mais recente ou caso sejam iguais
    * Retorna 0 se a principal for mais antiga
    * Retorna -1 se alguma das datas introduzidas é inválida
*/
int compara_data(DATA *dp, DATA *dc);

/*
    ! Mostra as despesas de um aluno
    * Retorna 1 se o aluno tiver despesas
    * Retorna 0 se o aluno não tiver despesas
    * Retorna -1 se não existir um aluno com o número inserido
    Chama a função de procurar o aluno
*/
int mostrar_despesas(lista *l, int numero);

/*
    ! Verifica nome
    * Return 1 se válido
    * Return 0 se inválido
*/
int verifica_nome(char *nome);

/*
    ! Verifica data
    * Return 1 se for válida
    * Return 0 se for inválida
*/
int verifica_data(DATA * d);

/*
    ! Verifica Numero de estudante
    * Return 1 se for válida
    * Return 0 se for inválida
*/
int verifica_numero(int numero);

/*
    ! Verifica turma
    * Return 1 se for inválida
    * Return 0 se for válida
*/
int verifica_turma(TURMA *t);

/*
    ! Verifica saldo
    * Return 1 se for válido
    * Return 0 se for inválido
*/
int verifica_saldo(double saldo);

#endif //TRABALHO_PPP_AUXILIAR_H
