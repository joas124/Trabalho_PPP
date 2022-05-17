#include "principal.h"
#include "auxiliar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clean() {
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}

/*
    ! Inicializa a lista
    * Return 1 se inicializou com sucesso
    * Return 0 se não conseguiu inicializar
*/
int inicializa_lista(lista *l) {
    if (l == NULL) return 0;
    l->inicio = NULL;
    return 1;
}

/*
    ! Inserir um novo aluno
    * Return 1 se inseriu com sucesso
    * Return 0 se não inseriu
*/
int inserir_aluno(lista *l, ALUNO *aluno) {
    if (l == NULL) return 0;
    no_lista *novo = malloc(sizeof(no_lista)); // reserva espaço para o novo aluno
    if (novo == NULL) return 0;                // se não conseguir reservar acaba a função
    novo->aluno = *aluno;                      // novo aluno é o aluno passado por parâmetro
    novo->prox = l->inicio;                    // o aluno asseguir ao novo agora é o inicio da lista
    l->inicio = novo;                          // o inicio é o novo aluno
    return 1;
}

/*
    ! Eliminar um aluno
    * Return 1 se eliminou com sucesso
    * Return 0 se não eliminou
    Usa o número de estudante para procurar pelo aluno
*/
int eliminar_aluno(lista *l, int numero) {
    no_lista *atual = l->inicio;
    no_lista *ant = NULL;
    while (atual != NULL) { // percorre a lista toda
        if (atual->aluno.numero == numero) {
            if (ant == NULL) l->inicio = atual->prox; // no caso de ser o primeiro aluno da lista: o inicio passa a ser o segundo aluno
            else ant->prox = atual->prox;             // nos outros casos: anterior aponta para o proximo
            free(atual);                              // liberta a memoria do aluno
            return 1;                                 // retorna 1 porque já foi eliminado
        }
        ant = atual;         // atualiza o anterior para o atual
        atual = atual->prox; // atual agora é o próximo
    }
    return 0; // não teve successo
}

/*
    ! Ordenar por ordem alfabética
    TODO: implementar usando dois whiles ou for's
    (CASO SEJA POSSIVEL)
    * Return 1 se ordenou com sucesso
    * Return 0 se não ordenou
*/
int ordena_alfabeticamente(lista *l) {
    if (l == NULL) return 0;
    no_lista *atual = l->inicio;
    while (atual != NULL) {
        no_lista *prox = atual->prox; // proximo é o proximo do atual
        while (prox != NULL) {
            if (strcmp(atual->aluno.nome, prox->aluno.nome) > 0) {
                ALUNO aux = atual->aluno;   // guarda o aluno atual
                atual->aluno = prox->aluno; // troca o aluno atual com o proximo
                prox->aluno = aux;          // troca o proximo com o aluno atual
            }
            prox = prox->prox; // continua em frente
        }
        atual = atual->prox; // continua em frente
    }
    return 1; // Sucesso
}

