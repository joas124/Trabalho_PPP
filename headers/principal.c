#include "principal.h"
#include "auxiliar.h"
#include "alunos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

int inicializa_lista(lista *l) {
    if (l == NULL) return 0;
    l->inicio = NULL;
    FILE *f = fopen(ALUNOS_FILE, "a+"); // a+ -> abre para leitura e escrita, cria se nao existir (não se usa a escrita)
    if (f == NULL) return 0;
    ALUNO *a = malloc(sizeof(ALUNO));
    if (a == NULL) return 0;
    char line_aluno[MAX_LINE];
    while (fgets(line_aluno, sizeof(line_aluno), f) != NULL) {
        sscanf(line_aluno, "%[^:]: %d/%d/%d | %d | %s | %d | %lf | %d:", a->nome, &a->data_nascimento.dia,
                &a->data_nascimento.mes, &a->data_nascimento.ano, &a->turma.ano, a->turma.sigla, &a->numero, &a->saldo,
                &a->num_despesas);
        LISTA_DESPESAS *d = malloc(sizeof(LISTA_DESPESAS));
        d->inicio = NULL;
        for (int i = 0; i < a->num_despesas; ++i) {
            fgets(line_aluno, sizeof(line_aluno), f);
            NO_DESPESAS *no = malloc(sizeof(NO_DESPESAS));
            DESPESAS *despesa = malloc(sizeof(DESPESAS));
            if (no == NULL || despesa == NULL) return 0;
            sscanf(line_aluno, "%[^:]: %lf | %d/%d/%d", despesa->descricao, &despesa->valor, &despesa->data.dia,
                    &despesa->data.mes, &despesa->data.ano);
            no->despesa = *despesa;
            no->proximo = NULL;
            NO_DESPESAS *aux = d->inicio; // Ponteiro auxiliar para navegar a lista
            if (aux == NULL) { // Caso a lista esteja vazia (primeira ocorrência)
                d->inicio = no;
            } else {
                while (aux->proximo != NULL) aux = aux->proximo; // Percorrer a lista até o ultimo elemento
                aux->proximo = no; // Novo elemento é o ultimo (porque as despesas estao em ordem decrescente de data)
            }
        }
        a->despesas = d;
        inserir_aluno(l, a, 0);
    }
    fclose(f);
    return 1;
}

int inicializa_despesa(ALUNO *a) {
    a->despesas = malloc(sizeof(LISTA_DESPESAS));
    if (a->despesas == NULL) return 0;
    a->despesas->inicio = NULL;
    return 1;
}

int criar_despesa(lista *l, DATA data, int numero, double montante, const char descricao[]){
    ALUNO *aluno = procurar_aluno(l, numero);
    if (aluno == NULL) return 0;
    NO_DESPESAS *nova_despesa = malloc(sizeof(NO_DESPESAS));
    DESPESAS *despesa = malloc(sizeof (DESPESAS));
    if (nova_despesa == NULL || despesa == NULL) return 0; //Verifica se consegue alocar espaco para a despesa
    if (aluno->saldo < montante) return -1; //Retorna caso o aluno nao tenha saldo suficiente
    // Atualiza o saldo do aluno
    aluno->saldo -= montante; //Subtrair a despesa do saldo do aluno
    despesa->valor = montante;
    despesa->data = data;
    // Parte de inserir a despesa
    strcpy(despesa->descricao, descricao);
    nova_despesa->despesa = *despesa; // Passa a estrutura da despesa para o nó por parâmetro
    NO_DESPESAS *aux = aluno->despesas->inicio; // Ponteiro auxiliar para poder percorrer a lista de despesas
    if (aux == NULL || compara_data(&data, &aux->despesa.data)) { // Caso a lista esteja nula ou a primeiro despesa é mais antiga que a nova despesa
        nova_despesa->proximo = aluno->despesas->inicio;
        aluno->despesas->inicio = nova_despesa;
    } else {
        NO_DESPESAS *anterior = aux; // Ponteiro para guardar o antigo valor do aux
        while (aux != NULL){
            if (compara_data(&data, &aux->despesa.data)) { // Caso a data da despesa seja mais recente que a data da despesa auxiliar
                nova_despesa->proximo = aux;
                anterior->proximo = nova_despesa;
                break;
            } else if (aux->proximo == NULL) { // Caso a data da despeja seja mais antiga que todas as despesas existentes na lista
                nova_despesa->proximo = NULL;
                anterior->proximo = nova_despesa;
                break;
            }
            anterior = aux; // Ponteiro anterior guarda o auxiliar
            aux = aux->proximo; // Auxiliar passa para o próximo
        }
    }
    ++aluno->num_despesas; // Adicionar 1 ao numero de despesas
    return 1;
}

