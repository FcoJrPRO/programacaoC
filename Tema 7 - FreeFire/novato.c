#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define LARGURA_NOME 16
#define LARGURA_TIPO 13

// Desafio Free Fire: Sistema de Inventário e Gerenciamento de Itens
// Aluno: Francisco Araújo de Paiva Junior
// Tema 2 - Lista e Ordenação (2º Semestre 2026)
// Nível: Novato

/* * Definição da struct: Item
 * Armazena as informações essenciais de cada objeto coletado.
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *total);
bool removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void pressioneEnter();
void limparBuffer();
void buscarItem(Item mochila[], int total);

int main() {
    Item mochila[MAX_ITENS]; 
    int totalItens = 0; 
    int opcao;

    do {
        // Menu
        printf("\n===================================\n");
        printf("MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("===================================\n");
        printf("Itens na Mochila: %d/%d\n", totalItens, MAX_ITENS);
        printf("\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("0. Sair\n");
        printf("\n");
        printf("Escolha uma opcao: ");
        
        // Validacao
        if (scanf("%d", &opcao) != 1) { 
            limparBuffer();
            opcao = -1; 
        } else {
            limparBuffer(); 
        }

        // Navegacao
        switch(opcao) {
            case 1: 
                inserirItem(mochila, &totalItens); 
                listarItens(mochila, totalItens);
                pressioneEnter();
                break;
            case 2: 
                if (removerItem(mochila, &totalItens)) {
                    listarItens(mochila, totalItens);
                }
                pressioneEnter();
                break;
            case 3: 
                listarItens(mochila, totalItens); 
                pressioneEnter();
                break;
            case 0: 
                printf("\nSaindo do jogo. Ate a proxima aventura!\n"); 
                break;
            default: 
                if (opcao != -1) {
                    printf("\n[ERRO] Opcao invalida. Tente novamente.\n");
                    pressioneEnter();
                }
                break;
        }
    } while(opcao != 0);

    return 0;
}

/* * Função para inserir um novo item.
 * Verifica se há espaço e lê os dados.
 */
void inserirItem(Item mochila[], int *total) {
    // Capacidade
    if (*total >= MAX_ITENS) {
        printf("\n--- Adicionar Novo Item ---\n");
        printf("[AVISO] A mochila esta cheia! Limite de %d itens atingido.\n", MAX_ITENS);
        return;
    }

    // Cabecalho
    printf("\n--- Adicionar Novo Item ---\n"); 
    
    // Leitura
    printf("Nome do item: ");
    fgets(mochila[*total].nome, 30, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0'; 

    printf("Tipo do item (arma, municao, cura, etc.): ");
    fgets(mochila[*total].tipo, 20, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    if (scanf("%d", &mochila[*total].quantidade) != 1) { 
        limparBuffer();
        mochila[*total].quantidade = 0;
    } else {
        limparBuffer();
    }

    // Confirmacao
    printf("\nItem '%s' adicionado com sucesso!\n", mochila[*total].nome);
    (*total)++; 
}

/* * Função para remover um item por nome.
 * Reorganiza o vetor. Retorna true se removeu, false se não encontrou.
 */
bool removerItem(Item mochila[], int *total) {
    // Cabecalho
    printf("\n--- Remover Item ---\n"); 

    // Verificacao
    if (*total == 0) {
        printf("[AVISO] A mochila ja esta vazia.\n");
        return false;
    }

    // Entrada
    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: "); 
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    
    // Busca
    for (int i = 0; i < *total; i++) {
        if (strcasecmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            char nomeRemovido[30];
            strcpy(nomeRemovido, mochila[i].nome); 
            
            // Reordenacao
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--; 
            
            // Confirmacao
            printf("\nItem '%s' removido com sucesso!\n", nomeRemovido);
            return true; 
        }
    }

    // Falha
    if (!encontrado) {
        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
    return false; 
}

/* * Função para listar itens com formatação de tabela alinhada.
 */
void listarItens(Item mochila[], int total) {
    // Cabecalho
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", total, MAX_ITENS);
    
    // Formatacao
    printf("---------------------------------------------\n");
    printf("%-16s | %-13s | %s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------\n");

    // Exibicao
    if (total == 0) {
        printf("[VAZIO] A mochila esta vazia.\n");
    } else {
        for (int i = 0; i < total; i++) {
            printf("%-16s | %-13s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("---------------------------------------------\n");
}

/* * Função auxiliar para fazer uma pausa e esperar o enter.
 */
void pressioneEnter() {
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); 
}

/* * Função auxiliar para limpar o buffer do teclado.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* * Função de busca (mantida para manutenibilidade).
 */
void buscarItem(Item mochila[], int total) {
    // Implementacao futura
}