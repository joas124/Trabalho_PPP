#ifndef TRABALHO_H_HEADERS_ALUNOS_H
#define TRABALHO_H_HEADERS_ALUNOS_H

/*
    ! Pede aluno
    * Return ponteiro para um se tudo correu bem
    * Return NULL se algum dos dados foi inserido incorretamente
    ? Dados que começam a 0 ou NULL:
        - Saldo
        - Despesas
    ? Dados Pedidos:
        - Nome do aluno
        - Data de nascimento
        - Número do aluno
        - Turma
*/
ALUNO * pede_aluno();

/*
    ! Inserir um novo aluno na lista
    * Return 1 se inseriu com sucesso
    * Return 0 se não inseriu
    Toggler serve para dizer quando é para inserir apenas na lista ou também no ficheiro
*/
int inserir_aluno(lista * l, ALUNO *aluno, int toggler);

/*
    ! Eliminar um aluno
    * Return 1 se eliminou com sucesso
    * Return 0 se não eliminou
    Apaga o aluno da lista (não apaga do ficheiro > basta reescrever o ficheiro)
*/
int eliminar_aluno(lista *l, int numero);

/*
    ! Procura aluno e mostra a sua informação toda
    * Return ponteiro para aluno se encontrou
    * Return NULL se não encontrou
    Usa o número de estudante para procurar
*/
ALUNO * procurar_aluno(lista *l, int numero);

/*
    ! Carregar conta de um aluno
    * Return 1 se carregou com sucesso
    * Return 0 se não carregou
*/
int carregar_conta(lista *l, int numero, double montante);

#endif //TRABALHO_H_HEADERS_ALUNOS_H