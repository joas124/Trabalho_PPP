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
    ! Pede alunos
    * Return ponteiro para lista de alunos se tudo correu bem
    * Return NULL se algum dos dados foi inserido incorretamente
*/
ALUNO * pede_aluno();

#endif //TRABALHO_PPP_AUXILIAR_H
