/**
 * Nome: Matheus Goulart Ranzani
 * Curso: Ciência da Computação
 * RA: 800278
 */

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10 // Tamanho do nome do arquivo de entrada

// Realiza a intercalação dos subvetores e devolve o número de inversões
unsigned long long intercala_contando_inversoes(int vetor[], int p, int q, int r) {
    int i, j, k, tamanho;

    i = p; // Começo do primeiro subvetor
    j = q; // Começo do segundo subvetor
    k = 0; // Índice do vetor w
    tamanho = r - p; // Tamanho do vetor completo

    unsigned long long numero_inversoes = 0;

    int* w = malloc(tamanho * sizeof(int)); // Vetor auxiliar

    // Realiza o laço até que algum índice chegue ao fim
    while (i < q && j < r) {
        if (vetor[i] <= vetor[j]) {
            w[k++] = vetor[i++]; // Intercala
        } else {
            // Intercala e conta as inversões
            w[k++] = vetor[j++];
            numero_inversoes += q - i;
        }
    }

    // Caso algum índice não tenha chego ao fim, completa de inserir no vetor w
    while (i < q) w[k++] = vetor[i++];
    while (j < r) w[k++] = vetor[j++];

    // Cópia do vetor auxiliar para o vetor original
    for (k = 0; k < tamanho; k++) {
        vetor[p + k] = w[k];
    }

    free(w); // Libera o vetor auxiliar

    return numero_inversoes;
}

// Determina o total de inversões no vetor passado como parâmetro
unsigned long long conta_inversoes(int vetor[], int p, int r) {
    unsigned long long numero_inversoes = 0;

    if (r - p > 1) { // Caso o vetor tiver tamanho maior que 1
        int m = (p + r) / 2; // m indica o meio do vetor

        // Calcula o número de inversões nos dois subvetores do vetor
        numero_inversoes += conta_inversoes(vetor, p, m);
        numero_inversoes += conta_inversoes(vetor, m, r);
        numero_inversoes += intercala_contando_inversoes(vetor, p, m, r);
    }

    return numero_inversoes;
}

int main(int argc, char* argv[]) {
    char nome_arquivo[TAMANHO];
    FILE* arquivo_entrada;
    unsigned long long numero_inversoes = 0;

    // Verifica se apenas o nome do executável foi inserido na compilação
    if (argc != 1) {
        return 0;
    }

    // Leitiura do nome do arquivo da instância
    scanf("%s", nome_arquivo);
    arquivo_entrada = fopen(nome_arquivo, "r");

    // Verificação se a abertura do arquivo deu certo
    if (arquivo_entrada == NULL) {
        exit(EXIT_FAILURE);
    }

    int N; // Quantidade de genes dos indivíduos comparados
    int* genes; // Vetor de genes do indivíduo 2

    fscanf(arquivo_entrada, "%d", &N); // Primeira linha do arquivo .in
    genes = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        fscanf(arquivo_entrada, "%d", &genes[i]); // Segunda linha do arquivo .in
    }

    // Cálculo e impressão do menor número de inversões
    numero_inversoes = conta_inversoes(genes, 0, N);
    printf("%llu\n", numero_inversoes);

    fclose(arquivo_entrada); // Fechamento do arquivo de instância

    return 0;
}
