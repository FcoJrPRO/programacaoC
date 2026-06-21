#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack: Fila e Pilha de reserva com Trocas
// Aluno: Francisco Araújo de Paiva Junior
// Tema 3 - Pilhas e Filas (2º Semestre 2026)
// Nível: Mestre

// --- CONFIGURAÇÕES ---
#define MAX_FILA 5  // Capacidade máxima da fila de peças futuras
#define MAX_PILHA 3 // Capacidade máxima da pilha de peças reservadas

// --- DEFINIÇÃO DAS ESTRUTURAS (STRUCTS) ---

typedef struct {
    char nome; 
    int id;    
} Peca;

typedef struct {
    Peca elementos[MAX_FILA]; 
    int frente;               
    int tras;                 
    int tamanho;              
} FilaCircular;

typedef struct {
    Peca elementos[MAX_PILHA]; 
    int topo;                  
} Pilha;

// --- ASSINATURAS DAS FUNÇÕES ---
void inicializarFila(FilaCircular *f);
int filaCheia(FilaCircular *f);
int filaVazia(FilaCircular *f);
void enqueue(FilaCircular *f, Peca p);
Peca dequeue(FilaCircular *f);
void exibirFila(FilaCircular *f);

void inicializarPilha(Pilha *p);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void push(Pilha *p, Peca p_nova);
Peca pop(Pilha *p);
void exibirPilha(Pilha *p);

Peca gerarPeca();

// Novas Funções de Troca
void trocarPecaAtual(FilaCircular *f, Pilha *p);
void trocaMultipla(FilaCircular *f, Pilha *p);


