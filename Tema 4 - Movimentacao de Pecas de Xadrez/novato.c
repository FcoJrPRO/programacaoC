#include <stdio.h>

    // Desafio Jogo do Xadrez
    // Aluno: Francisco Araújo de Paiva Junior
    // Tema 4 - Movimentação de Peças de Xadrez
    // Nível: Novato
    //Simular movimentos de peças de xadrez utilizando estruturas de repetição
    
    
int main() {

    // Definindo valores através de variáveis/constantes
    int movimentosTorre = 5;
    int movimentosBispo = 5;
    int movimentosRainha = 8;

    // --- 1. Movimentação da TORRE ---
    // Estrutura escolhida: for
    //Torre: 5 casas para a Direita 
    
    printf("***Movimento da Torre***\n");
    for (int i = 0; i < movimentosTorre; i++) {
        printf("Direita\n");
    }
    
    printf("\n"); // Pula uma linha para organizar a saída

    // --- 2. Movimentação do BISPO ---
    // Estrutura escolhida: while
    //Bispo: 5 casas na Diagonal Cima/Direita 
    
    printf("***Movimento do Bispo***\n");
    int contadorBispo = 0;
    while (contadorBispo < movimentosBispo) {
        printf("Cima, Direita\n"); // Movimento composto (Diagonal)
        contadorBispo++;
    }

    printf("\n"); 

    // --- 3. Movimentação da RAINHA ---
    // Estrutura escolhida: do-while
    //Rainha: 8 casas para a Esquerda
    
    printf("***Movimento da Rainha***\n");
    int contadorRainha = 0;
    do {
        printf("Esquerda\n");
        contadorRainha++;
    } while (contadorRainha < movimentosRainha);

    return 0;
}