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
    ! Compara duas datas para ver qual a mais recente
    Retorna 1 se a principal for mais recente
    Retorna 0 se a principal for mais antiga
    Retorna -1 se alguma das datas introduzidas é inválida
*/
int compara_data(DATA *dataprincipal, DATA *datacomp);

/*
    ! Mostra as despesas de um aluno
    Retorna 1 se o aluno tiver despesas
    Retorna 0 se o aluno não tiver despesas
    Retorna -1 se não existir um aluno com o número inserido
    Chama a função de procurar o aluno
*/
int mostrar_despesas(lista *l, int numero);

/*
    ! Inicializa as depesas de um aluno
    Retorna 1 caso consiga inicializar
    Retorna 0 caso contrário
    (Criado para resolver um bug que acontecia
    caso o aluno não possuísse despesas ao ser
    lido do ficheiro)
 */

int inicializa_despesa(ALUNO *a);

/*
    ! Cria a despesa para um aluno
    Chama a função de procurar o aluno
    Se conseguir criar da return a "1"
    Caso contrário, da return a "0"
    Se o aluno não tiver saldo suficiente, dá return a "-1"
 */
int criar_despesas(lista *l, DATA data, int numero, double montante, const char descricao[]);

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
    * Return 1 se for válido
    * Return 0 se for inválido
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

#endif //TRABALHO_PPP_AUXILIAR_H