// --- FUNÇÃO PRINCIPAL ---
int main() {
    srand(time(NULL));

    FilaCircular fila;
    Pilha pilha;
    
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila inicial
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        printf("\n========================================\n");
        printf("Estado atual:\n");
        exibirFila(&fila);
        exibirPilha(&pilha);
        printf("========================================\n");

        printf("Opcoes disponiveis:\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para a pilha de reserva\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
        printf("0 - Sair\n");
        printf("Opcao escolhida: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); 
            opcao = -1;
        }

        printf("\n");
        Peca peca_movimentada;

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    peca_movimentada = dequeue(&fila);
                    printf(">> Acao: Peca [%c %d] foi jogada no tabuleiro!\n", peca_movimentada.nome, peca_movimentada.id);
                    enqueue(&fila, gerarPeca());
                }
                break;
                
            case 2:
                if (pilhaCheia(&pilha)) {
                    printf(">> AVISO: A pilha de reserva esta cheia!\n");
                } else if (!filaVazia(&fila)) {
                    peca_movimentada = dequeue(&fila);
                    push(&pilha, peca_movimentada);
                    printf(">> Acao: Peca [%c %d] movida para a reserva!\n", peca_movimentada.nome, peca_movimentada.id);
                    enqueue(&fila, gerarPeca());
                }
                break;
                
            case 3:
                if (!pilhaVazia(&pilha)) {
                    peca_movimentada = pop(&pilha);
                    printf(">> Acao: Peca reservada [%c %d] foi jogada!\n", peca_movimentada.nome, peca_movimentada.id);
                } else {
                    printf(">> AVISO: A pilha de reserva esta vazia!\n");
                }
                break;

            case 4:
                trocarPecaAtual(&fila, &pilha);
                break;

            case 5:
                trocaMultipla(&fila, &pilha);
                break;
                
            case 0:
                printf("Encerrando o sistema da ByteBros. Ate logo!\n");
                break;
                
            default:
                printf(">> Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES DE TROCA (NÍVEL MESTRE) ---

// Troca 1 por 1: Frente da Fila <-> Topo da Pilha
void trocarPecaAtual(FilaCircular *f, Pilha *p) {
    if (filaVazia(f)) {
        printf(">> AVISO: Fila vazia, impossivel trocar.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf(">> AVISO: Pilha vazia, impossivel trocar. Reserve uma peca primeiro.\n");
        return;
    }

    // Acessa diretamente os elementos para realizar a troca
    Peca temp = f->elementos[f->frente];
    f->elementos[f->frente] = p->elementos[p->topo];
    p->elementos[p->topo] = temp;

    printf(">> Acao: Troca realizada entre a frente da fila e o topo da pilha.\n");
}

// Troca 3 por 3: Inverte e substitui as três primeiras peças
void trocaMultipla(FilaCircular *f, Pilha *p) {
    if (f->tamanho < 3) {
        printf(">> AVISO: Fila possui menos de 3 pecas. Impossivel realizar a troca multipla.\n");
        return;
    }
    if (p->topo < 2) { // Topo == 2 significa que há 3 peças (0, 1 e 2)
        printf(">> AVISO: A pilha precisa estar completamente cheia (3 pecas) para a troca multipla.\n");
        return;
    }

    // Captura as três primeiras peças da fila, respeitando a circularidade
    int i0 = f->frente;
    int i1 = (f->frente + 1) % MAX_FILA;
    int i2 = (f->frente + 2) % MAX_FILA;

    Peca q0 = f->elementos[i0];
    Peca q1 = f->elementos[i1];
    Peca q2 = f->elementos[i2];

    // Captura as três peças da pilha (s0 = base, s1 = meio, s2 = topo)
    Peca s0 = p->elementos[0]; 
    Peca s1 = p->elementos[1]; 
    Peca s2 = p->elementos[2]; 

    // Alimenta a fila com as peças da pilha (invertendo a ordem conforme o exemplo)
    f->elementos[i0] = s2; // Topo da pilha vai para a frente da fila
    f->elementos[i1] = s1; // Meio com meio
    f->elementos[i2] = s0; // Base da pilha vai para a 3ª posição da fila

    // Alimenta a pilha com as peças da fila
    p->elementos[0] = q0; // Frente da fila vai para a base da pilha
    p->elementos[1] = q1; // 2ª da fila vai para o meio
    p->elementos[2] = q2; // 3ª da fila vai para o topo da pilha

    printf(">> Acao: Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
}


// --- IMPLEMENTAÇÃO DAS ESTRUTURAS BÁSICAS ---

void inicializarFila(FilaCircular *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int filaCheia(FilaCircular *f) { return f->tamanho == MAX_FILA; }
int filaVazia(FilaCircular *f) { return f->tamanho == 0; }

void enqueue(FilaCircular *f, Peca p) {
    if (filaCheia(f)) return; 
    f->tras = (f->tras + 1) % MAX_FILA; 
    f->elementos[f->tras] = p;
    f->tamanho++;
}

Peca dequeue(FilaCircular *f) {
    Peca pecaRemovida = f->elementos[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return pecaRemovida;
}

void exibirFila(FilaCircular *f) {
    printf("Fila de pecas\t\t: ");
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

void inicializarPilha(Pilha *p) { p->topo = -1; }
int pilhaCheia(Pilha *p) { return p->topo == MAX_PILHA - 1; }
int pilhaVazia(Pilha *p) { return p->topo == -1; }

void push(Pilha *p, Peca p_nova) {
    if (pilhaCheia(p)) return;
    p->topo++;
    p->elementos[p->topo] = p_nova;
}

Peca pop(Pilha *p) {
    Peca pecaRemovida = p->elementos[p->topo];
    p->topo--; 
    return pecaRemovida;
}

void exibirPilha(Pilha *p) {
    printf("Pilha de reserva\t: ");
    if (pilhaVazia(p)) {
        printf("[Vazia]\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->elementos[i].nome, p->elementos[i].id);
    }
    printf("\n");
}

Peca gerarPeca() {
    static int contador_id = 0; 
    char tiposPossiveis[] = {'I', 'O', 'T', 'L'};
    Peca novaPeca;
    novaPeca.nome = tiposPossiveis[rand() % 4]; 
    novaPeca.id = contador_id++; 
    return novaPeca;
}