int reescreve_ficheiro(lista *l) {
    FILE *f = fopen(ALUNOS_FILE, "w");
    if (f == NULL) return 0;
    no_lista *aux = l->inicio;
    for (; aux != NULL; aux = aux->prox) {
        aux->aluno.nome[strlen(aux->aluno.nome)] = '\0'; // Quick fix no ficheiro -> de vez em quando ele lê um espaço a mais
        fprintf(f, "%s: %d/%d/%d | %d | %s | %d | %.2f | %d\n", aux->aluno.nome, aux->aluno.data_nascimento.dia,
                aux->aluno.data_nascimento.mes, aux->aluno.data_nascimento.ano, aux->aluno.turma.ano,
                aux->aluno.turma.sigla, aux->aluno.numero, aux->aluno.saldo, aux->aluno.num_despesas);
        NO_DESPESAS *aux_d = aux->aluno.despesas->inicio;
        for (; aux_d != NULL; aux_d = aux_d->proximo) {
            fprintf(f, "%s: %.2f | %d/%d/%d\n", aux_d->despesa.descricao, aux_d->despesa.valor, aux_d->despesa.data.dia, aux_d->despesa.data.mes, aux_d->despesa.data.ano);
        }
    }
    fclose(f);
    return 1;
}

int inserir_aluno_ficheiro(ALUNO *aluno) {
    FILE *f = fopen(ALUNOS_FILE, "a");
    if (f == NULL) return 0;
    fprintf(f, "%s: %d/%d/%d | %d | %s | %d | %.2lf | %d\n", aluno->nome, aluno->data_nascimento.dia, aluno->data_nascimento.mes, aluno->data_nascimento.ano, aluno->turma.ano, aluno->turma.sigla, aluno->numero, aluno->saldo, aluno->num_despesas);
    fclose(f);
    return 1;
}

int ordena_alfabeticamente(lista *l) {
    no_lista *atual = l->inicio;
    if (atual == NULL) return 0;
    for (; atual != NULL; atual = atual->prox) {
        no_lista *prox = atual->prox;
        for (; prox != NULL; prox = prox->prox) {
            if (strcmp(atual->aluno.nome, prox->aluno.nome) > 0) {
                ALUNO temp = atual->aluno;   // Guardar o aluno atual numa variavel temporaria
                atual->aluno = prox->aluno;  // Substituir o aluno atual pelo proximo
                prox->aluno = temp;          // Substituir o proximo pelo aluno atual (que estava guardado na variavel temporaria)
            }
        }
    }
    reescreve_ficheiro(l);
    return 1;
}

int ordena_saldo(lista *l) {
    no_lista *atual = l->inicio;
    for (; atual != NULL; atual = atual->prox) {
        no_lista *prox = atual->prox;
        for (; prox != NULL; prox = prox->prox) {
            if (atual->aluno.saldo < prox->aluno.saldo) {
                ALUNO temp = atual->aluno;   // Guardar o aluno atual numa variavel temporaria
                atual->aluno = prox->aluno;  // Substituir o aluno atual pelo proximo
                prox->aluno = temp;          // Substituir o proximo pelo aluno atual (que estava guardado na variavel temporaria)
            }
        }
    }
    return 1;
}

