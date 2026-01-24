#include <stdio.h>

int main() {
    // Desafio Super Trunfo - Países
    // Aluno: Francisco Araújo de Paiva Junior
    // Nível Novato: Desenvolvendo a Lógica do Jogo

    // Cadastro das Cartas:

    // --- VARIÁVEIS CARTA 01 ---
    char estado1[3];
    char codigo1[10];
    char nomeCidade1[50];
    int populacao1;
    float area1;
    float pib1;
    int pontosTuristicos1;
    float densidade1;
    float pibPerCapita1;
    // float superPoder1;   // variavél ocultada
    // PibPerCapra usar formato Bilhão um numero seguido de nove zeros ex: 1000000000

   // --- VARIÁVEIS CARTA 01 ---
    char estado2[3];
    char codigo2[10];
    char nomeCidade2[50];
    int populacao2;
    float area2;
    float pib2;
    int pontosTuristicos2;
    float densidade2;
    float pibPerCapita2;
    // PibPerCapra usar formato Bilhão um numero seguido de nove zeros ex: 1000000000
   
    //// float superPoder2;   // variavél ocultada

    // ============================================================
    // LEITURA DE DADOS: CARTA 01
    // ============================================================
    // Implementando a lógica para solicitar ao usuário que insira os dados das cidades
    printf("\n*** Cadastro da Carta 01 ***\n");

    printf("Estado (ex: SP): ");
    scanf("%s", estado1);

    printf("Código da Cidade (ex: A01): ");
    scanf("%s", codigo1);

    printf("Nome da Cidade: ");
    scanf(" %[^\n]", nomeCidade1);

    printf("Digite a População: ");
    scanf("%d", &populacao1);

    printf("Área (em km²): ");
    scanf("%f", &area1);

    printf("PIB (em bilhões): ");
    scanf("%f", &pib1);

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontosTuristicos1);

    // Cálculos da Carta 1
    densidade1 = populacao1 / area1;
    pibPerCapita1 = pib1 / populacao1;

    // =====================================================
    // CADASTRO DA CARTA 2
    // =====================================================
    printf("\nCadastro da Carta 2\n");
    
    printf("Estado (ex: RJ): ");
    scanf("%s", estado2);

    printf("Código da Cidade (ex: B02): ");
    scanf("%s", codigo2);

    printf("Nome da Cidade: ");
    scanf(" %[^\n]", nomeCidade2);

    printf("População: ");
    scanf("%d", &populacao2);

    printf("Área (em km²): ");
    scanf("%f", &area2);

    printf("PIB (em bilhões): ");
    scanf("%f", &pib2);

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontosTuristicos2);

    // Cálculos da Carta 2
    densidade2 = populacao2 / area2;
    pibPerCapita2 = pib2 / populacao2;

    // =====================================================
    // EXIBIÇÃO DOS DADOS CALCULADOS
    // =====================================================
    printf("\n--- Dados Calculados ---\n");

    printf("Carta 1 - %s (%s)\n", nomeCidade1, estado1);
    printf("Densidade Populacional: %.2f\n", densidade1);
    printf("PIB per capita: %.6f\n\n", pibPerCapita1);

    printf("Carta 2 - %s (%s)\n", nomeCidade2, estado2);
    printf("Densidade Populacional: %.2f\n", densidade2);
    printf("PIB per capita: %.6f\n\n", pibPerCapita2);

    // =====================================================
    // COMPARAÇÃO DAS CARTAS
    // ATRIBUTO ESCOLHIDO: PIB PER CAPITA
    // REGRA: MAIOR VALOR VENCE
    // =====================================================
    printf("Comparacao de cartas (Atributo: PIB per capita)\n\n");



    printf("Carta 1:\n");
    printf("Nome: %s\n", nomeCidade1);
    printf("Estado: %s\n", estado1);
    printf("PIB per capita: R$ %.2f\n\n", (pibPerCapita1 * 1000000.0));

    printf("Carta 2:\n");
    printf("Nome: %s\n", nomeCidade2);
    printf("Estado: %s\n", estado2);
    printf("PIB per capita: R$ %.2f\n\n", (pibPerCapita1 * 1000000.0));

    if (pibPerCapita1 > pibPerCapita2) {
        printf("Carta 1 (%s) venceu!\n", nomeCidade1);
        
    }
    else if (pibPerCapita2 > pibPerCapita1) {
        printf("Carta 2 (%s) venceu!\n", nomeCidade2);
    }
    else {
        printf("Resultado: Empate!\n");
    }

    return 0;
}