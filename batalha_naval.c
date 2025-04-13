#include <stdio.h>

#define TAM 10
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

// Inicializa todas as posições do tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = VALOR_AGUA;
}

// Posiciona os navios ao longo da diagonal principal (\)
void posicionarDiagonalPrincipal(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        tabuleiro[i][i] = VALOR_NAVIO; // Linha e coluna são iguais
    }
}

// Posiciona os navios ao longo da diagonal secundária (/)
void posicionarDiagonalSecundaria(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        tabuleiro[i][TAM - 1 - i] = VALOR_NAVIO; // Coluna é TAM - 1 - linha
    }
}

// Exibe o tabuleiro no console com espaçamento e rótulos
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro Batalha Naval:\n\n");

    // Exibe as letras das colunas
    printf("   ");
    for (int j = 0; j < TAM; j++) {
        printf(" %c ", 'A' + j); // Letras de A a J
    }
    printf("\n");

    // Exibe o tabuleiro com os números das linhas
    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i + 1); // Números de 1 a 10
        for (int j = 0; j < TAM; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = água, 3 = navio\n");
}

int main() {
    int tabuleiro[TAM][TAM];

    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios nas diagonais
    posicionarDiagonalPrincipal(tabuleiro);
    posicionarDiagonalSecundaria(tabuleiro);

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}