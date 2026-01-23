#include <stdio.h>

int main() {
    // Desafio Super Trunfo - Países
    // Aluno: Francisco Araújo de Paiva Junior
    // Nível Mestre: Comparações Múltiplas, Menus Dinâmicos e Operadores Ternários

    // --- VARIÁVEIS CARTA 01 ---
    char pais1[50], codigo1[10], nomeCidade1[50];
    int populacao1, pontosTuristicos1;
    float area1, pib1, densidade1, pibPerCapita1;

    // --- VARIÁVEIS CARTA 02 ---
    char pais2[50], codigo2[10], nomeCidade2[50];
    int populacao2, pontosTuristicos2;
    float area2, pib2, densidade2, pibPerCapita2;

    // Variáveis de Lógica do Jogo
    int escolha1, escolha2;
    float valor1_c1, valor1_c2; // Valores do primeiro atributo escolhido
    float valor2_c1, valor2_c2; // Valores do segundo atributo escolhido
    float soma1, soma2;         // Soma dos dois atributos
    char *nomeAtributo1, *nomeAtributo2; // Para exibir o nome na tela

    // ============================================================
    // LEITURA DE DADOS
    // ============================================================
        
    printf("\n*** Cadastro da Carta 01 ***\n");
    printf("País: "); scanf(" %[^\n]", pais1);
    printf("Código: "); scanf("%s", codigo1);
    printf("Cidade: "); scanf(" %[^\n]", nomeCidade1);
    printf("População: "); scanf("%d", &populacao1);
    printf("Área: "); scanf("%f", &area1);
    printf("PIB: "); scanf("%f", &pib1);
    printf("Pontos Turísticos: "); scanf("%d", &pontosTuristicos1);
    densidade1 = populacao1 / area1;
    pibPerCapita1 = pib1 / populacao1; 

    printf("\n*** Cadastro da Carta 02 ***\n");
    printf("País: "); scanf(" %[^\n]", pais2);
    printf("Código: "); scanf("%s", codigo2);
    printf("Cidade: "); scanf(" %[^\n]", nomeCidade2);
    printf("População: "); scanf("%d", &populacao2);
    printf("Área: "); scanf("%f", &area2);
    printf("PIB: "); scanf("%f", &pib2);
    printf("Pontos Turísticos: "); scanf("%d", &pontosTuristicos2);
    densidade2 = populacao2 / area2;
    pibPerCapita2 = pib2 / populacao2;


    // ======================================================
    // MENU 1 - PRIMEIRO ATRIBUTO
    // ======================================================
    printf("\n=== ESCOLHA O PRIMEIRO ATRIBUTO ===\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Demográfica\n");
    printf("Escolha: ");
    scanf("%d", &escolha1);

    // Lógica para carregar os valores do primeiro atributo
    switch (escolha1) {
        case 1:
            valor1_c1 = (float)populacao1;
            valor1_c2 = (float)populacao2;
            nomeAtributo1 = "População";
            break;
        case 2:
            valor1_c1 = area1;
            valor1_c2 = area2;
            nomeAtributo1 = "Área";
            break;
        case 3:
            valor1_c1 = pib1;
            valor1_c2 = pib2;
            nomeAtributo1 = "PIB";
            break;
        case 4:
            valor1_c1 = (float)pontosTuristicos1;
            valor1_c2 = (float)pontosTuristicos2;
            nomeAtributo1 = "Pontos Turísticos";
            break;
        case 5:
            valor1_c1 = densidade1;
            valor1_c2 = densidade2;
            nomeAtributo1 = "Densidade Demográfica";
            break;
        default:
            printf("Opção inválida! Encerrando.\n");
            return 1;
    }

    // ======================================================
    // MENU 2 - SEGUNDO ATRIBUTO (DINÂMICO)
    // ======================================================
    
    printf("\n*** ESCOLHA O SEGUNDO ATRIBUTO ***\n");
    if (escolha1 != 1) printf("1. População\n");
    if (escolha1 != 2) printf("2. Área\n");
    if (escolha1 != 3) printf("3. PIB\n");
    if (escolha1 != 4) printf("4. Pontos Turísticos\n");
    if (escolha1 != 5) printf("5. Densidade Demográfica\n");
    printf("Escolha: ");
    scanf("%d", &escolha2);

    if (escolha1 == escolha2) {
        printf("Você não pode escolher o mesmo atributo duas vezes!\n");
        return 1;
    }

    // Lógica para carregar os valores do segundo atributo
    switch (escolha2) {
        case 1:
            valor2_c1 = (float)populacao1;
            valor2_c2 = (float)populacao2;
            nomeAtributo2 = "População";
            break;
        case 2:
            valor2_c1 = area1;
            valor2_c2 = area2;
            nomeAtributo2 = "Área";
            break;
        case 3:
            valor2_c1 = pib1;
            valor2_c2 = pib2;
            nomeAtributo2 = "PIB";
            break;
        case 4:
            valor2_c1 = (float)pontosTuristicos1;
            valor2_c2 = (float)pontosTuristicos2;
            nomeAtributo2 = "Pontos Turísticos";
            break;
        case 5:
            valor2_c1 = densidade1;
            valor2_c2 = densidade2;
            nomeAtributo2 = "Densidade Demográfica";
            break;
        default:
            printf("Opção inválida!\n");
            return 1;
    }

    // ======================================================
    // EXIBIÇÃO DOS RESULTADOS E SOMA
    // ======================================================
    
    printf("\n========================================\n");
    printf(" RESULTADO DA COMPARAÇÃO \n");
    printf("========================================\n");
    printf("Carta 1: %s (%s)\n", nomeCidade1, pais1);
    printf("Carta 2: %s (%s)\n", nomeCidade2, pais2);
    printf("----------------------------------------\n");

    // 1. Comparação do Primeiro Atributo
    printf("Atributo 1: %s\n", nomeAtributo1);
    printf("   C1: %.2f | C2: %.2f -> ", valor1_c1, valor1_c2);
    
    // Regra especial para Densidade (menor vence)
    if (escolha1 == 5) {
        if (valor1_c1 < valor1_c2) printf("Vencedor: Carta 1\n");
        else if (valor2_c1 < valor1_c1) printf("Vencedor: Carta 2\n");
        else printf("Empate\n");
    } else {
        // Regra geral (maior vence)
        if (valor1_c1 > valor1_c2) printf("Vencedor: Carta 1\n");
        else if (valor1_c2 > valor1_c1) printf("Vencedor: Carta 2\n");
        else printf("Empate\n");
    }

    // 2. Comparação do Segundo Atributo
    printf("Atributo 2: %s\n", nomeAtributo2);
    printf("   C1: %.2f | C2: %.2f -> ", valor2_c1, valor2_c2);

    if (escolha2 == 5) {
        if (valor2_c1 < valor2_c2) printf("Vencedor: Carta 1\n");
        else if (valor2_c2 < valor2_c1) printf("Vencedor: Carta 2\n");
        else printf("Empate\n");
    } else {
        if (valor2_c1 > valor2_c2) printf("Vencedor: Carta 1\n");
        else if (valor2_c2 > valor2_c1) printf("Vencedor: Carta 2\n");
        else printf("Empate\n");
    }

    // ======================================================
    // SOMA E RESULTADO FINAL 
    // ======================================================
    
    soma1 = valor1_c1 + valor2_c1;
    soma2 = valor1_c2 + valor2_c2;

    printf("----------------------------------------\n");
    printf("SOMA DOS ATRIBUTOS:\n");
    printf("Carta 1: %.2f\n", soma1);
    printf("Carta 2: %.2f\n", soma2);
    
    // Uso do Operador Ternário aninhado para definir o vencedor final
    // (condição) ? verdadeiro : falso
    // Aqui faze: (soma1 > soma2) ? Vence 1 : (soma2 > soma1 ? Vence 2 : Empate)
    
    printf("\n>>> RESULTADO FINAL: %s <<<\n", 
        (soma1 > soma2) ? "VENCEDOR: CARTA 1" : 
        (soma2 > soma1) ? "VENCEDOR: CARTA 2" : "EMPATE!");

    return 0;
}