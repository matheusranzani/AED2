#include <stdio.h>
#include <stdlib.h>

unsigned long long intercala_contando_inversoes(int v[], int p, int q, int r) {
    int i, j, k, tam;
    i = p;
    j = q;
    k = 0;
    tam = r - p;
    unsigned long long num_inv = 0;

    int* w = malloc(tam * sizeof(int));

    while (i < q && j < r) {
        if (v[i] <= v[j]) {
            w[k++] = v[i++];
        } else {
            w[k++] = v[j++];
            num_inv += q - i;
        }
    }

    while (i < q) w[k++] = v[i++];
    while (j < r) w[k++] = v[j++];

    for (k = 0; k < tam; k++) {
        v[p + k] = w[k];
    }

    free(w);
    return num_inv;
}

unsigned long long conta_inversoes(int v[], int p, int r) {
    int m;
    unsigned long long num_inv = 0;

    if (r - p > 1) {
        m = (p + r) / 2;
        num_inv += conta_inversoes(v, p, m);
        num_inv += conta_inversoes(v, m, r);
        num_inv += intercala_contando_inversoes(v, p, m, r);
    }

    return num_inv;
}

int main() {
    int N;
    scanf("%d", &N);

    int vetor[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &vetor[i]);
    }

    unsigned long long num_inv = conta_inversoes(vetor, 0, N);

    printf("%llu\n", num_inv);

    return 0;
}