/*
    ! Mostrar os alunos com saldo abaixo de um determinado valor (decrescente)
    TODO: Provavelmente há uma maneira mais eficaz de fazer isso (NÃO FAZER UMA FUNÇÃO QUE PERCORRE A LISTA "l" MAIS DE UMA VEZ)
*/
void listar_alunos_saldo(lista *l, double saldo) {
    if (l == NULL) return;
    lista *novalista = malloc(sizeof(lista)); // Criar nova lista para os alunos com saldo inferior a "saldo"
    if (novalista == NULL) return; // Se não for possível alocar espaço, a função acaba
    novalista->inicio = NULL;
    no_lista *atual = l->inicio; // Ponteiro para percorrer a lista original
    no_lista *auxprox = NULL;    // Ponteiro auxilar para guardar a localização do próximo
    no_lista *auxatual = NULL;   // ''   ''  ''  ''  ''  ''  ''  ''  ''  ''  ''   atual (só é usado caso a lista nova já possua um elemento maior que o atual)
    while (atual != NULL) {
        double *saldoantigo = &atual->aluno.saldo;
        double *saldonovo = &novalista->inicio->aluno.saldo; // Só criei estas variáveis para o código dos if's ser menos poluído
        if (*saldoantigo <= saldo && (novalista->inicio == NULL || *saldonovo <= *saldoantigo))
        {                                              // Simplesmente adiciona um aluno ao topo da lista
            no_lista *novo = malloc(sizeof(no_lista)); // Aloca espaço na nova lista
            if (novo == NULL)
                break; // TODO Talvez aqui seja melhor um return, mas ainda tenho de perguntar ao professor
            novo->aluno = atual->aluno;
            novo->prox = novalista->inicio;
            novalista->inicio = novo;
        }
        else if (*saldoantigo <= saldo && *saldoantigo < *saldonovo)
        {
            // Caso o saldo seja menor que o número, mas o primeiro elemento da lista nova seja maior
            no_lista *novo = malloc(sizeof(no_lista)); // Aloca espaço na nova lista
            if (novo == NULL)
                break; // TODO
            novo->aluno = atual->aluno;
            auxatual = novalista->inicio;
            auxprox = novalista->inicio->prox;
            while (auxatual->aluno.saldo > *saldonovo)
            {
                // Percorrer a lista nova até encontrar um elemento com menor saldo
                auxatual = auxprox;
                auxprox = auxatual->prox;
            }
            auxatual->prox = novo;
            novo->prox = auxprox;
        }
        atual = atual->prox;
    }
    imprime_lista(novalista);
}

/*
    ! Carregar conta de um aluno
    * Return 1 se carregou com sucesso
    * Return 0 se não carregou
    Chama a função de procurar o aluno
*/
int carregar_conta(lista *l, int numero, double montante) {
    if (l == NULL) return 0;
    ALUNO *aluno = procurar_aluno(l, numero);
    if (aluno == NULL) return 0;
    unsigned int saldo = (aluno->saldo * 100); // converte o saldo para centimos
    saldo += (montante * 100);                 // adiciona saldo em centimos
    aluno->saldo = saldo / 100.0;              // transforma de centimos para euros again
    return 1;
}


void menu(lista *l){
    int n, numero;
    double saldo;
    opcoes(); // mostra as opções
    printf("Digite o número correspondente à operação que quer realizar: ");
    scanf("%d", &n);
    clean();
    switch (n) {
        case 1: {
            printf("Intruduzindo um aluno...\n");
            ALUNO * aluno = pede_aluno();
            if (aluno == NULL) {
                printf("Não foi possível introduzir o aluno.\n");
                break;
            }
            inserir_aluno(l, aluno);
            clean();
            break;
        }
        case 2: {
            printf("Digite o número do aluno que quer eliminar: ");
            scanf("%d", &numero);
            clean();
            if (eliminar_aluno(l, numero) == 1) printf("O aluno foi eliminado com sucesso\n");
            else printf("Não existe um aluno com este número\n");
            break;
        }
        case 3: {
            ordena_alfabeticamente(l);
            imprime_lista(l);
            break;
        }
        case 4: {
            printf("Listando alunos pelo seu saldo...\n");
            printf("Digite o saldo máximo: ");
            scanf("%lf", &saldo);
            clean();
            listar_alunos_saldo(l, saldo);
            break;
        }
        case 5: {
            printf("Listando informação de um aluno...\n");
            printf("Digite o número do aluno: ");
            scanf("%d", &numero);
            clean();
            imprime_aluno(procurar_aluno(l, numero));
            break;
        }
        case 6: {
            // TODO
            break;
        }
        case 7: {
            printf("Carregando conta de um aluno...\n");
            printf("Digite o número do aluno: ");
            scanf("%d", &numero);
            printf("Digite o valor que queres carregar: ");
            scanf("%lf", &saldo);
            carregar_conta(l, numero, saldo);
            clean();
            break;
        }
        default:
            printf("Opção inválida!\n");
            return;
    }
}