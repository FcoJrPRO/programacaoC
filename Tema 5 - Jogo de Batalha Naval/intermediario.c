#include <stdio.h>

int main() {
    
    // ***1. Representação do Tabuleiro Batalha Naval***
    // Aluno: Francisco Araújo de Paiva Junior
    // Tema 5 - Jogo de Batalha Naval
    // Nível: Intermediario
    // Cria uma matriz 10x10 preenchida com 0 (água)
    // A sintaxe {0} inicializa todos os elementos com zero.
    int tabuleiro[10][10] = {0};

    // Navios continuam sendo representados pelo valor 3
    // Tamanho fixo de 3 partes para todos os navios
    int tamanhoNavio = 3;

    //***2. Definição das Coordenadas Iniciais***
    // Navio 1: Horizontal
    int linH = 1, colH = 1; 

    // Navio 2: Vertical
    int linV = 2, colV = 6; 

    // Navio 3: Diagonal Principal (Desce para a direita)
    // Lógica: Linha aumenta, Coluna aumenta
    int linD1 = 5, colD1 = 0; 

    // Navio 4: Diagonal Secundária (Sobe para a direita)
    // Lógica: Linha diminui, Coluna aumenta
    int linD2 = 8, colD2 = 6;

    //***3. Posicionamento dos Navios***

    //***Navio 1: Horizontal***
    // Validação de limites (coluna + tamanho <= 10)
    if (colH + tamanhoNavio <= 10) {
        for (int i = 0; i < tamanhoNavio; i++) {
            // Verifica sobreposição antes de colocar
            if (tabuleiro[linH][colH + i] == 0) {
                tabuleiro[linH][colH + i] = 3;
            } else {
                printf("Erro: Sobreposição detectada no Navio Horizontal!\n");
            }
        }
    } else {
        printf("Erro: Navio Horizontal fora dos limites.\n");
    }

    //***Navio 2: Vertical***
    // Validação de limites (linha + tamanho <= 10)
    if (linV + tamanhoNavio <= 10) {
        for (int i = 0; i < tamanhoNavio; i++) {
            if (tabuleiro[linV + i][colV] == 0) {
                tabuleiro[linV + i][colV] = 3;
            } else {
                printf("Erro: Sobreposição detectada no Navio Vertical!\n");
            }
        }
    } else {
        printf("Erro: Navio Vertical fora dos limites.\n");
    }

    //***Navio 3: Diagonal (Descendo à direita)***
    // Validação: Precisa de espaço tanto na linha quanto na coluna
    if (linD1 + tamanhoNavio <= 10 && colD1 + tamanhoNavio <= 10) {
        for (int i = 0; i < tamanhoNavio; i++) {
            // O segredo da diagonal: somamos 'i' na linha E na coluna simultaneamente
            if (tabuleiro[linD1 + i][colD1 + i] == 0) {
                tabuleiro[linD1 + i][colD1 + i] = 3;
            } else {
                printf("Erro: Sobreposição detectada no Navio Diagonal 1!\n");
            }
        }
    } else {
        printf("Erro: Navio Diagonal 1 fora dos limites.\n");
    }

    //***Navio 4: Diagonal (Subindo à direita)***
    // Validação: Precisa ter linhas "para cima" (linha - tamanho >= -1) e colunas "para a direita"
    if (linD2 - tamanhoNavio >= -1 && colD2 + tamanhoNavio <= 10) {
        for (int i = 0; i < tamanhoNavio; i++) {
            // O segredo da diagonal inversa: subtraímos 'i' da linha e somamos na coluna
            if (tabuleiro[linD2 - i][colD2 + i] == 0) {
                tabuleiro[linD2 - i][colD2 + i] = 3;
            } else {
                printf("Erro: Sobreposição detectada no Navio Diagonal 2!\n");
            }
        }
    } else {
        printf("Erro: Navio Diagonal 2 fora dos limites.\n");
    }

    //***4. Exibição do Tabuleiro***
    printf("\n--- Batalha Naval: Nivel Aventureiro ---\n\n");

    // Cabeçalho das Colunas (A-J)
    printf("   ");
    for (int k = 0; k < 10; k++) {
        printf("%c ", 'A' + k);
    }
    printf("\n");

    // Exibição da Matriz
    for (int i = 0; i < 10; i++) {
        printf("%d |", i); // Índice da linha
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}