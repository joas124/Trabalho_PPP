#include "principal.h"
#include "auxiliar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>

/*
    ! Imprime a lista
*/
void imprime_lista(lista *l) {
    if (l == NULL) return;
    no_lista *aux = l->inicio;
    while (aux != NULL) { // percorre a lista
        printf("Nome: %s\n", aux->aluno.nome);
        printf("Data de nascimento: %d/%d/%d\n", aux->aluno.data_nascimento.dia, aux->aluno.data_nascimento.mes, aux->aluno.data_nascimento.ano);
        printf("Turma: %dº %s\n", aux->aluno.turma.ano, aux->aluno.turma.sigla);
        printf("Numero: %d\n", aux->aluno.numero);
        printf("Saldo: %.2f\n", (aux->aluno.saldo));
        printf("\n");
        aux = aux->prox; // proximo aluno da lista
    }
}

/*
    ! Imprime nomes dos alunos ordem alfabetica
    * Return 1 se houver alguem na lista
    * Return 0 se lista estiver vazia
*/
int imprime_nomes(lista *l) {
    if (l == NULL) return 0;
    no_lista *aux = l->inicio;
    if (aux == NULL) return 0;
    for (; aux != NULL; aux = aux->prox) printf("%s\n", aux->aluno.nome);
    return 1;
}

/*
    ! Imprime dados do aluno
*/
void imprime_aluno(ALUNO *aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Data de nascimento: %d/%d/%d\n", aluno->data_nascimento.dia, aluno->data_nascimento.mes,
            aluno->data_nascimento.ano);
    printf("Turma: %dº %s\n", aluno->turma.ano, aluno->turma.sigla);
    printf("Numero: %d\n", aluno->numero);
    printf("Saldo: %.2lf\n", aluno->saldo);
}

/*
    ! Procura aluno e mostra a sua informação toda
    * Return ponteiro para aluno se encontrou
    * Return NULL se não encontrou
    Usa o número de estudante para procurar
*/
ALUNO * procurar_aluno(lista *l, int numero) {
    no_lista *atual = l->inicio;
    while (atual != NULL) { // percorre a lista toda
        if (atual->aluno.numero == numero) {
            return &(atual->aluno);
        }
        atual = atual->prox; // atual agora é o próximo
    }
    return NULL; // não teve successo
}

/*
    ! Função Auxiliar para converter datas
    Converte uma data DD/MM/AAAA em dias para
    poder comparar datas mais facilmente
    Retorna -1 se não conseguir converter
    Se conseguir, retorna o número de dias
    (Dá demasiado trabalho, vou desistir dela só)
*/

int converte_data(DATA *data){
    if (verifica_data(data) == 0) return -1;
    int d = data->dia;
    int anosbis = (data->ano % 4) - (data->ano - len(data->ano) + 2);
    int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    d += (data->ano - anosbis)*365 + anosbis*366;
    for (int i = 0; i < data->mes -2; ++i){
        d += meses[i];
        }
    return d;
}
/*
    ! Compara duas datas para ver qual a mais recente
    Retorna 1 se a principal for mais recente ou caso sejam iguais
    Retorna 0 se a principal for mais antiga
    Retorna -1 se alguma das datas introduzidas é inválida
    (Desisti de ordenar a lista de despessas, apenas ignore)
*/
int compara_data(DATA *dataprincipal, DATA *datacomp){
    if ((verifica_data(dataprincipal) && verifica_data(datacomp)) == 0) return -1;
    if (datacomp->ano > dataprincipal->ano) return 0;
    if ((datacomp->ano == dataprincipal->ano) && (datacomp->mes > dataprincipal->mes)) return 0;
    if ((datacomp->ano == dataprincipal->ano) && (datacomp->mes == dataprincipal->mes) && (datacomp->dia > dataprincipal->dia)) return 0;
    return 1;
}

/*
    ! Mostra as despesas de um aluno
    Chama a função de procurar o aluno
*/

void mostrar_despesas(lista *l, int numero) {
    if (l == NULL) return;
    ALUNO *aluno = procurar_aluno(l, numero);
    if (aluno == NULL) return;
    NO_DESPESAS *desp = aluno->despesas->inicio;
    while (desp != NULL) {
        printf("%s: %.02lf (%d/%d/%d)\n", desp->despesa.descricao, desp->despesa.valor, desp->despesa.data.dia,
                desp->despesa.data.mes, desp->despesa.data.ano);
        desp = desp->proximo;
    }
}

