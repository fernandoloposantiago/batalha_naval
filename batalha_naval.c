#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

int podePosicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < 3; i++) {
        int l = linha, c = coluna;
        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'd') { l += i; c -= i; }

        if (l >= TAM || c >= TAM || c < 0 || tabuleiro[l][c] != AGUA)
            return 0;
    }
    return 1;
}

void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < 3; i++) {
        if (direcao == 'H') tabuleiro[linha][coluna + i] = NAVIO;
        else if (direcao == 'V') tabuleiro[linha + i][coluna] = NAVIO;
        else if (direcao == 'D') tabuleiro[linha + i][coluna + i] = NAVIO;
        else if (direcao == 'd') tabuleiro[linha + i][coluna - i] = NAVIO;
    }
}

void gerarCone(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

void gerarCruz(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

void gerarOctaedro(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origem_linha, int origem_coluna) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int l = origem_linha - offset + i;
            int c = origem_coluna - offset + j;
            if (l >= 0 && l < TAM && c >= 0 && c < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[l][c] == AGUA)
                    tabuleiro[l][c] = HABILIDADE;
            }
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: 0 = água, 3 = navio, 5 = habilidade\n");
}

int main() {
    int tabuleiro[TAM][TAM];
    int habilidade[TAM_HAB][TAM_HAB];

    inicializarTabuleiro(tabuleiro);

    // Coordenadas fixas para os 4 navios
    int navios[4][3] = {
        {0, 0, 'H'},
        {2, 5, 'V'},
        {4, 4, 'D'},
        {0, 9, 'd'}
    };

    for (int i = 0; i < 4; i++) {
        int l = navios[i][0];
        int c = navios[i][1];
        char d = (char)navios[i][2];
        if (podePosicionarNavio(tabuleiro, l, c, d))
            posicionarNavio(tabuleiro, l, c, d);
    }

    // Cone
    gerarCone(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 6, 2);

    // Cruz
    gerarCruz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 4, 7);

    // Octaedro
    gerarOctaedro(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 8, 8);

    exibirTabuleiro(tabuleiro);

    return 0;
}
