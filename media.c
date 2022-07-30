#include <stdio.h>

float min(float x, float y) {
    return x <= y ? x : y;
}

int main() {
    float P1, P2;
    float T1, T2, T3;

    scanf("%f %f", &P1, &P2);
    scanf("%f %f %f", &T1, &T2, &T3);

    float MP = (P1 + P2) / 2;
    float MT = (T1 + T2 + T3) / 3;
    float media;

    if (MP >= 5.0 && MT >= 5.0) {
        media = .7 * MP + .3 * MT;
    } else {
        media = min(MP, MT);
    }

    printf("\n%.2f\n", media);

    return 0;
}
