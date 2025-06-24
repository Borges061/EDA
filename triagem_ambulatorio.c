/*
Trabalho de Estrutura de Dados - Fila com Prioridade
Tema: Sistema de triagem em ambulatório com cores de pulseira
Alunos:
    Luis Guilherme Borges - 211045178
    Vinicius Fernandes Rufino - 200062891

Descrição do Sistema:
Este trabalho implementa um sistema de triagem de pacientes em um ambulatório, utilizando uma
estrutura de dados do tipo fila com prioridade.
Cada paciente é classificado com uma cor de pulseira que representa o nível de urgência:
- Vermelha (emergência)
- Amarela (urgência moderada)
- Verde (caso leve)
Pacientes com pulseiras vermelhas têm prioridade no atendimento, seguidos pelos amarelos e, por
último, os verdes.
O sistema permite:
- Inserção de pacientes com prioridade
- Atendimento conforme prioridade
- Visualização das filas

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100
#define TAM_MAX_PACIENTES 100

typedef struct {
    char nome[TAM_NOME];
} Pessoa;

typedef struct {
    Pessoa lista[TAM_MAX_PACIENTES];
    int inicio;
    int fim;
} FilaDeEspera;

void iniciarFila(FilaDeEspera* fila) {
    fila->inicio = 0;
    fila->fim = 0;
}

int estaVazia(FilaDeEspera* fila) {
    return fila->inicio == fila->fim;
}

int estaCheia(FilaDeEspera* fila) {
    return fila->fim == TAM_MAX_PACIENTES;
}

void adicionarPaciente(FilaDeEspera* fila, char nomePaciente[]) {
    if (estaCheia(fila)) {
        printf("Fila cheia! Não é possível adicionar mais pacientes.\n");
        return;
    }
    int i = 0;
    while (nomePaciente[i] != '\0' && i < TAM_NOME - 1) {
        fila->lista[fila->fim].nome[i] = nomePaciente[i];
        i++;
    }
    fila->lista[fila->fim].nome[i] = '\0';
    fila->fim++;
}

char* chamarPaciente(FilaDeEspera* fila) {
    if (estaVazia(fila)) return NULL;
    char* nome = fila->lista[fila->inicio].nome;
    fila->inicio++;
    return nome;
}

void mostrarFila(FilaDeEspera* fila) {
    for (int i = fila->inicio; i < fila->fim; i++) {
        printf("• %s\n", fila->lista[i].nome);
    }
}

int main() {
    FilaDeEspera filaVermelha, filaAmarela, filaVerde;
    iniciarFila(&filaVermelha);
    iniciarFila(&filaAmarela);
    iniciarFila(&filaVerde);

    int escolha;
    char nomePaciente[TAM_NOME];
    int prioridade;

    do {
        printf("\n=========== TRIAGEM AMBULATÓRIO ===========\n");
        printf("1 - Cadastrar novo paciente\n");
        printf("2 - Chamar próximo paciente\n");
        printf("3 - Ver filas\n");
        printf("0 - Encerrar sistema\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        getchar(); // limpa o '\n'

        switch (escolha) {
            case 1:
                printf("Digite o nome do paciente: ");
                fgets(nomePaciente, TAM_NOME, stdin);
                nomePaciente[strcspn(nomePaciente, "\n")] = 0; // remove o enter

                printf("Informe a prioridade da pulseira (1 = Vermelha, 2 = Amarela, 3 = Verde): ");
                scanf("%d", &prioridade);
                getchar();

                switch (prioridade) {
                    case 1:
                        adicionarPaciente(&filaVermelha, nomePaciente);
                        break;
                    case 2:
                        adicionarPaciente(&filaAmarela, nomePaciente);
                        break;
                    case 3:
                        adicionarPaciente(&filaVerde, nomePaciente);
                        break;
                    default:
                        printf("Prioridade inválida!\n");
                }
                break;

            case 2: {
                char* proximo = NULL;
                if (!estaVazia(&filaVermelha)) {
                    proximo = chamarPaciente(&filaVermelha);
                    printf("🔴 Atendendo emergência: %s\n", proximo);
                } else if (!estaVazia(&filaAmarela)) {
                    proximo = chamarPaciente(&filaAmarela);
                    printf("🟠 Atendendo urgência: %s\n", proximo);
                } else if (!estaVazia(&filaVerde)) {
                    proximo = chamarPaciente(&filaVerde);
                    printf("🟢 Atendendo caso leve: %s\n", proximo);
                } else {
                    printf("Nenhum paciente aguardando no momento.\n");
                }
                break;
            }

            case 3:
                printf("\n--- Fila Vermelha (Emergência) ---\n");
                mostrarFila(&filaVermelha);
                printf("--- Fila Amarela (Urgência) ---\n");
                mostrarFila(&filaAmarela);
                printf("--- Fila Verde (Pouco urgente) ---\n");
                mostrarFila(&filaVerde);
                break;

            case 0:
                printf("Encerrando o atendimento. Até logo!\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (escolha != 0);

    return 0;
}
