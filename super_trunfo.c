#include <stdio.h>

int main() {
    // Variáveis para a Carta 1
    char estado1;
    char codigo1[03];
    char nomeCidade1[50];
    int populacao1;
    float area1;
    float pib1;
    int pontosTuristicos1;

    //Cadastro da Carta 1
    printf("Digite os dados da Carta 1:\n");
    printf("Estado: (A-H): \n");
    scanf("%c", &estado1);
    printf("Código da Carta (ex: A01): \n");
    scanf("%s", codigo1);
    printf("Nome da Cidade: \n");
    scanf("%s", nomeCidade1);
    printf("População: \n");
    scanf("%d", &populacao1);
    printf("Área (em km²): \n");
    scanf("%f", &area1);
    printf("PIB: \n");
    scanf("%f", &pib1);
    printf("Número de Pontos Turísticos: \n");
    scanf("%d", &pontosTuristicos1);

    // Variáveis para a Carta 2
    char estado2;
    char codigo2[03];
    char nomeCidade2[50];
    int populacao2;
    float area2;
    float pib2;
    int pontosTuristicos2;

    //Cadastro da Carta 2
    printf("Digite os dados da Carta 2:\n");
    printf("Estado (A-H): \n");
    scanf("%c", &estado2);
    printf("Código da Carta (ex: B03): \n");
    scanf("%s", codigo2);
    printf("Nome da Cidade: \n");
    scanf("%s", nomeCidade2);
    printf("População: \n");
    scanf("%d", &populacao2);
    printf("Área (em km²): \n");
    scanf("%f", &area2);
    printf("PIB: \n");
    scanf("%f", &pib2);
    printf("Número de Pontos Turísticos: \n");
    scanf("%d", &pontosTuristicos2);

    return 0;
}
