#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Desafio War: Implementando ataque entre territórios
// Aluno: Francisco Araújo de Paiva Junior
// Tema 1 - Estruturas de Dados: Conceitos e Representação
// Nível: Aventureiro

//Estrutura Territorio:

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPOS) ---
void cadastrarTerritorios(Territorio* mapa, int qtd);
void exibirMapa(Territorio* mapa, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    // Definindo a quantidade fixa de territórios como 5
    int num_territorios = 5;
    int id_atacante, id_defensor;

    // Inicializa a semente de números aleatórios com o tempo atual
    srand(time(NULL));

    printf("=======================================\n\n");
    printf("Vamos cadastrar os %d territorios iniciais do nosso mundo.\n\n", num_territorios);

    
     // Alocação Dinâmica:
     // Usa calloc para alocar o vetor de territórios na memória dinamicamente.
     
    Territorio* mundo = (Territorio*) calloc(num_territorios, sizeof(Territorio));
    
    if (mundo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Chama a função modularizada para cadastrar
    cadastrarTerritorios(mundo, num_territorios);

    printf("Cadastro inicial concluido com sucesso!\n\n");
    
    // Chama a função para exibir o mapa inicial
    exibirMapa(mundo, num_territorios);

    
     // Loop da Fase de Ataque:
     
    while (1) {
        printf("--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", num_territorios);
        scanf("%d", &id_atacante);

        if (id_atacante == 0) {
            break; // Sai do loop de ataque
        }

        printf("Escolha o territorio defensor (1 a %d): ", num_territorios);
        scanf("%d", &id_defensor);

        // Validações básicas de entrada
        if (id_atacante < 1 || id_atacante > num_territorios || id_defensor < 1 || id_defensor > num_territorios) {
            printf("\nErro: Territorio invalido. Tente novamente.\n\n");
            continue;
        }

        if (id_atacante == id_defensor) {
            printf("\nErro: Um territorio nao pode atacar a si mesmo!\n\n");
            continue;
        }

        // Utilizando ponteiros para acessar os territórios escolhidos
        Territorio* ptr_atacante = &mundo[id_atacante - 1];
        Territorio* ptr_defensor = &mundo[id_defensor - 1];

        // Validações das regras de negócio do jogo
        if (strcmp(ptr_atacante->cor, ptr_defensor->cor) == 0) {
            printf("\nRegra: Nao e possivel atacar um territorio aliado (mesma cor)!\n\n");
            continue;
        }

        if (ptr_atacante->tropas <= 1) {
            printf("\nRegra: O territorio '%s' precisa de mais de 1 tropa para atacar.\n\n", ptr_atacante->nome);
            continue;
        }

        // Executa a simulação de batalha
        atacar(ptr_atacante, ptr_defensor);

        // Após apertar Enter na função atacar, exibe o estado atualizado do mundo
        exibirMapa(mundo, num_territorios);
    }

    printf("\nFim de jogo. Tropas Salvas...\n");
    
    // Libera a memória alocada antes de encerrar o programa
    liberarMemoria(mundo);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Função para cadastrar os territórios.

void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        
        printf("Nome do Territorio: ");
        scanf(" %[^\n]", mapa[i].nome); 
        
        printf("Cor do Exercito: ");
        scanf(" %s", mapa[i].cor);
        
        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("\n");
    }
}


// Função para exibir o mapa.

void exibirMapa(Territorio* mapa, int qtd) {
    printf("=======================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL     \n");
    printf("=======================================\n\n");

    for (int i = 0; i < qtd; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n"); // Espaçamento antes da próxima FASE DE ATAQUE
}


// Função que simula a batalha utilizando ponteiros.
 
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- RESULTADO DA BATALHA ---\n");
    
    // Sorteia números de 1 a 6 simulando a rolagem de dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    // Layout baseado na imagem
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    // Lógica de combate
    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas -= 1;
        
        // Se o defensor ficar com 0 tropas, o atacante conquista
        if (defensor->tropas == 0) {
            int tropasMovidas = atacante->tropas / 2;
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = tropasMovidas;
            atacante->tropas -= tropasMovidas;
            printf("=> O exercito %s conquistou o territorio de %s!\n", atacante->cor, defensor->nome);
        }
    } else {
        // Empate ou vitória da defesa
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
    
    // Pausa para o próximo turno
    printf("\nPressione Enter para continuar para o proximo turno...");
    
    // Limpeza de buffer para garantir que o 'Enter' pause a tela corretamente
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o \n pendente do scanf
    getchar(); // Espera o Enter do usuário
}


// Função para limpar o espaço alocado dinamicamente.

void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}