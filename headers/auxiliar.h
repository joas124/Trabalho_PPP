#ifndef TRABALHO_PPP_HEADERS_AUXILIAR_H
#define TRABALHO_PPP_HEADERS_AUXILIAR_H

/*
    ! Imprime a lista
*/
void imprime_lista(lista *l);

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
void mostrar_despesas(lista *l, int numero);

/* 
    ! Auxiliar para o menu
*/
void opcoes();

/*
    ! Número de digitos de um inteiro
*/
int len(int n);

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
    ! Confirmar passo
    * Return 1 se confirmar
    * Return 0 se não confirmar
*/
int confirmar();

#endif //TRABALHO_PPP_AUXILIAR_H
