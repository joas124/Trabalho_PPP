#ifndef TRABALHO_PPP_HEADERS_AUXILIAR_H
#define TRABALHO_PPP_HEADERS_AUXILIAR_H

/*
    ! Imprime a lista
*/
void imprime_lista(lista *l);

/*
    ! Imprime nomes dos alunos ordem alfabetica
*/
int imprime_nomes(lista *l);

/*
    ! Imprime dados do aluno
*/
void imprime_aluno(ALUNO *aluno);

/*
    ! Procura aluno e mostra a sua informação toda
    * Return ponteiro para aluno se encontrou
    * Return NULL se não encontrou
    Usa o número de estudante para procurar
*/
ALUNO * procurar_aluno(lista *l, int numero);

/*
    ! Mostra as despesas de um aluno
    Chama a função de procurar o aluno
*/

int converte_data(DATA *data);

void mostrar_despesas(lista *l, int numero);

/*
    ! Cria uma despesa para um aluno
    Chama a função de procurar aluno
    Se conseguir criar da return a "1"
    Caso contrário, da return a "0"
 */

int criar_despeas(lista *l, int numero, double valor, DATA *data);

/* 
    ! Auxiliar para o menu
*/
void opcoes();

/*
    ! Número de digitos de um inteiro
*/
int len(int n);

/*
    ! Verifica nome
    * Return 1 se inválido
    * Return 0 se válido
*/
int verifica_nome(char *nome);

/*
    ! Verifica Data
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
    * Return 1 se for inválida
    * Return 0 se for válida
*/
int verifica_saldo(double saldo);

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

#endif //TRABALHO_PPP_AUXILIAR_H
