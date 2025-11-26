#include <stdio.h>

#define TAM_TABULEIRO 10   // Tamanho do tabuleiro: 10x10
#define TAM_NAVIO 3        // Tamanho fixo dos navios: 3 posições

// Função que inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    int linha, coluna;
    for (linha = 0; linha < TAM_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = 0; // 0 representa água
        }
    }
}

// Função que verifica se é possível posicionar o navio
// orientacao = 0 → horizontal
// orientacao = 1 → vertical
int podePosicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                        int linhaInicial,
                        int colunaInicial,
                        int orientacao) {
    int i;

    // Verifica se está dentro dos limites do tabuleiro
    if (orientacao == 0) { // horizontal
        if (colunaInicial < 0 || colunaInicial + TAM_NAVIO > TAM_TABULEIRO) {
            return 0; // inválido
        }
        if (linhaInicial < 0 || linhaInicial >= TAM_TABULEIRO) {
            return 0; // linha inválida
        }
    } else { // vertical
        if (linhaInicial < 0 || linhaInicial + TAM_NAVIO > TAM_TABULEIRO) {
            return 0; // inválido
        }
        if (colunaInicial < 0 || colunaInicial >= TAM_TABULEIRO) {
            return 0; // coluna inválida
        }
    }

    // Verifica se já existe navio nas posições (evita sobreposição)
    for (i = 0; i < TAM_NAVIO; i++) {
        if (orientacao == 0) { // horizontal
            if (tabuleiro[linhaInicial][colunaInicial + i] != 0) {
                return 0; // já tem algo aqui, não pode
            }
        } else { // vertical
            if (tabuleiro[linhaInicial + i][colunaInicial] != 0) {
                return 0; // já tem algo aqui, não pode
            }
        }
    }

    return 1; // pode posicionar
}

// Função que posiciona o navio no tabuleiro usando o vetor do navio
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                     int linhaInicial,
                     int colunaInicial,
                     int orientacao,
                     int navio[TAM_NAVIO]) {
    int i;
    for (i = 0; i < TAM_NAVIO; i++) {
        if (orientacao == 0) { // horizontal
            tabuleiro[linhaInicial][colunaInicial + i] = navio[i];
        } else { // vertical
            tabuleiro[linhaInicial + i][colunaInicial] = navio[i];
        }
    }
}

// Função para exibir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    int linha, coluna;

    printf("Tabuleiro (0 = agua, 3 = navio):\n\n");

    // Cabeçalho de colunas (opcional)
    printf("   ");
    for (coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
        printf("%2d ", coluna);
    }
    printf("\n");

    for (linha = 0; linha < TAM_TABULEIRO; linha++) {
        printf("%2d ", linha); // número da linha
        for (coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            printf("%2d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Declaração dos navios como vetores (tamanho 3)
    int navioHorizontal[TAM_NAVIO] = {3, 3, 3};
    int navioVertical[TAM_NAVIO]   = {3, 3, 3};

    // Coordenadas iniciais definidas diretamente no código (0 a 9)
    int linhaInicioHorizontal = 2;
    int colunaInicioHorizontal = 1;

    int linhaInicioVertical = 5;
    int colunaInicioVertical = 7;

    // 1) Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // 2) Valida e posiciona o navio horizontal
    if (!podePosicionarNavio(tabuleiro,
                             linhaInicioHorizontal,
                             colunaInicioHorizontal,
                             0)) { // 0 = horizontal
        printf("Erro: nao foi possivel posicionar o navio horizontal.\n");
        return 1;
    }
    posicionarNavio(tabuleiro,
                    linhaInicioHorizontal,
                    colunaInicioHorizontal,
                    0,
                    navioHorizontal);

    // 3) Valida e posiciona o navio vertical
    if (!podePosicionarNavio(tabuleiro,
                             linhaInicioVertical,
                             colunaInicioVertical,
                             1)) { // 1 = vertical
        printf("Erro: nao foi possivel posicionar o navio vertical.\n");
        return 1;
    }
    posicionarNavio(tabuleiro,
                    linhaInicioVertical,
                    colunaInicioVertical,
                    1,
                    navioVertical);

    // 4) Exibe o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
