#include <stdio.h>

int main() {
    // Desafio Super Trunfo - Países
    // Aluno: Francisco Araújo de Paiva Junior
    // Tema 1 - Cadastro das cartas
    // Nível Intermediário: Cálculos de Densidade e PIB per Capita

    // --- VARIÁVEIS CARTA 01 ---
    char estado1;
    char codigo1[20];
    char nomeCidade1[50];
    int populacao1;
    float area1;
    float pib1;
    int pontosTuristicos1;
    float densidade1;      // Nova variável
    float pibPerCapita1;   // Nova variável

    // --- VARIÁVEIS CARTA 02 ---
    char estado2;
    char codigo2[20];
    char nomeCidade2[50];
    int populacao2;
    float area2;
    float pib2;
    int pontosTuristicos2;
    float densidade2;      // Nova variável
    float pibPerCapita2;   // Nova variável

    // --- LEITURA DE DADOS: CARTA 01 ---
    printf("***Cadastro da Carta 01***\n");
    
    printf("Digite o Estado (uma letra de A-H): ");
    scanf(" %c", &estado1); 

    printf("Digite o Código da Carta (ex: A01): ");
    scanf("%s", codigo1);

    printf("Digite o Nome da Cidade: ");
    scanf(" %[^\n]", nomeCidade1); 

    printf("Digite a População: ");
    scanf("%d", &populacao1);

    printf("Digite a Área (em km²): ");
    scanf("%f", &area1);

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &pib1);

    printf("Digite o Número de Pontos Turísticos: ");
    scanf("%d", &pontosTuristicos1);

    // CÁLCULOS CARTA 01
    // Densidade = População dividido pela Área
    densidade1 = (float)populacao1 / area1;
    
    // PIB per Capita = (PIB em bilhões transformado em reais) dividido pela População
    // Multiplicamos por 1 bilhão (1000000000) para converter de bilhões para reais
    pibPerCapita1 = (pib1 * 1000000000.0) / (float)populacao1;

    printf("------------------------------------\n");

    // --- LEITURA DE DADOS: CARTA 02 ---
    printf("***Cadastro da Carta 02***\n");

    printf("Digite o Estado (uma letra de A-H): ");
    scanf(" %c", &estado2);

    printf("Digite o Código da Carta (ex: B02): ");
    scanf("%s", codigo2);

    printf("Digite o Nome da Cidade: ");
    scanf(" %[^\n]", nomeCidade2);

    printf("Digite a População: ");
    scanf("%d", &populacao2);

    printf("Digite a Área (em km²): ");
    scanf("%f", &area2);

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &pib2);

    printf("Digite o Número de Pontos Turísticos: ");
    scanf("%d", &pontosTuristicos2);

    // CÁLCULOS CARTA 02
    densidade2 = (float)populacao2 / area2;
    pibPerCapita2 = (pib2 * 1000000000.0) / (float)populacao2;
    
    // --- EXIBIÇÃO DOS DADOS ---
    printf("\n====================================\n");
    printf("EXIBIÇÃO DOS DADOS CADASTRADOS\n");
    printf("====================================\n");
    
    // Exibição Carta 01
    printf("Carta 1:\n");
    printf("Estado: %c\n", estado1);
    printf("Código: %s\n", codigo1);
    printf("Nome da Cidade: %s\n", nomeCidade1);
    printf("População: %d\n", populacao1);
    printf("Área: %.2f km²\n", area1);
    printf("PIB: %.2f bilhões de reais\n", pib1);
    printf("Número de Pontos Turísticos: %d\n", pontosTuristicos1);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade1);
    printf("PIB per Capita: %.2f reais\n", pibPerCapita1);
    
    printf("\n"); 

    // Exibição Carta 02
    printf("Carta 2:\n");
    printf("Estado: %c\n", estado2);
    printf("Código: %s\n", codigo2);
    printf("Nome da Cidade: %s\n", nomeCidade2);
    printf("População: %d\n", populacao2);
    printf("Área: %.2f km²\n", area2);
    printf("PIB: %.2f bilhões de reais\n", pib2);
    printf("Número de Pontos Turísticos: %d\n", pontosTuristicos2);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade2);
    printf("PIB per Capita: %.2f reais\n", pibPerCapita2);
     
    return 0;
}