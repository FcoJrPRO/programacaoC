#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack: Simular uma fila de peças
// Aluno: Francisco Araújo de Paiva Junior
// Tema 3 - Pilhas e Filas (2º Semestre 2026)
// Nível: Novato

// --- CONFIGURAÇÕES DA FILA ---
#define MAX_FILA 5 // Capacidade máxima da fila de peças futuras

// --- DEFINIÇÃO DAS ESTRUTURAS (STRUCTS) ---

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único (ordem de criação)
} Peca;

// Estrutura que representa a Fila Circular
typedef struct {
    Peca elementos[MAX_FILA]; // Array para armazenar as peças
    int frente;               // Índice do primeiro elemento (frente da fila)
    int tras;                 // Índice do último elemento inserido
    int tamanho;              // Quantidade atual de elementos na fila
} FilaCircular;


// --- ASSINATURAS DAS FUNÇÕES ---
void inicializarFila(FilaCircular *f);
int filaCheia(FilaCircular *f);
int filaVazia(FilaCircular *f);
Peca gerarPeca();
void enqueue(FilaCircular *f, Peca p);
void dequeue(FilaCircular *f);
void exibirFila(FilaCircular *f);


// --- FUNÇÃO PRINCIPAL ---
int main() {
    // Configura a semente para geração de números aleatórios
    srand(time(NULL));

    FilaCircular fila;
    inicializarFila(&fila);

    // Inicializa a fila preenchendo-a com o número máximo de peças iniciais
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    // Loop do menu principal
    do {
        printf("\n========================================\n");
        printf("          TETRIS STACK - FILA           \n");
        printf("========================================\n");
        
        // Exibe o estado atual da fila de peças
        exibirFila(&fila);

        // Exibe as opções de ação
        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer se o usuário não digitar um número
            while (getchar() != '\n'); 
            opcao = -1;
        }

        printf("\n");

        // Controle de fluxo com base na escolha do jogador
        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                if (filaCheia(&fila)) {
                    printf("AVISO: A fila esta cheia! Jogue uma peca primeiro.\n");
                } else {
                    enqueue(&fila, gerarPeca());
                    printf("Sucesso: Nova peca adicionada a fila.\n");
                }
                break;
            case 0:
                printf("Encerrando o sistema da ByteBros. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Inicializa os ponteiros e o tamanho da fila
void inicializarFila(FilaCircular *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Verifica se a fila atingiu a capacidade máxima
int filaCheia(FilaCircular *f) {
    return f->tamanho == MAX_FILA;
}

// Verifica se a fila não possui elementos
int filaVazia(FilaCircular *f) {
    return f->tamanho == 0;
}

// Gera uma peça aleatória ('I', 'O', 'T', 'L') e atribui um ID único incremental
Peca gerarPeca() {
    static int contador_id = 0; // Variável estática para manter o incremento do ID
    char tiposPossiveis[] = {'I', 'O', 'T', 'L'};
    int quantidadeTipos = 4;
    
    int indiceAleatorio = rand() % quantidadeTipos;

    Peca novaPeca;
    novaPeca.nome = tiposPossiveis[indiceAleatorio];
    novaPeca.id = contador_id++; // Atribui e depois incrementa

    return novaPeca;
}

// Insere uma nova peça no final da fila circular (Enqueue)
void enqueue(FilaCircular *f, Peca p) {
    if (filaCheia(f)) {
        return; // Retorna silenciosamente, a validação principal é feita no main()
    }
    
    // Cálculo modular para reaproveitamento de espaço circular
    f->tras = (f->tras + 1) % MAX_FILA; 
    f->elementos[f->tras] = p;
    f->tamanho++;
}

// Remove a peça da frente da fila circular (Dequeue)
void dequeue(FilaCircular *f) {
    if (filaVazia(f)) {
        printf("AVISO: A fila esta vazia! Nao ha pecas para jogar.\n");
        return;
    }

    Peca pecaRemovida = f->elementos[f->frente];
    
    // Avança a frente da fila circularmente
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;

    printf("Peca [%c %d] foi jogada no tabuleiro!\n", pecaRemovida.nome, pecaRemovida.id);
}

// Exibe todas as peças atualmente na fila, da frente para trás
void exibirFila(FilaCircular *f) {
    printf("Fila de pecas: ");
    
    if (filaVazia(f)) {
        printf("[Vazia]\n");
        return;
    }

    // Itera pela quantidade de elementos atuais na fila
    for (int i = 0; i < f->tamanho; i++) {
        // Encontra o índice correto baseado na frente da fila
        int indice = (f->frente + i) % MAX_FILA;
        printf("[%c %d] ", f->elementos[indice].nome, f->elementos[indice].id);
    }
    printf("\n");
}