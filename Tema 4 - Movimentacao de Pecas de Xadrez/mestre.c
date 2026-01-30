#include <stdio.h>

// Desafio Jogo do Xadrez
// Aluno: Francisco Araújo de Paiva Junior
// Tema: Movimentação de Peças com Recursividade e Loops Complexos
// Nível: Mestre

// --- PROTÓTIPOS DAS FUNÇÕES RECURSIVAS ---
// Recursividade substitui os loops simples. A função chama a si mesma
// até que uma condição de parada (casas > 0) seja falsa.

void moverTorreRecursivo(int casas) {
    if (casas > 0) {
        printf("Direita\n");
        moverTorreRecursivo(casas - 1); // Chamada recursiva com decremento
    }
}

void moverRainhaRecursivo(int casas) {
    if (casas > 0) {
        printf("Esquerda\n");
        moverRainhaRecursivo(casas - 1);
    }
}

// Bispo: Recursividade + Loops Aninhados (Vertical Externo, Horizontal Interno)
// A função é recursiva para repetir o movimento diagonal N vezes.
// Dentro de cada passo, usamos loops aninhados para compor "Cima + Direita".
void moverBispoRecursivo(int casas) {
    if (casas > 0) {
        // Loop Externo: Vertical
        for(int v = 0; v < 1; v++) {
            printf("Cima\n");
            // Loop Interno: Horizontal
            for(int h = 0; h < 1; h++) {
                printf("Direita\n");
            }
        }
        moverBispoRecursivo(casas - 1);
    }
}

int main() {
    // Definindo quantidades de movimento
    int casasTorre = 5;
    int casasBispo = 5;
    int casasRainha = 8;
    int casasCavalo = 1; // O cavalo faz 1 movimento completo em "L"

    // --- 1. Movimentação da TORRE (Recursiva) ---
    printf("***Movimento da Torre (Recursivo)***\n");
    moverTorreRecursivo(casasTorre);
    printf("\n");

    // --- 2. Movimentação do BISPO (Recursivo + Loops Aninhados) ---
    printf("***Movimento do Bispo (Recursivo + Aninhado)***\n");
    moverBispoRecursivo(casasBispo);
    printf("\n");

    // --- 3. Movimentação da RAINHA (Recursiva) ---
    printf("***Movimento da Rainha (Recursivo)***\n");
    moverRainhaRecursivo(casasRainha);
    printf("\n");

    // --- 4. Movimentação do CAVALO (Loops Complexos) ---
    // Desafio: 2 Cima, 1 Direita.
    // Uso de Múltiplas Variáveis, Loops Aninhados, Continue e Break.
    
    printf("***Movimento do Cavalo (Complexo)***\n");

    // Loop externo com múltiplas variáveis (i controla vertical, j controla lógica interna)
    for (int i = 0, j = 0; i < 2; i++, j++) {
        
        printf("Cima\n"); // Imprime o movimento vertical a cada iteração do loop externo

        // Lógica Complexa de Controle de Fluxo:
        // O Cavalo só vira à direita após a segunda casa vertical (quando i é 1).
        
        if (j < 1) { 
            // Se j for 0 (primeira iteração), usamos 'continue' para pular
            // o código abaixo e forçar a próxima iteração do loop imediatamente.
            continue; 
        }

        // Loop aninhado para o movimento horizontal
        int k = 0;
        while (k < 1) {
            printf("Direita\n");
            k++;
            // 'break' para garantir que o loop interno pare (controle explícito)
            break; 
        }
    }

    return 0;
}