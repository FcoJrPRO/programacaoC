#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack: Fila e Pilha de reserva
// Aluno: Francisco Araújo de Paiva Junior
// Tema 3 - Pilhas e Filas (2º Semestre 2026)
// Nível: Intermediário

// --- CONFIGURAÇÕES ---
#define MAX_FILA 5  // Capacidade máxima da fila de peças futuras
#define MAX_PILHA 3 // Capacidade máxima da pilha de peças reservadas

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

// Estrutura que representa a Pilha (Reserva)
typedef struct {
    Peca elementos[MAX_PILHA]; // Array para armazenar as peças reservadas
    int topo;                  // Índice do elemento no topo da pilha
} Pilha;

// --- ASSINATURAS DAS FUNÇÕES ---
// Fila
void inicializarFila(FilaCircular *f);
int filaCheia(FilaCircular *f);
int filaVazia(FilaCircular *f);
void enqueue(FilaCircular *f, Peca p);
Peca dequeue(FilaCircular *f);
void exibirFila(FilaCircular *f);

// Pilha
void inicializarPilha(Pilha *p);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void push(Pilha *p, Peca p_nova);
Peca pop(Pilha *p);
void exibirPilha(Pilha *p);

// Peças
Peca gerarPeca();


// --- FUNÇÃO PRINCIPAL ---
int main() {
    // Configura a semente para geração de números aleatórios
    srand(time(NULL));

    FilaCircular fila;
    Pilha pilha;
    
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inicializa a fila preenchendo-a completamente
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    // Loop do menu principal
    do {
        printf("\n========================================\n");
        printf("Estado atual:\n");
        
        // Exibe o estado atual da fila e da pilha
        exibirFila(&fila);
        exibirPilha(&pilha);
        
        printf("========================================\n");

        // Exibe as opções de ação conforme a tabela do desafio
        printf("Opcoes de Acao:\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer se o usuário digitar algo não numérico
            while (getchar() != '\n'); 
            opcao = -1;
        }

        printf("\n");
        Peca peca_movimentada; // Variável para armazenar a peça em trânsito

        // Controle de fluxo com base na escolha do jogador
        switch (opcao) {
            case 1:
                // Jogar peça (Remove da fila e gera uma nova para o final)
                if (!filaVazia(&fila)) {
                    peca_movimentada = dequeue(&fila);
                    printf(">> Peca [%c %d] foi jogada no tabuleiro!\n", peca_movimentada.nome, peca_movimentada.id);
                    // Mantém a fila cheia
                    enqueue(&fila, gerarPeca());
                }
                break;
                
            case 2:
                // Reservar peça (Remove da fila e coloca na pilha)
                if (pilhaCheia(&pilha)) {
                    printf(">> AVISO: A pilha de reserva esta cheia! Use uma peca reservada primeiro.\n");
                } else if (!filaVazia(&fila)) {
                    peca_movimentada = dequeue(&fila);
                    push(&pilha, peca_movimentada);
                    printf(">> Peca [%c %d] foi movida para a reserva!\n", peca_movimentada.nome, peca_movimentada.id);
                    // Mantém a fila cheia
                    enqueue(&fila, gerarPeca());
                }
                break;
                
            case 3:
                // Usar peça reservada (Remove do topo da pilha e joga)
                if (!pilhaVazia(&pilha)) {
                    peca_movimentada = pop(&pilha);
                    printf(">> Peca reservada [%c %d] foi jogada no tabuleiro!\n", peca_movimentada.nome, peca_movimentada.id);
                } else {
                    printf(">> AVISO: A pilha de reserva esta vazia!\n");
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


// --- IMPLEMENTAÇÃO DAS FUNÇÕES: FILA ---

void inicializarFila(FilaCircular *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int filaCheia(FilaCircular *f) {
    return f->tamanho == MAX_FILA;
}

int filaVazia(FilaCircular *f) {
    return f->tamanho == 0;
}

void enqueue(FilaCircular *f, Peca p) {
    if (filaCheia(f)) return; 
    
    // Avança circularmente o índice "tras"
    f->tras = (f->tras + 1) % MAX_FILA; 
    f->elementos[f->tras] = p;
    f->tamanho++;
}

// Alterado para retornar a peça removida em vez de 'void'
Peca dequeue(FilaCircular *f) {
    Peca pecaRemovida = f->elementos[f->frente];
    // Avança circularmente a "frente"
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return pecaRemovida;
}

void exibirFila(FilaCircular *f) {
    printf("Fila de pecas: ");
    if (filaVazia(f)) {
        printf("[Vazia]\n");
        return;
    }
    for (int i = 0; i < f->tamanho; i++) {
        int indice = (f->frente + i) % MAX_FILA;
        printf("[%c %d] ", f->elementos[indice].nome, f->elementos[indice].id);
    }
    printf("\n");
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES: PILHA ---

void inicializarPilha(Pilha *p) {
    p->topo = -1; // Topo igual a -1 indica pilha vazia
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca p_nova) {
    if (pilhaCheia(p)) return;
    p->topo++;
    p->elementos[p->topo] = p_nova; // Adiciona no novo topo
}

Peca pop(Pilha *p) {
    Peca pecaRemovida = p->elementos[p->topo];
    p->topo--; // Rebaixa o topo
    return pecaRemovida;
}

void exibirPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p)) {
        printf("[Vazia]\n");
        return;
    }
    // A pilha é exibida de cima para baixo (do último a entrar até o primeiro)
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->elementos[i].nome, p->elementos[i].id);
    }
    printf("\n");
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES: PEÇAS ---

Peca gerarPeca() {
    static int contador_id = 0; // Mantém a contagem de ID entre as chamadas
    char tiposPossiveis[] = {'I', 'O', 'T', 'L'};
    
    Peca novaPeca;
    novaPeca.nome = tiposPossiveis[rand() % 4]; // Escolhe um tipo aleatoriamente
    novaPeca.id = contador_id++; // Atribui o ID e depois incrementa
    
    return novaPeca;
}