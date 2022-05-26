#include "principal.h"
#include "auxiliar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define MAX_NOME 100
#define MAX_TURMA 10

void clean() {
    #if defined(_WIN32)
        // system("cls"); /* Não está disponivel para o CLion (provavelmenta buga) */
    #else
        system("clear");
    #endif
}

/*
    ! Refaz o ficheiro de alunos
    * Return 1 se conseguiu
    * Return 0 se não conseguiu
*/
int reescreve_ficheiro(lista *l) {
    FILE *f = fopen("../alunos.txt", "w");
    if (f == NULL) return 0;
    no_lista *aux = l->inicio;
    while (aux != NULL) {
        aux->aluno.nome[strlen(aux->aluno.nome)] = '\0'; // Quick fix no ficheiro
        fprintf(f, "%s| %d/%d/%d | %d | %s | %d | %.2f\n", aux->aluno.nome, aux->aluno.data_nascimento.dia,
                aux->aluno.data_nascimento.mes, aux->aluno.data_nascimento.ano, aux->aluno.turma.ano,
                aux->aluno.turma.sigla, aux->aluno.numero, aux->aluno.saldo);
        aux = aux->prox;
    }
    fclose(f);
    return 1;
}

/*
    ! Inicializa a lista
    * Return 1 se inicializou com sucesso
    * Return 0 se não conseguiu inicializar
*/
int inicializa_lista(lista *l) {
    if (l == NULL) return 0;
    l->inicio = NULL;
    FILE *file = fopen("../alunos.txt", "r");
    if (file == NULL) return 0;
    ALUNO * a = malloc(sizeof(ALUNO));
    if (a == NULL) {
        free(a);
        return 0;
    };

    char line[MAX_NOME + MAX_TURMA + 100 + 10 + 10 + 10];
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^|] | %d/%d/%d | %d | %s | %d | %lf", a->nome, &a->data_nascimento.dia, &a->data_nascimento.mes, &a->data_nascimento.ano, &a->turma.ano, a->turma.sigla, &a->numero, &a->saldo);
        inserir_aluno(l, a, 0);
    }
    free(a);
    fclose(file);
    return 1;
}

/*
    ! Inserir aluno no ficheiro
    * Return 1 se inseriu com sucesso
    * Return 0 se não conseguiu inserir
*/
int aluno_ficheiro(ALUNO *aluno) {
    FILE *file = fopen("../alunos.txt", "a+");
    if (file == NULL) return 0;
    fprintf(file, "%s | %d/%d/%d | %d | %s | %d | %.2lf\n", aluno->nome, aluno->data_nascimento.dia, aluno->data_nascimento.mes, aluno->data_nascimento.ano, aluno->turma.ano, aluno->turma.sigla, aluno->numero, aluno->saldo);
    fclose(file);
    return 1;
}

/*
    ! Inserir um novo aluno
    * Return 1 se inseriu com sucesso
    * Return 0 se não inseriu
*/
int inserir_aluno(lista *l, ALUNO *aluno, int toggler) {
    if (l == NULL) return 0; // se não existir nenhum aluno com esse numero
    if (procurar_aluno(l, aluno->numero) != NULL) {
        printf("Já existe um aluno com o número inserido\n");
        return 0;
    }
    no_lista *novo = malloc(sizeof(no_lista)); // reserva espaço para o novo aluno
    if (novo == NULL) return 0;                // se não conseguir reservar acaba a função
    novo->aluno = *aluno;                      // novo aluno é o aluno passado por parâmetro
    novo->prox = l->inicio;                    // o aluno asseguir ao novo agora é o inicio da lista
    l->inicio = novo;                          // o inicio é o novo aluno

    // Escrever no final do ficheiro os dados do novo aluno
    // OBS: não reescreve o ficheiro, apenas adiciona o novo aluno
    if (toggler == 1) aluno_ficheiro(aluno);

    return 1;
}

