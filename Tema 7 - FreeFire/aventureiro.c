#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Desafio Free Fire: Desenvolvimento de duas versoes do sistema
// Aluno: Francisco Araújo de Paiva Junior
// Tema 2 - Lista e Ordenação (2º Semestre 2026)
// Nível: Aventureiro

// Agrupa as propriedades de um objeto coletavel em um unico tipo de dado estruturado
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Prototipos: Informam ao compilador a existencia e a assinatura das funcoes antes da main
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);
void pressioneEnter();
void limparBuffer();

int main() {
    Item mochila[MAX_ITENS]; 
    int totalItens = 0; 
    int opcao;

    do {
        // Exibe a interface principal em laco para garantir que o usuario faca multiplas acoes sem o programa fechar
        printf("\n===================================\n");
        printf("MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("===================================\n");
        printf("Itens na Mochila: %d/%d\n", totalItens, MAX_ITENS);
        printf("\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("-----------------------------------\n");
        printf("Escolha uma opcao: ");
        
        // Seguranca: Verifica se o scanf conseguiu ler um numero inteiro. Se ler uma letra, evita loop infinito limpando o lixo de memoria
        if (scanf("%d", &opcao) != 1) { 
            limparBuffer();
            opcao = -1; 
        } else {
            limparBuffer(); 
        }

        // Estrutura de decisao que mapeia a escolha do usuario para a chamada da funcao correspondente
        switch(opcao) {
            case 1: 
                inserirItem(mochila, &totalItens); 
                listarItens(mochila, totalItens);
                pressioneEnter();
                break;
            case 2: 
                removerItem(mochila, &totalItens);
                pressioneEnter();
                break;
            case 3: 
                listarItens(mochila, totalItens); 
                pressioneEnter();
                break;
            case 4:
                buscarItem(mochila, totalItens);
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

// Verifica a capacidade do vetor estatico e, se houver espaco, registra os dados no indice atual apontado pelo ponteiro '*total'
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n[AVISO] A mochila esta cheia! Limite de %d itens atingido.\n", MAX_ITENS);
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n"); 
    
    // Le a string com espacos e substitui a quebra de linha (\n) gerada pelo ENTER por um terminador nulo (\0)
    printf("Nome do item: ");
    fgets(mochila[*total].nome, 30, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0'; 

    printf("Tipo do item: ");
    fgets(mochila[*total].tipo, 20, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    if (scanf("%d", &mochila[*total].quantidade) != 1) { 
        mochila[*total].quantidade = 0;
    }
    limparBuffer();

    printf("\nItem '%s' adicionado com sucesso!\n", mochila[*total].nome);
    (*total)++; 
}

// Executa uma remocao fisica em vetor: localiza o indice do item e desloca todos os elementos subsequentes uma posicao para a esquerda
void removerItem(Item mochila[], int *total) {
    printf("\n--- Remover Item ---\n"); 

    if (*total == 0) {
        printf("[AVISO] A mochila ja esta vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: "); 
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        // Compara o nome alvo com os nomes armazenados (case-sensitive)
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Laco aninhado responsavel pelo rearanjo (sobrescrevendo o item removido)
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--; 
            
            printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
            return; 
        }
    }

    printf("\nResultado: Item '%s' NAO foi encontrado na mochila.\n", nomeBusca);
}

// Percorre o vetor usando limitadores de espacamento no printf (ex: %-16s) para formatar a saida como uma tabela alinhada
void listarItens(Item mochila[], int total) {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", total, MAX_ITENS);
    printf("---------------------------------------------\n");
    printf("%-16s | %-13s | %s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------\n");

    if (total > 0) {
        for (int i = 0; i < total; i++) {
            printf("%-16s | %-13s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("---------------------------------------------\n\n");
}

// Implementa o algoritmo de Busca Sequencial (Linear), iterando sobre os indices ate encontrar uma correspondencia exata na string
void buscarItem(Item mochila[], int total) {
    printf("\n--- Buscar Item na Mochila ---\n");
    
    if (total == 0) {
        printf("[AVISO] A mochila esta vazia.\n\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        // Interrompe o laco no momento em que o item e validado e exibe seus metadados de forma individual
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("-----------------------------------\n\n");
            return;
        }
    }

    // Fluxo alternativo: so e executado se o laco for finalizado sem o 'return', caracterizando que o item inexiste
    printf("\nResultado: Item '%s' NAO foi encontrado na mochila.\n\n", nomeBusca);
}

// Interrompe o processamento (pausa o console) ate que o caractere de nova linha '\n' seja capturado do teclado
void pressioneEnter() {
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); 
}

// Consome caracteres residuais no fluxo de entrada padrao (stdin) para evitar saltos ou bugs de leitura em operacoes sequenciais
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}