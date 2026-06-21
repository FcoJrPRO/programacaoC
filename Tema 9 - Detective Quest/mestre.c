#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Desafio Detective Quest: Sistema de Pistas e Acusacao
// Aluno: Francisco Araújo de Paiva Junior
// Tema 4 - Arvore Binaria, Arvore de Busca (BST) e Tabela Hash (2º Semestre 2026)
// Nível: Mestre

// --- CONFIGURACOES DA HASH ---
#define TAM_HASH 10

// --- DEFINICAO DAS ESTRUTURAS ---

// 1. Noh da Arvore de Pistas (BST)
typedef struct PistaNode {
    char descricao[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

// 2. Noh da Arvore da Mansao (Mapa)
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// 3. Noh da Tabela Hash (Dicionario Pista -> Suspeito)
typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode* prox; // Tratamento de colisoes por encadeamento
} HashNode;


// --- ASSINATURAS DAS FUNCOES ---
// Mapa
Sala* criarSala(const char* nome);
const char* obterPistaDaSala(const char* nomeSala);
void explorarSalas(Sala* atual, PistaNode** raizPistas);
void liberarMansao(Sala* raiz);

// BST de Pistas
PistaNode* inserirPista(PistaNode* raiz, const char* descricao);
void exibirPistas(PistaNode* raiz);
void contarPistasPorSuspeito(PistaNode* raiz, HashNode** tabela, const char* suspeitoAcusado, int* contador);
void liberarPistas(PistaNode* raiz);

// Tabela Hash
int calcularHash(const char* chave);
void inserirNaHash(HashNode** tabela, const char* pista, const char* suspeito);
const char* encontrarSuspeito(HashNode** tabela, const char* pista);
void liberarHash(HashNode** tabela);

// Lógica Final
void verificarSuspeitoFinal(PistaNode* raizPistas, HashNode** tabela);


// --- FUNCAO PRINCIPAL ---
int main() {
    printf("==================================================\n");
    printf("         DETECTIVE QUEST - JULGAMENTO FINAL       \n");
    printf("==================================================\n\n");

    // 1. Inicializa a Tabela Hash
    HashNode* tabelaHash[TAM_HASH];
    for (int i = 0; i < TAM_HASH; i++) tabelaHash[i] = NULL;

    // Popula a Tabela Hash com as associacoes Pista -> Suspeito
    inserirNaHash(tabelaHash, "Pegadas de lama", "Sr. Marinho");
    inserirNaHash(tabelaHash, "Cofre arrombado", "Sr. Marinho");
    inserirNaHash(tabelaHash, "Copo quebrado", "Coronel Mostarda");
    inserirNaHash(tabelaHash, "Fio de tecido rasgado", "Coronel Mostarda");
    inserirNaHash(tabelaHash, "Faca ausente", "Dona Branca");
    inserirNaHash(tabelaHash, "Livro de venenos", "Dona Branca");

    // 2. Montagem manual do Mapa da Mansao
    Sala* raizMansao = criarSala("Hall de entrada");
    raizMansao->esquerda = criarSala("Sala de estar");
    raizMansao->direita = criarSala("Biblioteca");
    raizMansao->esquerda->esquerda = criarSala("Cozinha");
    raizMansao->esquerda->direita = criarSala("Jardim de Inverno");
    raizMansao->direita->esquerda = criarSala("Escritorio");

    // 3. Inicializa a Arvore de Pistas (Inventario)
    PistaNode* raizPistas = NULL;

    printf("Explore a mansao, colete provas e descubra o culpado!\n");

    // 4. Inicia a exploracao
    explorarSalas(raizMansao, &raizPistas);

    // 5. Julgamento Final
    verificarSuspeitoFinal(raizPistas, tabelaHash);

    // 6. Limpeza de memoria
    liberarMansao(raizMansao);
    liberarPistas(raizPistas);
    liberarHash(tabelaHash);

    return 0;
}


// --- IMPLEMENTACAO: MAPA E EXPLORACAO ---

// criarSala() - Cria dinamicamente um comodo.
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Lógica codificada para associar pistas aos comodos.
const char* obterPistaDaSala(const char* nomeSala) {
    if (strcmp(nomeSala, "Hall de entrada") == 0) return "Pegadas de lama";
    if (strcmp(nomeSala, "Sala de estar") == 0) return "Copo quebrado";
    if (strcmp(nomeSala, "Biblioteca") == 0) return "Livro de venenos";
    if (strcmp(nomeSala, "Cozinha") == 0) return "Faca ausente";
    if (strcmp(nomeSala, "Jardim de Inverno") == 0) return "Fio de tecido rasgado";
    if (strcmp(nomeSala, "Escritorio") == 0) return "Cofre arrombado";
    return NULL; // Sala sem pista
}

// explorarSalas() - Navega pela arvore e ativa o sistema de pistas.
void explorarSalas(Sala* atual, PistaNode** raizPistas) {
    char escolha;

    while (atual != NULL) {
        printf("\n--------------------------------------------------\n");
        printf("Local atual: [%s]\n", atual->nome);

        // Verifica logica de pistas para a sala atual
        const char* pistaEncontrada = obterPistaDaSala(atual->nome);
        if (pistaEncontrada != NULL) {
            printf(">> ALERTA: Voce encontrou uma pista: \"%s\"\n", pistaEncontrada);
            *raizPistas = inserirPista(*raizPistas, pistaEncontrada);
        }

        printf("\nPara onde deseja ir?\n");
        if (atual->esquerda != NULL) printf("(e) Esquerda - %s\n", atual->esquerda->nome);
        if (atual->direita != NULL) printf("(d) Direita  - %s\n", atual->direita->nome);
        printf("(s) Sair e ir para o Tribunal\n");
        
        printf("Opcao: ");
        scanf(" %c", &escolha);
        getchar(); // Limpa o buffer do teclado (evita bugs no fgets depois)

        if (tolower(escolha) == 'e') {
            if (atual->esquerda != NULL) atual = atual->esquerda;
            else printf(">> Nao ha caminho por ai.\n");
        } 
        else if (tolower(escolha) == 'd') {
            if (atual->direita != NULL) atual = atual->direita;
            else printf(">> Nao ha caminho por ai.\n");
        } 
        else if (tolower(escolha) == 's') {
            break;
        } else {
            printf(">> Comando invalido.\n");
        }
    }
}


// --- IMPLEMENTACAO: ARVORE DE PISTAS (BST) ---

// inserirPista() - Insere a pista coletada na arvore de pistas em ordem alfabetica.
PistaNode* inserirPista(PistaNode* raiz, const char* descricao) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->descricao, descricao);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (strcmp(descricao, raiz->descricao) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, descricao);
    else if (strcmp(descricao, raiz->descricao) > 0)
        raiz->direita = inserirPista(raiz->direita, descricao);
    
    return raiz; // Evita duplicatas se for igual
}

