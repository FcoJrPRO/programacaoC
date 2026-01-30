#include <stdio.h>

int main() {
    // Inicialização da matriz 10x10 
    // 1. Inicialização do Tabuleiro
    // Aluno: Francisco Araújo de Paiva Junior
    // Nível: Mestre - Habilidades Especiais
    // 0 = Fundo
    // 1 = Padrão inferior esquerdo (triângulo/cone)
    // 2 = Padrão lateral direito (mancha)
    // 3 = Padrão superior (cruz/espada)
    int tabuleiro[10][10] = {
        {0, 0, 0, 3, 0, 0, 0, 0, 0, 0}, // Linha 0
        {0, 0, 0, 3, 0, 0, 0, 0, 0, 0}, // Linha 1
        {0, 3, 3, 3, 3, 3, 0, 0, 0, 0}, // Linha 2
        {0, 0, 0, 3, 0, 0, 0, 2, 0, 0}, // Linha 3
        {0, 0, 0, 3, 0, 0, 2, 2, 2, 0}, // Linha 4
        {0, 0, 1, 0, 0, 2, 2, 2, 2, 2}, // Linha 5
        {0, 1, 1, 1, 0, 0, 2, 2, 2, 0}, // Linha 6
        {1, 1, 1, 1, 1, 0, 0, 2, 0, 0}, // Linha 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Linha 8
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // Linha 9
    };

    // --- Exibição do Tabuleiro ---
    printf("\n***Representacao***\n\n");

    // Cabeçalho das colunas (A a J) 
    printf("  "); // Espaçamento inicial para alinhar com os números das linhas
    for (int k = 0; k < 10; k++) {
        // 'A' + 0 = A, 'A' + 1 = B, etc.
        printf("%c ", 'A' + k); 
    }
    printf("\n");

    // Loop para exibir a matriz
    for (int i = 0; i < 10; i++) {
        printf("%d ", i); // Exibe o índice da linha na esquerda
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}