/*
    ! Eliminar um aluno
    * Return 1 se eliminou com sucesso
    * Return 0 se não eliminou
*/
// apaga o aluno da lista e do ficheiro
int eliminar_aluno(lista *l, int numero) {
    if (l == NULL) return 0;
    FILE *file = fopen("../alunos.txt", "w");
    if (file == NULL) return 0;
    no_lista *aux = l->inicio;
    no_lista *ant = NULL;
    while (aux != NULL) {
        if (aux->aluno.numero == numero) {
            if (ant == NULL) l->inicio = aux->prox;
            else ant->prox = aux->prox;
            NO_DESPESAS *despant = aux->aluno.despesas->inicio;
            NO_DESPESAS *despaux = aux->aluno.despesas->inicio->proximo;
            while(despaux != NULL){
                free(despant);
                despant = despaux;
                despaux = despaux->proximo;
            }
            free(aux);
            reescreve_ficheiro(l);
            return 1;
        }
        ant = aux;
        aux = aux->prox;
    }
    return 0;
}

/*
    ! Ordenar por ordem alfabética
    * Return 1 se ordenou com sucesso
    * Return 0 se não ordenou
*/
int ordena_alfabeticamente(lista *l) {
    if (l == NULL) return 0;
    no_lista *atual = l->inicio;
    if (atual == NULL) return 0;
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
    reescreve_ficheiro(l);
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
    if (aluno == NULL) {
        printf("Aluno não encontrado\n");
        return 0;
    }
    unsigned int saldo = (aluno->saldo * 100); // converte o saldo para centimos
    saldo += (montante * 100);                 // adiciona saldo em centimos
    aluno->saldo = saldo / 100.0;              // transforma de centimos para euros again
    return 1;
}

