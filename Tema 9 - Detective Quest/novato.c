#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest: Mapa da Mansão
// Aluno: Francisco Araújo de Paiva Junior
// Tema 4 - Árvores Binárias (2º Semestre 2026)
// Nível: Novato

// --- DEFINIÇÃO DA ESTRUTURA ---

// Struct que representa um nó da árvore (um cômodo da mansão)
typedef struct Sala {
    char nome[50];          // Nome da sala
    struct Sala* esquerda;  // Ponteiro para o caminho da esquerda
    struct Sala* direita;   // Ponteiro para o caminho da direita
} Sala;

// --- ASSINATURAS DAS FUNÇÕES ---
Sala* criarSala(const char* nome);
void explorarSalas(Sala* atual);
void liberarMansao(Sala* atual);


// --- FUNÇÃO PRINCIPAL ---
// main() - Monta o mapa inicial e dá início à exploração.
int main() {
    printf("========================================\n");
    printf("      DETECTIVE QUEST - A MANSAO        \n");
    printf("========================================\n\n");
    printf("Voce acaba de entrar na mansao. O culpado deixou pistas...\n");

    // Construção manual da árvore binária da mansão
    // Raiz da árvore
    Sala* raiz = criarSala("Hall de entrada");

    // Nível 1
    raiz->esquerda = criarSala("Sala de estar");
    raiz->direita = criarSala("Biblioteca");

    // Nível 2 (Caminhos a partir da Sala de estar)
    raiz->esquerda->esquerda = criarSala("Cozinha");
    raiz->esquerda->direita = criarSala("Jardim de Inverno");

    // Nível 2 (Caminhos a partir da Biblioteca)
    raiz->direita->esquerda = criarSala("Escritorio");
    raiz->direita->direita = criarSala("Quarto Secreto");

    // Inicia a navegação interativa a partir da raiz (Hall de entrada)
    explorarSalas(raiz);

    // Boa prática de programação: liberar a memória alocada dinamicamente antes de sair
    liberarMansao(raiz);

    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// criarSala() - Cria, de forma dinâmica, uma sala com nome.
// Retorna o ponteiro para a nova sala alocada na memória.
Sala* criarSala(const char* nome) {
    // Aloca memória dinamicamente para o novo nó da árvore
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocação foi bem-sucedida
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome); // Copia o nome recebido para a struct
        novaSala->esquerda = NULL;    // Inicializa os ponteiros sem caminhos
        novaSala->direita = NULL;
    }
    
    return novaSala;
}

// explorarSalas() - Permite a navegação interativa do jogador pela árvore.
void explorarSalas(Sala* atual) {
    char escolha;

    // Loop de exploração: continua enquanto houver uma sala válida
    while (atual != NULL) {
        printf("\n----------------------------------------\n");
        printf("Local atual: [%s]\n", atual->nome);

        // Verifica se chegamos a um nó-folha (sala sem saídas)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf(">> Fim do caminho! Voce investigou o(a) %s e encontrou uma pista.\n", atual->nome);
            printf(">> Retorne para relatar suas descobertas.\n");
            break; // Encerra a exploração
        }

        // Exibe as opções de caminho disponíveis
        printf("\nPara onde deseja ir?\n");
        if (atual->esquerda != NULL) {
            printf("(e) Esquerda - Ir para: %s\n", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            printf("(d) Direita  - Ir para: %s\n", atual->direita->nome);
        }
        printf("(s) Sair da exploracao\n");
        
        printf("Opcao: ");
        scanf(" %c", &escolha);

        // Controle condicional da decisão do jogador
        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda; // O ponteiro "atual" avança para o nó filho à esquerda
            } else {
                printf(">> Nao ha caminho por ai! Tente outra direcao.\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita; // O ponteiro "atual" avança para o nó filho à direita
            } else {
                printf(">> Nao ha caminho por ai! Tente outra direcao.\n");
            }
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf(">> Voce decidiu sair da mansao por enquanto. Fim de jogo!\n");
            break; // Sai do loop e encerra a exploração
        } 
        else {
            printf(">> Comando invalido. Use 'e', 'd' ou 's'.\n");
        }
    }
}

// Função auxiliar para evitar vazamento de memória (Memory Leak)
// Percorre a árvore deletando os nós de baixo para cima (Pós-ordem)
void liberarMansao(Sala* atual) {
    if (atual != NULL) {
        liberarMansao(atual->esquerda);
        liberarMansao(atual->direita);
        free(atual); // Libera o espaço de memória que foi reservado pelo malloc()
    }
}