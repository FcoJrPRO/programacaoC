#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPONENTES 10

// Desafio Free Fire:  Implementação de diferentes algoritmos de ordenacao
// Aluno: Francisco Araújo de Paiva Junior
// Tema 2 - Lista e Ordenação (2º Semestre 2026)
// Nível: Mestre

// A struct Componente agrupa todos os atributos necessarios para construir a torre de fuga, atuando como o tipo de dado principal do sistema.
typedef struct {
    char nome[30];
    char tipo[30];
    int quantidade;
    int prioridade;
} Componente;

// Variavel global para armazenar a contagem de comparacoes dos algoritmos
int comparacoesGlobais = 0;

// Prototipos das funcoes
void adicionarComponente(Componente mochila[], int *total, int *ordenado);
void descartarComponente(Componente mochila[], int *total, int *ordenado);
void listarComponentes(Componente mochila[], int total);
void organizarMochila(Componente mochila[], int total, int *ordenado);
void buscaBinaria(Componente mochila[], int total);

// Funcoes de ordenacao
void bubbleSortNome(Componente vetor[], int tamanho);
void insertionSortTipo(Componente vetor[], int tamanho);
void selectionSortPrioridade(Componente vetor[], int tamanho);

void limparBuffer();
void pressioneEnter();

int main() {
    Componente mochila[MAX_COMPONENTES];
    int totalItens = 0;
    int opcao;
    
    // Flag de controle de estado: rastreia se a mochila atual foi devidamente ordenada pelo algoritmo de Bubble Sort, liberando a busca binaria.
    int ordenadoPorNome = 0; 

    do {
        // Renderiza o menu interativo principal, exibindo em tempo real a capacidade da mochila e o status atual da ordenacao dos itens.
        printf("\n========================================================\n");
        printf("   PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("========================================================\n");
        printf("Itens na Mochila: %d/%d\n", totalItens, MAX_COMPONENTES);
        
        if (ordenadoPorNome) {
            printf("Status da Ordenacao por Nome: ORDENADO\n\n");
        } else {
            printf("Status da Ordenacao por Nome: NAO ORDENADO\n\n");
        }

        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("--------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) { 
            limparBuffer();
            opcao = -1; 
        } else {
            limparBuffer(); 
        }

        // Estrutura de roteamento que mapeia a escolha do usuario para a rotina do sistema correspondente.
        switch(opcao) {
            case 1: 
                adicionarComponente(mochila, &totalItens, &ordenadoPorNome);
                pressioneEnter();
                break;
            case 2: 
                descartarComponente(mochila, &totalItens, &ordenadoPorNome);
                pressioneEnter();
                break;
            case 3: 
                listarComponentes(mochila, totalItens);
                pressioneEnter();
                break;
            case 4:
                organizarMochila(mochila, totalItens, &ordenadoPorNome);
                pressioneEnter();
                break;
            case 5:
                // Bloqueio de seguranca: garante a pre-condicao fundamental da busca binaria, exigindo que o array esteja previamente ordenado.
                if (ordenadoPorNome == 0) {
                    printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
                    printf("Use a Opcao 4 para organizar a mochila primeiro.\n\n");
                } else {
                    buscaBinaria(mochila, totalItens);
                }
                pressioneEnter();
                break;
            case 0: 
                printf("\nIniciando sequencia de ativacao da Torre de Fuga... Boa sorte!\n"); 
                break;
            default: 
                if (opcao != -1) {
                    printf("\n[ERRO] Opcao invalida.\n\n");
                    pressioneEnter();
                }
                break;
        }
    } while(opcao != 0);

    return 0;
}

// Captura os dados via teclado, insere no final do vetor e redefine a flag de ordenacao, ja que um novo item bagunca a ordem atual.
void adicionarComponente(Componente mochila[], int *total, int *ordenado) {
    if (*total >= MAX_COMPONENTES) {
        printf("\n[AVISO] A mochila esta cheia!\n");
        return;
    }

    printf("\n--- Coletando Novo Componente ---\n"); 
    
    printf("Nome: ");
    fgets(mochila[*total].nome, 30, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0'; 

    printf("Tipo (Estrutural, Eletronico, Energia): ");
    fgets(mochila[*total].tipo, 30, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    limparBuffer();

    printf("Prioridade de Montagem (1-5): ");
    scanf("%d", &mochila[*total].prioridade);
    limparBuffer();

    printf("\nComponente '%s' adicionado!\n", mochila[*total].nome);
    (*total)++; 
    *ordenado = 0; // Inserir novo item bagunça a ordenacao
    
    listarComponentes(mochila, *total);
}

// Realiza uma exclusao logica e fisica: encontra o item alvo e sobrescreve-o arrastando os elementos seguintes uma posicao para tras.
void descartarComponente(Componente mochila[], int *total, int *ordenado) {
    if (*total == 0) {
        printf("\n[AVISO] O inventario ja esta vazio.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Descartar Componente ---\n"); 
    printf("Nome do componente a ser descartado: "); 
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--; 
            // Nao mudamos a flag de ordenacao, pois remover um item nao desordena os restantes
            printf("\nComponente '%s' descartado com sucesso!\n", nomeBusca);
            return; 
        }
    }
    printf("\nComponente nao encontrado no inventario.\n");
}

// Varre o vetor de componentes utilizando espacamento pre-definido (ex: %-18s) para renderizar uma tabela alinhada e facil de ler no console.
void listarComponentes(Componente mochila[], int total) {
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", total, MAX_COMPONENTES);
    printf("------------------------------------------------------------------\n");
    printf("%-18s | %-15s | %-10s | %s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-18s | %-15s | %-10d | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("------------------------------------------------------------------\n\n");
}

// Submenu responsavel por acionar os diferentes algoritmos de ordenacao, reiniciando o contador de comparacoes para analise de complexidade.
void organizarMochila(Componente mochila[], int total, int *ordenado) {
    if (total == 0) {
        printf("\nInventario vazio. Nao ha o que ordenar.\n\n");
        return;
    }

    int opcaoSort;
    printf("\n--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabética)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");
    
    if (scanf("%d", &opcaoSort) != 1) { 
        limparBuffer();
        opcaoSort = -1; 
    } else {
        limparBuffer(); 
    }

    comparacoesGlobais = 0; // Zera para medir a nova operacao

    switch(opcaoSort) {
        case 1:
            bubbleSortNome(mochila, total);
            *ordenado = 1; // Libera o uso da busca binaria
            printf("\nMochila organizada por NOME.\n");
            printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n", comparacoesGlobais);
            listarComponentes(mochila, total);
            break;
        case 2:
            insertionSortTipo(mochila, total);
            *ordenado = 0; 
            printf("\nMochila organizada por TIPO.\n");
            printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n", comparacoesGlobais);
            listarComponentes(mochila, total);
            break;
        case 3:
            selectionSortPrioridade(mochila, total);
            *ordenado = 0;
            printf("\nMochila organizada por PRIORIDADE.\n");
            printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n", comparacoesGlobais);
            listarComponentes(mochila, total);
            break;
        case 0:
            printf("\nOrganizacao cancelada.\n");
            break;
        default:
            printf("\n[ERRO] Criterio invalido.\n");
            break;
    }
}

// Algoritmo de busca logaritmica (O(log n)): divide o espaco de busca pela metade a cada iteracao ate encontrar o alvo ou esgotar as possibilidades.
void buscaBinaria(Componente mochila[], int total) {
    char nomeBusca[30];
    
    printf("\n--- Busca Binaria por Componente-Chave ---\n");
    printf("Nome do componente a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int inicio = 0;
    int fim = total - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {
            printf("\n--- Componente-Chave Encontrado! ---\n");
            printf("Nome: %s, Tipo: %s, Qtd: %d, Prio: %d\n\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        }
        if (cmp < 0) {
            inicio = meio + 1; 
        } else {
            fim = meio - 1;    
        }
    }
    printf("\nComponente '%s' nao foi encontrado!\n\n", nomeBusca);
}

// Implementando os algoritmos base, esta funcao realiza o Bubble Sort contando o laco interno
void bubbleSortNome(Componente vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            comparacoesGlobais++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Componente temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

// Implementando os algoritmos base, esta funcao realiza o Insertion Sort deslocando blocos na memoria
void insertionSortTipo(Componente vetor[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        Componente chave = vetor[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoesGlobais++;
            if (strcmp(vetor[j].tipo, chave.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j = j - 1;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
}

// Implementando os algoritmos base, esta funcao realiza o Selection Sort buscando inteiros
void selectionSortPrioridade(Componente vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int indice_menor = i;
        for (int j = i + 1; j < tamanho; j++) {
            comparacoesGlobais++;
            if (vetor[j].prioridade < vetor[indice_menor].prioridade) {
                indice_menor = j;
            }
        }
        if (indice_menor != i) {
            Componente temp = vetor[i];
            vetor[i] = vetor[indice_menor];
            vetor[indice_menor] = temp;
        }
    }
}

// Interrompe temporariamente a execucao, aguardando uma acao do usuario para prosseguir, garantindo tempo de leitura das mensagens de retorno.
void pressioneEnter() {
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); 
}

// Auxiliar padrao para limpar sobras de 'scanf' e nao pular telas
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}