/*
    ! Pede alunos
    * Return ponteiro para lista de alunos se tudo correu bem
    * Return NULL se algum dos dados foi inserido incorretamente
    ? Dados Pedidos:
        - Nome do aluno
        - Data de nascimento
        - Número do aluno
        - Turma
    ? Dados que começam a 0:
        - Saldo
        - Despesas
*/
ALUNO * pede_aluno() {
    int erro = 0; // quando erro = 1 a função return NULL

    // Pede Nome
    char nome[MAX_NOME];
    printf("Nome do aluno: ");
    while (getchar() != '\n'); // Apanha o ultimo '\n' para que não interfira o input
    fgets(nome, MAX_NOME, stdin);
    nome[strlen(nome) - 1] = '\0'; // Troca o '\n' do fim da string

    // Pede Data de Nascimento
    DATA nascimento;
    printf("Data nascimento (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &nascimento.dia, &nascimento.mes, &nascimento.ano);

    // Pede Numero
    printf("Número de estudante: ");
    int numero = pede_numero();

    // Pede turma
    TURMA turma;
    char t[MAX_TURMA];
    while (getchar() != '\n');
    printf("Ano e Turma (10-12): ");
    fgets(t, MAX_TURMA, stdin);
    t[strlen(t) - 1] = '\0'; // Troca o '\n' do fim da string
    turma.ano = (int) strtol(t, NULL, MAX_TURMA);
    strcpy(turma.sigla, t + 3);

    // Handle erros
    erro = verifica_nome(nome) || verifica_data(&nascimento) || verifica_numero(numero) || verifica_turma(&turma);
    if (erro) { // erro = 1
        printf("Algum dos parâmetros não é válido.\n");
        return NULL;
    }

    // Confirma dados
    if (confirmar() == 0) return NULL; // Utilizador não confirmou
    ALUNO * a = malloc(sizeof(ALUNO));
    if (a == NULL) {
        free(a);
        return NULL;
    };

    // Passa os dados para a struct
    strcpy(a->nome, nome);
    a->data_nascimento = nascimento;
    a->numero = numero;
    a->turma = turma;
    a->saldo = 0.00;
    a->despesas = malloc(sizeof(NO_DESPESAS));
    a->despesas->inicio = NULL;

    return a; // Retorna o aluno
}

int menu(lista *l) {
    int input, numero;
    double saldo, despesa;
    char descricao[100];
    DATA data;
    opcoes(); // mostra as opções
    printf("Digite o número correspondente à operação que quer realizar: ");
    if (scanf("%d", &input) == 0) { // faz com que dê handle ao infinite loop do input
        input = -1;
        while (getchar() != '\n'); // Apanha o ultimo '\n' para que não interfira o input
    }

    clean();

    switch (input) {
        case 0: { // ! Sair do programa
            printf("Fim do programa\n");
            return 0;
        }
        case 1: { // ! Inserir aluno
            printf("Intruduzindo um aluno...\n");
            ALUNO * aluno = pede_aluno();
            if (aluno == NULL) {
                printf("Aluno inválido\n");
                printf("----------------------------------------------------\n");
                break;
            }
            clean();
            if (inserir_aluno(l, aluno, 1)) printf("Aluno inserido com sucesso!\n");
            printf("----------------------------------------------------\n");
            break;
        }
        case 2: { // ! Remover aluno
            printf("Digite o número do aluno que quer eliminar: ");
            numero = pede_numero();
            if (confirmar() == 0) break;
            clean();
            if (eliminar_aluno(l, numero)) printf("O aluno foi eliminado com sucesso\n");
            else printf("Não foi encontrado nenhum aluno com este número\n");
            printf("----------------------------------------------------\n");
            break;
        }
        case 3: { // ! Ordenar alunos e imprimir apenas os nomes
            ordena_alfabeticamente(l);
            if (imprime_nomes(l) == 0) printf("Não existem alunos na lista\n");
            printf("----------------------------------------------------\n");
            break;
        }
        case 4: { // ! Imprimir alunos com saldo inferior a um determinado valor «« AINDA NÃO ACABADO
            printf("Listando alunos pelo seu saldo...\n");
            printf("Digite o saldo máximo:");
            saldo = pede_montante();
            if (verifica_saldo(saldo) == 0) {
                clean();
                printf("Montante inválido\n");
                printf("----------------------------------------------------\n");
                break;
            }
            clean();
            listar_alunos_saldo(l, saldo);
            printf("----------------------------------------------------\n");
            break;
        }
        case 5: {
            printf("Listando informação de um aluno...\n");
            printf("Digite o número do aluno: ");
            numero = pede_numero();
            if (procurar_aluno(l, numero) == NULL) {
                clean();
                printf("Não foi encontrado nenhum aluno com este número\n");
                printf("----------------------------------------------------\n");
                break;
            }
            clean();
            imprime_aluno(procurar_aluno(l, numero));
            printf("----------------------------------------------------\n");
            break;
        }
        case 6: {
            printf("Efetuando uma despesa de um aluno...\n");
            printf("Digite o número do aluno: ");
            numero = pede_numero();
            if (procurar_aluno(l, numero) == NULL){
                clean();
                printf("Número inválido\n");
                break;
            }
            printf("Digite o valor da despesa: ");
            scanf("%lf", &despesa);
            if (verifica_saldo(despesa) == 0) {
                clean();
                printf("Montante inválido\n");
                break;
            }
            printf("Digite a descrição da despesa: ");
            scanf("%s", descricao);
            if (strlen(descricao) == 0){
                clean();
                printf("Descrição inválida\n");
                break;
            }
            printf("Digite a data de faturação da despesa(DD/MM/AAAA): ");
            scanf("%d/%d/%d",&data.dia, &data.mes, &data.ano);
            if (verifica_data(&data) == 1){
                clean();
                printf("Data inválida!");
                break;
            }
            if (confirmar() == 0) break;
            clean();
            switch (criar_despesas(l, data, numero, despesa, descricao)) {
                case 0:
                    printf("Não foi possível criar a despesa\n");
                    break;
                case -1:
                    printf("O aluno não possui saldo suficiente\n");
                    break;
                default:
                    printf("Despesa criada com sucesso\n");
                    break;
            };
            break;
        }
        case 7: //TODO Falta implementar uma função que diga se as despesas estão vazias
            printf("Listando as despesas de um aluno..\n");
            printf("Digite o número do aluno: ");
            numero = pede_numero();
            if (verifica_numero(numero) == 0) {
                clean();
                printf("Número inválido\n");
                break;
            }
            mostrar_despesas(l,numero);
            break;
        case 8: { // ! Carregar conta de um aluno
            printf("Carregando conta de um aluno...\n");
            printf("Digite o número do aluno: ");
            numero = pede_numero();

            printf("Digite o valor para carregar: ");
            saldo = pede_montante();
            if (verifica_saldo(saldo) == 0) {
                clean();
                printf("Montante não válido\n");
                printf("----------------------------------------------------\n");
                break;
            }
            if (confirmar() == 0) break;
            clean();
            if (carregar_conta(l, numero, saldo)) {
                printf("Conta carregada com sucesso\n");
                reescreve_ficheiro(l);
            }
            else printf("Não foi possível carregar a conta\n");
            printf("----------------------------------------------------\n");
            break;
        }
        default: { // ! Não mexer mais neste case
            printf("Opção inválida!\n");
            printf("----------------------------------------------------\n");
            break;
        }
    }
    return 1;
}