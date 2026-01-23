#include <stdio.h>

int main() {
    // Desafio Super Trunfo - Países
    // Aluno: Francisco Araújo de Paiva Junior
    // Nível Aventureiro: Adicionando Interatividade e Lógica Complexa

    // --- VARIÁVEIS CARTA 01 ---
    char pais1[50];       // Alterado de estado1 para pais1
    char codigo1[10];
    char nomeCidade1[50];
    int populacao1;
    float area1;
    float pib1;
    int pontosTuristicos1;
    float densidade1;
    float pibPerCapita1;

    // --- VARIÁVEIS CARTA 02 ---
    char pais2[50];       // Alterado de estado2 para pais2
    char codigo2[10];
    char nomeCidade2[50];
    int populacao2;
    float area2;
    float pib2;
    int pontosTuristicos2;
    float densidade2;
    float pibPerCapita2;

    // Variável para o menu
    int opcao;

    // ============================================================
    // LEITURA DE DADOS: CARTA 01
    // ============================================================
    printf("\n*** Cadastro da Carta 01 ***\n");
    
    printf("País: ");
    scanf(" %[^\n]", pais1); // Lê o nome do país (aceita espaços)
    
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
    // LEITURA DE DADOS: CARTA 02
    // =====================================================
    printf("\n*** Cadastro da Carta 02 ***\n");
    
    printf("País: ");
    scanf(" %[^\n]", pais2); // Lê o nome do país (aceita espaços)
    
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

    // ======================================================
    // MENU INTERATIVO // Nivel Intermediario - Implementação
    // ======================================================
    printf("\n========================================\n");
    printf(" ESCOLHA O ATRIBUTO PARA COMPARAÇÃO \n");
    printf("========================================\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Número de Pontos Turísticos\n");
    printf("5. Densidade Demográfica\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    printf("========================================\n");

    // =====================================================
    // LÓGICA DE COMPARAÇÃO COM SWITCH E IF/ELSE
    // =====================================================

    switch (opcao) {
     case 1: // População
    printf("Atributo escolhido: População\n");
    printf("País: %s - Cidade: %s (%d)\n", pais1, nomeCidade1, populacao1);
    printf("País: %s - Cidade: %s (%d)\n", pais2, nomeCidade2, populacao2);
            
    if (populacao1 > populacao2) {
     printf("\n>>> VENCEDOR: Carta 1 (%s - %s) venceu! <<<\n", nomeCidade1, pais1);
     } else if (populacao2 > populacao1) {
    printf("\n>>> VENCEDOR: Carta 2 (%s - %s) venceu! <<<\n", nomeCidade2, pais2);
    } else {
    printf("\n>>> RESULTADO: Empate! <<<\n");
    }
    break;

    case 2: // Área
    printf("Atributo escolhido: Área\n");
    printf("%s (%s): %.2f km²\n", nomeCidade1, pais1, area1);
    printf("%s (%s): %.2f km²\n", nomeCidade2, pais2, area2);
            
    if (area1 > area2) {
    printf("\n>>> VENCEDOR: Carta 1 (%s) venceu! <<<\n", nomeCidade1);
    } else if (area2 > area1) {
    printf("\n>>> VENCEDOR: Carta 2 (%s) venceu! <<<\n", nomeCidade2);
    } else {
    printf("\n>>> RESULTADO: Empate! <<<\n");
    }
    break;

    case 3: // PIB
    printf("Atributo escolhido: PIB\n");
    printf("%s (%s): %.2f\n", nomeCidade1, pais1, pib1);
    printf("%s (%s): %.2f\n", nomeCidade2, pais2, pib2);
            
    if (pib1 > pib2) {
    printf("\n>>> VENCEDOR: Carta 1 (%s) venceu! <<<\n", nomeCidade1);
    } else if (pib2 > pib1) {
    printf("\n>>> VENCEDOR: Carta 2 (%s) venceu! <<<\n", nomeCidade2);
    } else {
    printf("\n>>> RESULTADO: Empate! <<<\n");
    }
    break;

    case 4: // Pontos Turísticos
    printf("Atributo escolhido: Pontos Turísticos\n");
    printf("%s (%s): %d\n", nomeCidade1, pais1, pontosTuristicos1);
    printf("%s (%s): %d\n", nomeCidade2, pais2, pontosTuristicos2);
            
    if (pontosTuristicos1 > pontosTuristicos2) {
    printf("\n>>> VENCEDOR: Carta 1 (%s) venceu! <<<\n", nomeCidade1);
    } else if (pontosTuristicos2 > pontosTuristicos1) {
    printf("\n>>> VENCEDOR: Carta 2 (%s) venceu! <<<\n", nomeCidade2);
    } else {
    printf("\n>>> RESULTADO: Empate! <<<\n");
    }
    break;

    case 5: // Densidade Demográfica (REGRA INVERTIDA: MENOR VENCE)
    printf("Atributo escolhido: Densidade Demográfica\n");
    printf("%s (%s): %.2f\n", nomeCidade1, pais1, densidade1);
    printf("%s (%s): %.2f\n", nomeCidade2, pais2, densidade2);
            
    if (densidade1 < densidade2) {
    printf("\n>>> VENCEDOR: Carta 1 (%s) venceu! (Menor densidade) <<<\n", nomeCidade1);
    } else if (densidade2 < densidade1) {
    printf("\n>>> VENCEDOR: Carta 2 (%s) venceu! (Menor densidade) <<<\n", nomeCidade2);
    } else {
    printf("\n>>> RESULTADO: Empate! <<<\n");
    }
    break;

    default:
    printf("Opção Inválida! Reinicie o jogo e escolha entre 1 e 5.\n");
    break;
    }
    
    return 0;
}