#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest: Mapa da Mansão e Coleta de Pistas
// Aluno: Francisco Araújo de Paiva Junior
// Tema 4 - Árvores Binárias e Árvores Binárias de Busca (BST) (2º Semestre 2026)
// Nível: Aventureiro

// --- DEFINIÇÃO DAS ESTRUTURAS ---

// Struct que representa um nó da árvore de Pistas (BST)
typedef struct PistaNode {
    char descricao[100];         // Texto da pista
    struct PistaNode* esquerda;  // Pistas alfabeticamente menores
    struct PistaNode* direita;   // Pistas alfabeticamente maiores
} PistaNode;

// Struct que representa um nó da árvore do Mapa (Mansão)
typedef struct Sala {
    char nome[50];          // Nome da sala
    char pista[100];        // Pista escondida na sala (vazio se não houver)
    struct Sala* esquerda;  // Caminho da esquerda
    struct Sala* direita;   // Caminho da direita
} Sala;


// --- ASSINATURAS DAS FUNÇÕES ---
Sala* criarSala(const char* nome, const char* pista);
PistaNode* inserirPista(PistaNode* raiz, const char* descricao);
void explorarSalasComPistas(Sala* atual, PistaNode** raizPistas);
void exibirPistas(PistaNode* raiz);
void liberarMansao(Sala* raiz);
void liberarPistas(PistaNode* raiz);


// --- FUNÇÃO PRINCIPAL ---
int main() {
    printf("========================================\n");
    printf("      DETECTIVE QUEST - AVENTUREIRO     \n");
    printf("========================================\n\n");

    // 1. Construção manual da árvore da mansão com pistas
    Sala* raizMansao = criarSala("Hall de entrada", "Pegadas de lama na entrada.");
    
    // Nível 1
    raizMansao->esquerda = criarSala("Sala de estar", "Copo de cristal quebrado.");
    raizMansao->direita = criarSala("Biblioteca", "Livro de venenos aberto em cima da mesa.");
    
    // Nível 2
    raizMansao->esquerda->esquerda = criarSala("Cozinha", "Faca ausente no faqueiro.");
    raizMansao->esquerda->direita = criarSala("Jardim de Inverno", "Fio de tecido rasgado no espinheiro.");
    raizMansao->direita->esquerda = criarSala("Escritorio", "Cofre arrombado.");
    raizMansao->direita->direita = criarSala("Quarto Secreto", "Passagem oculta atras do quadro.");

    // 2. Inicialização da Árvore Binária de Busca (BST) para o inventário
    PistaNode* raizPistas = NULL;

    printf("Voce entrou na mansao. Explore os comodos e colete pistas!\n");

    // 3. Inicia a navegação interativa
    // Passamos o endereço da raizPistas para que a função possa modificá-la
    explorarSalasComPistas(raizMansao, &raizPistas);

    // 4. Fim do jogo: Exibe o relatório de pistas
    printf("\n========================================\n");
    printf("        RELATORIO DE INVESTIGACAO       \n");
    printf("========================================\n");
    printf("Pistas coletadas (em ordem alfabetica):\n");
    
    if (raizPistas == NULL) {
        printf("- Nenhuma pista foi encontrada.\n");
    } else {
        exibirPistas(raizPistas);
    }
    printf("========================================\n");

    // Libera a memória de ambas as árvores antes do encerramento
    liberarMansao(raizMansao);
    liberarPistas(raizPistas);

    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// criarSala() - Cria dinamicamente um cômodo com ou sem pista.
Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        strcpy(novaSala->pista, pista); // Copia o conteúdo da pista
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}

// inserirPista() - Insere recursivamente uma nova pista na árvore BST.
PistaNode* inserirPista(PistaNode* raiz, const char* descricao) {
    // Se chegou a um nó vazio, cria a nova pista aqui
    if (raiz == NULL) {
        PistaNode* novoNode = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novoNode->descricao, descricao);
        novoNode->esquerda = NULL;
        novoNode->direita = NULL;
        return novoNode;
    }

    // strcmp compara as strings. Se for < 0, a descrição é alfabeticamente menor.
    if (strcmp(descricao, raiz->descricao) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, descricao);
    } 
    // Se for > 0, a descrição é alfabeticamente maior.
    else if (strcmp(descricao, raiz->descricao) > 0) {
        raiz->direita = inserirPista(raiz->direita, descricao);
    }
    // Se for == 0, a pista é repetida e não a adicionamos (evita duplicatas).

    return raiz;
}

// explorarSalasComPistas() - Controla a navegação entre salas e a coleta automática de pistas.
void explorarSalasComPistas(Sala* atual, PistaNode** raizPistas) {
    char escolha;

    while (atual != NULL) {
        printf("\n----------------------------------------\n");
        printf("Local atual: [%s]\n", atual->nome);

        // Verifica se a sala possui uma pista (string não está vazia)
        if (strlen(atual->pista) > 0) {
            printf(">> ALERTA: Voce encontrou uma pista: \"%s\"\n", atual->pista);
            // Insere a pista na árvore BST
            *raizPistas = inserirPista(*raizPistas, atual->pista);
            
            // Limpa a pista da sala para não coletar a mesma caso haja alguma mecânica de retorno futura
            strcpy(atual->pista, ""); 
        } else {
            printf(">> Nenhuma pista nova neste comodo.\n");
        }

        // Exibe as opções de navegação
        printf("\nPara onde deseja ir?\n");
        if (atual->esquerda != NULL) {
            printf("(e) Esquerda - %s\n", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            printf("(d) Direita  - %s\n", atual->direita->nome);
        }
        printf("(s) Sair da exploracao (Encerrar e ver relatorio)\n");
        
        printf("Opcao: ");
        scanf(" %c", &escolha);

        // Processa a escolha do jogador
        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) atual = atual->esquerda;
            else printf(">> Parede solida! Nao ha caminho pela esquerda.\n");
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) atual = atual->direita;
            else printf(">> Parede solida! Nao ha caminho pela direita.\n");
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf(">> O detetive decide interromper as buscas e analisar as pistas.\n");
            break; // Sai do loop principal
        } 
        else {
            printf(">> Comando invalido. Tente 'e', 'd' ou 's'.\n");
        }
    }
}

// exibirPistas() - Imprime a árvore de pistas em ordem alfabética (Travessia In-Ordem).
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        // Visita a subárvore esquerda (menores)
        exibirPistas(raiz->esquerda);
        
        // Imprime o nó atual
        printf("- %s\n", raiz->descricao);
        
        // Visita a subárvore direita (maiores)
        exibirPistas(raiz->direita);
    }
}

// --- FUNÇÕES DE LIMPEZA DE MEMÓRIA ---

void liberarMansao(Sala* raiz) {
    if (raiz != NULL) {
        liberarMansao(raiz->esquerda);
        liberarMansao(raiz->direita);
        free(raiz);
    }
}

void liberarPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}