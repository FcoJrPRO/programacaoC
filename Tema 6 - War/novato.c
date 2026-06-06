#include <stdio.h>
#include <string.h>

// Desafio War: 
//Implementando uso de structs
// Aluno: Francisco Araújo de Paiva Junior
// Tema 1 - Estruturas de Dados: Conceitos e Representação 2º Semestre 2026
// Nível: Novato

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Declaração do vetor de structs para armazenar os 5 territórios.
    Territorio mundo[5];
    int i;

    // Interface inicial
    printf("=======================================\n\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n\n");

    
     // Cadastro dos territórios:
     
    for (i = 0; i < 5; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        
        // Entrada do Nome do Territorio
        printf("Nome do Territorio: ");
        scanf(" %[^\n]", mundo[i].nome); 
        
        // Entrada da Cor do Exército
        printf("Cor do Exercito: ");
        scanf(" %s", mundo[i].cor);
        
        // Entrada do Número de Tropas
        printf("Numero de Tropas: ");
        scanf("%d", &mundo[i].tropas);
        
        printf("\n"); // Linha em branco para melhor visualização no terminal
    }

    
     // Exibição dos dados:
     
    printf("Cadastro inicial concluido com sucesso!\n\n");
    printf("=======================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL     \n");
    printf("=======================================\n\n");

    for (i = 0; i < 5; i++) {
        printf("TERRITORIO %d:\n", i + 1);
        printf("  - Nome: %s\n", mundo[i].nome);
        printf("  - Dominado por: Exercito %s\n", mundo[i].cor);
        printf("  - Tropas: %d\n", mundo[i].tropas);
        printf("\n"); // Pula uma linha entre um território e outro
    }

    return 0;
}