void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->descricao);
        exibirPistas(raiz->direita);
    }
}


// --- IMPLEMENTACAO: TABELA HASH ---

int calcularHash(const char* chave) {
    int hash = 0;
    while (*chave) {
        hash += *chave++;
    }
    return hash % TAM_HASH;
}

// inserirNaHash() - Insere associacao pista/suspeito na tabela hash.
void inserirNaHash(HashNode** tabela, const char* pista, const char* suspeito) {
    int indice = calcularHash(pista);
    HashNode* novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    
    // Insere no inicio da lista encadeada (para tratar colisoes)
    novo->prox = tabela[indice];
    tabela[indice] = novo;
}

// encontrarSuspeito() - Consulta o suspeito correspondente a uma pista.
const char* encontrarSuspeito(HashNode** tabela, const char* pista) {
    int indice = calcularHash(pista);
    HashNode* atual = tabela[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->prox;
    }
    return "Desconhecido";
}


// --- IMPLEMENTACAO: LOGICA FINAL (JULGAMENTO) ---

// Percorre a arvore de pistas recursivamente e conta quantas apontam para o acusado
void contarPistasPorSuspeito(PistaNode* raiz, HashNode** tabela, const char* suspeitoAcusado, int* contador) {
    if (raiz != NULL) {
        contarPistasPorSuspeito(raiz->esquerda, tabela, suspeitoAcusado, contador);
        
        // Verifica na Hash de quem eh essa pista
        const char* donoDaPista = encontrarSuspeito(tabela, raiz->descricao);
        
        // strcasecmp ignoraria maiusculas, mas como nao eh padrao ANSI, usamos strstr para facilitar a busca flexivel
        if (strstr(donoDaPista, suspeitoAcusado) != NULL || strstr(suspeitoAcusado, donoDaPista) != NULL) {
            (*contador)++;
        }
        
        contarPistasPorSuspeito(raiz->direita, tabela, suspeitoAcusado, contador);
    }
}

// verificarSuspeitoFinal() - Conduz a fase de julgamento final.
void verificarSuspeitoFinal(PistaNode* raizPistas, HashNode** tabela) {
    char acusado[50];
    int evidencias = 0;

    printf("\n==================================================\n");
    printf("                  TRIBUNAL FINAL                  \n");
    printf("==================================================\n");
    
    if (raizPistas == NULL) {
        printf("Voce nao coletou NENHUMA pista! O caso foi arquivado.\n");
        return;
    }

    printf("Suas evidencias (Ordem Alfabetica):\n");
    exibirPistas(raizPistas);

    printf("\nOs suspeitos sao: Coronel Mostarda, Dona Branca e Sr. Marinho.\n");
    printf("Quem voce acusa? (Digite o nome): ");
    fgets(acusado, 50, stdin);
    acusado[strcspn(acusado, "\n")] = '\0'; // Remove o \n do final

    // Conta quantas provas no inventario (BST) apontam para o acusado usando a Hash
    contarPistasPorSuspeito(raizPistas, tabela, acusado, &evidencias);

    printf("\nAnalisando as provas contra [%s]...\n", acusado);
    printf("Provas encontradas no seu inventario: %d\n", evidencias);

    if (evidencias >= 2) {
        printf("\n>> PARABENS DETETIVE! Voce apresentou provas irrefutaveis.\n");
        printf(">> %s foi condenado(a) e preso(a)!\n", acusado);
    } else {
        printf("\n>> FALHOU! O juiz rejeitou o caso por falta de evidencias.\n");
        printf(">> %s saiu andando livremente pelo tribunal.\n", acusado);
    }
}

// --- FUNCOES DE LIMPEZA DE MEMORIA ---

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

void liberarHash(HashNode** tabela) {
    for (int i = 0; i < TAM_HASH; i++) {
        HashNode* atual = tabela[i];
        while (atual != NULL) {
            HashNode* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}