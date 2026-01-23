#include <stdio.h>

int main() {
    // Desafio Super Trunfo - Países
    // Aluno: Francisco Araújo de Paiva Junior
    // Nível Mestre: Lógica de Jogo e Super Poder

    // --- VARIÁVEIS CARTA 01 ---
    char estado1;
    char codigo1[20];
    char nomeCidade1[50];
    unsigned long int populacao1; // Alterado para unsigned long int
    float area1;
    float pib1;
    int pontosTuristicos1;
    float densidade1;
    float pibPerCapita1;
    float superPoder1;            // Nova variável

    // --- VARIÁVEIS CARTA 02 ---
    char estado2;
    char codigo2[20];
    char nomeCidade2[50];
    unsigned long int populacao2; // Alterado para unsigned long int
    float area2;
    float pib2;
    int pontosTuristicos2;
    float densidade2;
    float pibPerCapita2;
    float superPoder2;            // Nova variável

    // ============================================================
    // LEITURA DE DADOS: CARTA 01
    // ============================================================
    printf("\n*** Cadastro da Carta 01 ***\n");
    
    printf("Digite o Estado (uma letra de A-H): ");
    scanf(" %c", &estado1); 

    printf("Digite o Código da Carta (ex: A01): ");
    scanf("%s", codigo1);

    printf("Digite o Nome da Cidade: ");
    scanf(" %[^\n]", nomeCidade1); 

    printf("Digite a População: ");
    scanf("%lu", &populacao1); // Alterado para %lu

    printf("Digite a Área (em km²): ");
    scanf("%f", &area1);

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &pib1);

    printf("Digite o Número de Pontos Turísticos: ");
    scanf("%d", &pontosTuristicos1);

    // --- CÁLCULOS CARTA 01 ---
    densidade1 = (float)populacao1 / area1;
    pibPerCapita1 = (pib1 * 1000000000.0f) / (float)populacao1;
    
    // Super Poder: Soma de tudo (com inverso da densidade)
    superPoder1 = (float)populacao1 + area1 + pib1 + (float)pontosTuristicos1 + pibPerCapita1 + (1.0f / densidade1);

    printf("------------------------------------\n");

    // ============================================================
    // LEITURA DE DADOS: CARTA 02
    // ============================================================
    printf("\n*** Cadastro da Carta 02 ***\n");

    printf("Digite o Estado (uma letra de A-H): ");
    scanf(" %c", &estado2);

    printf("Digite o Código da Carta (ex: B02): ");
    scanf("%s", codigo2);

    printf("Digite o Nome da Cidade: ");
    scanf(" %[^\n]", nomeCidade2);

    printf("Digite a População: ");
    scanf("%lu", &populacao2); // Alterado para %lu

    printf("Digite a Área (em km²): ");
    scanf("%f", &area2);

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &pib2);

    printf("Digite o Número de Pontos Turísticos: ");
    scanf("%d", &pontosTuristicos2);

    // --- CÁLCULOS CARTA 02 ---
    densidade2 = (float)populacao2 / area2;
    pibPerCapita2 = (pib2 * 1000000000.0f) / (float)populacao2;
    
    superPoder2 = (float)populacao2 + area2 + pib2 + (float)pontosTuristicos2 + pibPerCapita2 + (1.0f / densidade2);

    // ============================================================
    // EXIBIÇÃO DOS DADOS
    // ============================================================
    printf("\n====================================\n");
    printf("RELATÓRIO DE ATRIBUTOS\n");
    printf("====================================\n");
    
    // Exibição Carta 01
    printf("Carta 1 (%s) - Super Poder: %.2f\n", nomeCidade1, superPoder1);
    // Exibição Carta 02
    printf("Carta 2 (%s) - Super Poder: %.2f\n", nomeCidade2, superPoder2);
    
    printf("\n====================================\n");
    printf("COMPARAÇÃO DE CARTAS\n");
    printf("Resultado 1 = Carta 1 Venceu | Resultado 0 = Carta 2 Venceu\n");
    printf("====================================\n");

    // LÓGICA DE COMPARAÇÃO (Operadores Relacionais)
    
    // População (Maior vence)
    printf("População: Carta 1 venceu (%d)\n", populacao1 > populacao2);

    // Área (Maior vence)
    printf("Área: Carta 1 venceu (%d)\n", area1 > area2);

    // PIB (Maior vence)
    printf("PIB: Carta 1 venceu (%d)\n", pib1 > pib2);

    // Pontos Turísticos (Maior vence)
    printf("Pontos Turísticos: Carta 1 venceu (%d)\n", pontosTuristicos1 > pontosTuristicos2);

    // Densidade Populacional (MENOR vence - Lógica Invertida)
    // Se densidade1 for MENOR que densidade2, retorna 1 (Vitória da Carta 1)
    printf("Densidade Populacional: Carta 1 venceu (%d)\n", densidade1 < densidade2);

    // PIB per Capita (Maior vence)
    printf("PIB per Capita: Carta 1 venceu (%d)\n", pibPerCapita1 > pibPerCapita2);

    // Super Poder (Maior vence)
    printf("Super Poder: Carta 1 venceu (%d)\n", superPoder1 > superPoder2);

    return 0;
}