/*
    ! Cria a despesa para um aluno
    Chama a função de procurar o aluno
    Se conseguir criar da return a "1"
    Caso contrário, da return a "0"
    Se o aluno não tiver saldo suficiente, dá return a "-1"
*/
int criar_despesas(lista *l, DATA data, int numero, double montante, const char descricao[]){
    if (l == NULL) return 0;
    ALUNO *aluno = procurar_aluno(l, numero);
    NO_DESPESAS *nova_despesa = malloc(sizeof(NO_DESPESAS));
    DESPESAS *despesa = malloc(sizeof (DESPESAS));
    if ((nova_despesa == NULL) || (aluno == NULL)) return 0; //Verifica se consegui alocar espaço para a despesa e o aluno foi encontrado
    if (aluno->saldo < montante) return -1; //Retorna caso o aluno não tenha saldo suficiente
    aluno->saldo -= montante; //Subtrair a despesa do saldo do aluno
    despesa->valor = montante;
    despesa->data = data;
    strcpy(despesa->descricao,descricao);
    nova_despesa->despesa = *despesa;
    nova_despesa->proximo = aluno->despesas->inicio;
    aluno->despesas->inicio = nova_despesa;
    return 1;
}

/* 
    ! Auxiliar para o menu
*/
void opcoes() {
    printf("1 - Introduzir um novo aluno\n");
    printf("2 - Eliminar um aluno existente\n");
    printf("3 - Listar os alunos por ordem alfabética\n");
    printf("4 - Listar os alunos com saldo abaixo de um determinado valor\n");
    printf("5 - Apresentar toda a informação de um aluno\n");
    printf("6 - Efectuar uma despesa para um aluno\n");
    printf("7 - Listar as despesas de um aluno\n");
    printf("8 - Carregar a conta de um aluno\n");
    printf("0 - Sair\n");
}

/*
    ! Número de digitos de um inteiro
*/
int len(int n) {
    if(n == 0) return 1;
    int count = 0;
    for (; n != 0; n /= 10) count++;
    return count;
}

/*
    ! Verifica nome
    * Return 1 se inválido
    * Return 0 se válido
*/
int verifica_nome(char *nome) {
    if (nome == NULL) return 1;
    int i = 0;
    for (; nome[i] != '\0'; i++) { // vai até o caracter da string que é '\0'
        if (toupper((nome[i]) < 'A' || toupper(nome[i]) > 'Z') && nome[i] != ' ') {
            return 1;
        }
    }
    return 0;
}

/*
    ! Verifica data
    * Return 1 se for inválida
    * Return 0 se for válida
*/
int verifica_data(DATA * d) {
    // Vê o ano atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_atual = tm.tm_year + 1900;
    if (d->dia < 1 || d->dia > 31 || d->mes < 1 || d->mes > 12 ||
        (d->mes == 2 && d->dia > 29) || (d->mes == 2 && d->dia > 28 &&
        d->ano % 4 != 0 && (d->ano % 100 == 0) && d->ano % 400 != 0) ||
        (d->mes == 4 && d->dia > 30) || (d->mes == 6 && d->dia > 30) ||
        (d->mes == 9 && d->dia > 30) || (d->mes == 11 && d->dia > 30) ||
        (d->ano >  ano_atual || d->ano < 1980)) 
    {
        return 1;
    }
    return 0;
}

/*
    ! Verifica Numero de estudante
    * Return 1 se for inválida
    * Return 0 se for válida
*/
int verifica_numero(int numero) {
    return (numero < 0) || (len(numero) != 10); 
}

/*
    ! Verifica turma
    * Return 1 se for inválida
    * Return 0 se for válida
*/
int verifica_turma(TURMA *t) {
    return (t->ano < 1 || t->ano > 12);
}

/*
    ! Verifica saldo
    * Return 1 se for válido
    * Return 0 se for inválido
*/
int verifica_saldo(double saldo) {
    return saldo > 0;
}

/*
    ! Confirmar passo
    * Return 1 se confirmar
    * Return 0 se não confirmar
*/
int confirmar() {
    char confirma[3];
    printf("Confirmar? (S/N): ");
    // while (getchar() != '\n');
    fgets(confirma, 3, stdin);
    if(toupper(confirma[0]) == 'S') return 1;
    printf("Operação cancelada\n");
    return 0;
}

/*
    ! Verifica input
    * Return 1 se for válido
    * Return 0 se for inválido
*/
int verifica_input(int input) {
    return (input >= 0 && input <= 7);
}

/*
    ! Pede numero
    * Return numero
*/
int pede_numero() {
    char num[11];
    while (getchar() != '\n'); // Apanha o ultimo '\n' para que não interfira o input
    fgets(num, 11, stdin);
    return (int) strtol(num, NULL, 10);
}

/*
    ! Pede montante
    * Return montante
*/
double pede_montante() {
    char num[11];
    while (getchar() != '\n'); // Apanha o ultimo '\n' para que não interfira o input
    fgets(num, 11, stdin);
    return strtod(num, NULL);
}