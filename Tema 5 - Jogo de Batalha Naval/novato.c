#include <stdio.h>

int main() {
    // ***1. Representação do Tabuleiro Batalha Naval***
    // Aluno: Francisco Araújo de Paiva Junior
    // Tema 5 - Jogo de Batalha Naval
    // Nível: Novato
    // Cria uma matriz 10x10 preenchida com 0 (água)
    // A sintaxe {0} inicializa todos os elementos com zero.
    int tabuleiro[10][10] = {0};

    // Navios representados por vetores com valor 3
    int navioHorizontal[3] = {3, 3, 3};
    int navioVertical[3] = {3, 3, 3};

    // ***2. Definição das Coordenadas Iniciais***
    // Coordenadas escolhidas (fixas no código)
    int linhaNavioH = 2;   // Linha 2
    int colunaNavioH = 4;  // Coluna 4 (equivalente a 'E')

    int linhaNavioV = 6;   // Linha 6
    int colunaNavioV = 7;  // Coluna 7 (equivalente a 'H')

    //***3. Posicionamento do Navio Horizontal***
    // Verifica limites (coluna inicial + tamanho do navio <= 10)
    if (colunaNavioH + 3 <= 10) {
        for (int i = 0; i < 3; i++) {
            // tabuleiro[linha fixa][coluna varia]
            tabuleiro[linhaNavioH][colunaNavioH + i] = navioHorizontal[i];
        }
    } else {
        printf("Erro: Navio horizontal fora dos limites!\n");
    }

    //***4. Posicionamento do Navio Vertical***
    // Verifica limites (linha inicial + tamanho do navio <= 10)
    if (linhaNavioV + 3 <= 10) {
        for (int i = 0; i < 3; i++) {
            // tabuleiro[linha varia][coluna fixa]
            tabuleiro[linhaNavioV + i][colunaNavioV] = navioVertical[i];
        }
    } else {
        printf("Erro: Navio vertical fora dos limites!\n");
    }

    // *** 5. Exibição do Tabuleiro (Com Letras A-J) ***
    printf("\n***Batalha Naval***\n\n");

    // Cabeçalho das Colunas (A até J)
    printf("   "); // Espaço para alinhar com os números das linhas
    for (int k = 0; k < 10; k++) {
        // Truque do ASCII: 'A' + 0 = A, 'A' + 1 = B, etc.
        printf("%c ", 'A' + k); 
    }
    printf("\n");

    // Exibição das Linhas e da Matriz
    for (int i = 0; i < 10; i++) {
        // Exibe o número da linha (0 a 9)
        printf("%d |", i); 
        
        // Exibe o conteúdo da linha
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Nova linha
    }

    return 0;
}