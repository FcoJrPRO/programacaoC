#include <stdio.h>

    // Desafio Jogo do Xadrez
    // Aluno: Francisco Araújo de Paiva Junior
    // Tema 4 - Movimentação de Peças de Xadrez
    // Nível: Aventureiro
    // Objetivo: Simular movimentos de peças de xadrez utilizando estruturas de repetição aninhadas

int main() {

    // Definindo valores através de variáveis/constantes
    int movimentosTorre = 5;
    int movimentosBispo = 5;
    int movimentosRainha = 8;
    
    // Variáveis para o movimento do Cavalo (Nível Aventureiro)
    int movimentosCavaloBaixo = 2;
    int movimentosCavaloEsquerda = 1;

    // --- 1. Movimentação da TORRE ---
    printf("***Movimento da Torre***\n");
    for (int i = 0; i < movimentosTorre; i++) {
        printf("Direita\n");
    }
    
    printf("\n"); 

    // --- 2. Movimentação do BISPO ---
    printf("***Movimento do Bispo***\n");
    int contadorBispo = 0;
    while (contadorBispo < movimentosBispo) {
        printf("Cima, Direita\n"); 
        contadorBispo++;
    }

    printf("\n"); 

    // --- 3. Movimentação da RAINHA ---
    printf("***Movimento da Rainha***\n");
    int contadorRainha = 0;
    do {
        printf("Esquerda\n");
        contadorRainha++;
    } while (contadorRainha < movimentosRainha);

    printf("\n"); 

    // --- 4. Movimentação do CAVALO (Nível Aventureiro) ---
    // Lógica: 2 casas para Baixo e 1 para a Esquerda.
    // Estrutura: Loops aninhados (For externo, While interno)
    
    printf("***Movimento do Cavalo***\n");

    // Loop Externo (FOR): Responsável pelo movimento vertical (Baixo)
    for (int i = 0; i < movimentosCavaloBaixo; i++) {
        
        printf("Baixo\n");

        // Loop Interno (WHILE): Responsável pelo movimento horizontal (Esquerda)
        // A lógica complexa do "L" exige que a curva seja feita apenas após completar a parte vertical.
        // Portanto, usamos uma condição: se estamos na última casa do movimento vertical (i == 1), fazemos a curva.
        
        if (i == (movimentosCavaloBaixo - 1)) {
            int j = 0;
            // Loop aninhado obrigatório conforme requisitos
            while (j < movimentosCavaloEsquerda) {
                printf("Esquerda\n");
                j++;
            }
        }
    }

    return 0;
}