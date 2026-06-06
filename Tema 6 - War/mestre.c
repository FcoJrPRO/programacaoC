#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Desafio War: implementando a funcionalidade de missões estratégicas
// Aluno: Francisco Araújo de Paiva Junior
// Tema 1 - Estruturas de Dados: Conceitos e Representação
// Nível: Mestre

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
void atribuirMissao(char* destino, char* cor_jogador, Territorio* mapa, int qtd);
int verificarMissao(char* missao, char* cor, Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* mapa, char* missao);

int main() {
    int num_territorios = 5;
    
    // Inicializa a semente de números aleatórios com o tempo atual
    srand(time(NULL));

    printf("=======================================\n\n");
    printf("Vamos cadastrar os %d territorios iniciais do nosso mundo.\n\n", num_territorios);

    // Alocação Dinâmica:
    
    Territorio* mundo = (Territorio*) calloc(num_territorios, sizeof(Territorio));
    if (mundo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mundo, num_territorios);
    printf("Cadastro inicial concluido com sucesso!\n");

    // Define a cor do jogador principal (dono do 1º território cadastrado)
    char cor_jogador[10];
    strcpy(cor_jogador, mundo[0].cor);

    // Aloca memória para a missão do jogador e sorteia o objetivo
    char* missao_jogador = (char*) malloc(100 * sizeof(char));
    atribuirMissao(missao_jogador, cor_jogador, mundo, num_territorios);

    // Loop Principal de Ações:
    
    while (1) {
        exibirMapa(mundo, num_territorios);

        // Exibição da Missão
        printf("--- SUA MISSAO (Exercito %s) ---\n", cor_jogador);
        printf("%s\n\n", missao_jogador);

        // Menu de Ações
        printf("--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        
        int acao;
        scanf("%d", &acao);

        if (acao == 0) {
            break; // Sair do jogo
        } 
        else if (acao == 2) {
            // Ação: Verificar se a missão foi cumprida
            if (verificarMissao(missao_jogador, cor_jogador, mundo, num_territorios)) {
                printf("\n=======================================\n");
                printf(" PARABENS! VOCE CUMPRIU SUA MISSAO!\n");
                printf(" VITORIA DO EXERCITO %s!\n", cor_jogador);
                printf("=======================================\n");
                break; // Fim de jogo
            } else {
                printf("\n>>> Missao ainda nao concluida. Avance com suas tropas! <<<\n");
                printf("\nPressione Enter para continuar...");
                int c; while ((c = getchar()) != '\n' && c != EOF); getchar(); 
            }
        } 
        else if (acao == 1) {
            // Ação: Iniciar um ataque
            int id_atacante, id_defensor;
            
            printf("\nEscolha o territorio atacante (1 a %d): ", num_territorios);
            scanf("%d", &id_atacante);

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
            
            // Verificação automática após o ataque
            if (verificarMissao(missao_jogador, cor_jogador, mundo, num_territorios)) {
                exibirMapa(mundo, num_territorios);
                printf("=======================================\n");
                printf(" PARABENS! VOCE CUMPRIU SUA MISSAO!\n");
                printf(" VITORIA DO EXERCITO %s!\n", cor_jogador);
                printf("=======================================\n");
                break; // Fim de jogo
            }
        } else {
            printf("\nOpcao invalida. Tente novamente.\n\n");
        }
    }

    printf("\nFim de jogo. Tropas Salvas...\n");
    liberarMemoria(mundo, missao_jogador);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

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

// Exibe o mapa perfeitamente alinhado com a imagem de referência.

void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n=============== MAPA DO MUNDO ===============\n");
    for (int i = 0; i < qtd; i++) {
        // Uso de %-15s e %-10s para alinhar as colunas com espaços à direita
        printf("%d. %-15s (Exercito: %-10s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("===============================================\n\n");
}

// Sorteia uma missão viável para o jogador.

void atribuirMissao(char* destino, char* cor_jogador, Territorio* mapa, int qtd) {
    // Busca uma cor inimiga real no mapa para criar a missão de "Destruir"
    char cor_inimiga[10] = "";
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mapa[i].cor, cor_jogador) != 0) {
            strcpy(cor_inimiga, mapa[i].cor);
            if (rand() % 2 == 0) break; // Pequena aleatoriedade ao escolher o inimigo
        }
    }

    int sorteio = rand() % 3;
    
    // Se encontrou um inimigo, pode sortear a missão de destruição
    if (sorteio == 0 && strlen(cor_inimiga) > 0) {
        sprintf(destino, "Destruir o exercito %s.", cor_inimiga);
    } 
    else if (sorteio == 1) {
        strcpy(destino, "Dominar 3 territorios.");
    } 
    else {
        strcpy(destino, "Acumular 10 tropas no total.");
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- RESULTADO DA BATALHA ---\n");
    
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas -= 1;
        
        if (defensor->tropas == 0) {
            int tropasMovidas = atacante->tropas / 2;
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = tropasMovidas;
            atacante->tropas -= tropasMovidas;
            printf("=> O exercito %s conquistou o territorio de %s!\n", atacante->cor, defensor->nome);
        }
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
    
    printf("\nPressione Enter para continuar para o proximo turno...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    getchar(); 
}

// Avalia as condições de vitória lendo e interpretando a string da missão.
int verificarMissao(char* missao, char* cor, Territorio* mapa, int tamanho) {
    int cont_territorios = 0;
    int cont_tropas = 0;

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, cor) == 0) {
            cont_territorios++;
            cont_tropas += mapa[i].tropas;
        }
    }

    if (strcmp(missao, "Dominar 3 territorios.") == 0 && cont_territorios >= 3) return 1;
    if (strcmp(missao, "Acumular 10 tropas no total.") == 0 && cont_tropas >= 10) return 1;

    // Lógica para verificar a missão de destruição ("Destruir o exercito X.")
    if (strncmp(missao, "Destruir o exercito", 19) == 0) {
        char cor_alvo[10];
        // Lê a cor a partir da string, ignorando o ponto final da frase
        sscanf(missao, "Destruir o exercito %[^.].", cor_alvo);
        
        int inimigo_vivo = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, cor_alvo) == 0) {
                inimigo_vivo = 1; // O inimigo ainda possui territórios
                break;
            }
        }
        if (!inimigo_vivo) return 1; // Inimigo extinto, missão cumprida
    }

    return 0; 
}

//  Limpa toda a memória alocada no programa.

void liberarMemoria(Territorio* mapa, char* missao) {
    if (mapa != NULL) {
        free(mapa);
    }
    if (missao != NULL) {
        free(missao);
    }
}