int menu(lista *l) {
    int input, numero;
    double saldo, despesa;
    char descricao[100];
    DATA data;
    opcoes(); // mostra as opcões
    printf("Digite o numero correspondente a operacao que quer realizar: ");
    int err = scanf("%d", &input);
    if (err == 0) { // faz com que dê handle quando se mete uma letra como input
        input = -1;
        while (getchar() != '\n'); // Apanha o ultimo '\n' para que nao interfira o input
    } else if (err == EOF) { // faz com que dê handle ao infinite loop do input (caso de dar ctrl + D)
        clean();
        printf("Programa forcado a terminar\n");
        return 0;
    }

    clean();

    switch (input) {
        case 0: { // ! Sair do programa
            printf("Fim do programa\n");
            return 0;
        } case 1: { // ! Inserir aluno
            printf("Intruduzindo um aluno...\n");
            ALUNO * aluno = pede_aluno();
            if (aluno == NULL) {
                printf("Aluno invalido\n");
                separador();
                break;
            }
            clean();
            if (inserir_aluno(l, aluno, 1)) printf("Aluno inserido com sucesso!\n");
            separador();
            break;
        } case 2: { // ! Remover aluno
            printf("Digite o numero do aluno que quer eliminar: ");
            numero = pede_numero();
            while (getchar() != '\n');
            if (!confirmar()) break;
            clean();
            if (eliminar_aluno(l, numero)) printf("O aluno foi eliminado com sucesso\n");
            else printf("Nao foi encontrado nenhum aluno com este numero\n");
            separador();
            reescreve_ficheiro(l);
            break;
        } case 3: { // ! Ordenar alunos e imprimir apenas os nomes
            ordena_alfabeticamente(l);
            if (!imprime_nomes(l)) printf("Nao existem alunos na lista\n");
            separador();
            break;
        } case 4: { // ! Imprimir alunos com saldo inferior a um determinado valor
            printf("Listando alunos pelo seu saldo...\n");
            printf("Digite o saldo maximo: ");
            saldo = pede_montante();
            if (!verifica_saldo(saldo)) {
                clean();
                printf("Montante invalido\n");
                separador();
                break;
            }
            clean();
            listar_alunos_saldo(l, saldo);
            separador();
            break;
        } case 5: { // ! Listar a informacao sobre o aluno
            printf("Listando informacao de um aluno...\n");
            printf("Digite o numero do aluno: ");
            numero = pede_numero();
            if (!verifica_numero(numero) || procurar_aluno(l, numero) == NULL) {
                clean();
                printf("Nao foi encontrado nenhum aluno com este numero\n");
                separador();
                break;
            }
            clean();
            imprime_aluno(procurar_aluno(l, numero));
            separador();
            break;
        } case 6: { // ! Efectuar um pagamento (criar despesa)
            printf("Efetuando uma despesa de um aluno...\n");
            printf("Digite o numero do aluno: ");
            numero = pede_numero();
            if (procurar_aluno(l, numero) == NULL) {
                clean();
                printf("Nao foi encontrado nenhum aluno com este numero\n");
                separador();
                break;
            }

            printf("Digite o valor da despesa: ");
            despesa = pede_montante();
            if (!verifica_saldo(despesa)) {
                clean();
                printf("Montante invalido\n");
                separador();
                break;
            }

            printf("Digite a descricao da despesa: ");
            fgets(descricao, 100, stdin);
            if (strlen(descricao) == 0) {
                clean();
                printf("Descricao invalida\n");
                separador();
                break;
            }
            descricao[strlen(descricao) - 1] = '\0'; // Troca o '\n' do fim da string
            printf("Digite a data de faturacao da despesa (DD/MM/AAAA): ");
            scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
            while (getchar() != '\n');
            if (!verifica_data(&data)) {
                clean();
                printf("Data invalida!\n");
                break;
            }

            if (!confirmar()) break;
            clean();
            int var = criar_despesa(l, data, numero, despesa, descricao);
            if (var == 0) printf("Nao foi possivel criar a despesa\n");
            else if (var == -1) printf("O aluno nao possui saldo suficiente\n");
            else {
                printf("Despesa efetuada com sucesso\n");
                reescreve_ficheiro(l);
            }
            separador();
            break;
        } case 7: { // ! Listar as despesas de um aluno
            printf("Listando as despesas de um aluno..\n");
            printf("Digite o numero do aluno: ");
            numero = pede_numero();
            if (!verifica_numero(numero)) {
                clean();
                printf("Numero invalido\n");
                separador();
                break;
            }
            clean();
            int var = mostrar_despesas(l, numero);
            if (var == -1) {
                printf("Nao existem despesas para este aluno\n");
            } else if (var == 0) {
                printf("O aluno nao possui despesas\n");
            }
            separador();
            break;
        } case 8: { // ! Carregar conta de um aluno
            printf("Carregando conta de um aluno...\n");
            printf("Digite o numero do aluno: ");
            numero = pede_numero();

            printf("Digite o valor para carregar: ");
            saldo = pede_montante();
            if (!verifica_saldo(saldo)) {
                clean();
                printf("Montante nao valido\n");
                separador();
                break;
            }

            if (!confirmar()) break;
            clean();

            if (carregar_conta(l, numero, saldo)) {
                printf("Conta carregada com sucesso\n");
                reescreve_ficheiro(l);
            } else printf("Nao foi possivel carregar a conta\n");
            separador();
            break;
        } default: { // ! Quando invalido
            printf("Opcao invalida!\n");
            separador();
            break;
        }
    }
    return 1;
}
