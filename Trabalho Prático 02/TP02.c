/**
 * Nome: Matheus Goulart Ranzani
 * Curso: Ciência da Computação
 * RA: 800278
 */

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

unsigned long long intercala_contando_inversoes(int vetor[], int p, int q, int r) {
    int i, j, k, tamanho;

    i = p;
    j = q;
    k = 0;
    tamanho = r - p;

    unsigned long long numero_inversoes = 0;

    int* w = malloc(tamanho * sizeof(int));

    while (i < q && j < r) {
        if (vetor[i] <= vetor[j]) {
            w[k++] = vetor[i++];
        } else {
            w[k++] = vetor[j++];
            numero_inversoes += q - i;
        }
    }

    while (i < q) w[k++] = vetor[i++];
    while (j < r) w[k++] = vetor[j++];

    for (k = 0; k < tamanho; k++) {
        vetor[p + k] = w[k];
    }

    free(w);

    return numero_inversoes;
}

unsigned long long conta_inversoes(int vetor[], int p, int r) {
    unsigned long long numero_inversoes = 0;

    if (r - p > 1) {
        int m = (p + r) / 2;
        numero_inversoes += conta_inversoes(vetor, p, m);
        numero_inversoes += conta_inversoes(vetor, m, r);
        numero_inversoes += intercala_contando_inversoes(vetor, p, m, r);
    }

    return numero_inversoes;
}

void imprime(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");
}

int main(int argc, char* argv[]) {
    char nome_arquivo[TAMANHO];
    FILE* arquivo_entrada;
    unsigned long long numero_inversoes = 0;

    if (argc != 1) {
        // printf("Há muitos parâmetros sendo passados! Passe apenas o nome do executável\n");
        return 0;
    }

    scanf("%s", nome_arquivo);
    arquivo_entrada = fopen(nome_arquivo, "r");

    if (arquivo_entrada == NULL) {
        // printf("Não foi possível encontrar o arquivo solicitado. Entre com o nome da instância\n");
        exit(EXIT_FAILURE);
    }

    int N;
    int* genes;
    fscanf(arquivo_entrada, "%d", &N); // Primeira linha do arquivo .in
    genes = (int*)malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++) {
        fscanf(arquivo_entrada, "%d", &genes[i]); // Sequência de genes (genoma do indivíduo 2)
    }

    // imprime(genes, N);
    numero_inversoes = conta_inversoes(genes, 0, N);
    printf("%llu\n", numero_inversoes);

    fclose(arquivo_entrada);

    return 0;
}
