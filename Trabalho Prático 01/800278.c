/**
 * Nome: Matheus Goulart Ranzani
 * Curso: Ciência da Computação
 * RA: 800278
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcmp(), strcpy(), strtok(), strlen() e strcat()

// Estrutura das palavras escolhidas pelos professores
typedef struct palavra {
    char conteudo[50];
    int pontuacao;
} Palavra;

// Estrutura dos nós das listas ligadas da Tabela Hash
typedef struct no No;
struct no {
    char chave[50]; // Conteúdo
    int valor; // Pontuação
    No* proximo;
};

// Variáveis globais da Tabela
No** tabela = NULL;
int tamanho_tabela;

// Inicia a Tabela com as listas apontando para NULL
void inicia_tabela(int maximo) {
    tamanho_tabela = maximo;

    tabela = (No**)malloc(sizeof(No*) * tamanho_tabela);
    for (int i = 0; i < tamanho_tabela; i++) {
        tabela[i] = NULL;
    }
}

// Determina o hash das palavras escolhidas
int hash(char* chave) {
    int i, h = 0;
    int primo = 127;

    for (i = 0; chave[i] != '\0'; i++) {
        h = (h * primo + chave[i]) % tamanho_tabela;
    }

    return h;
}

// Realiza a busca da palavra na Tabela
int busca(char* chave) {
    No* p;
    int h = hash(chave);
    p = tabela[h];

    while (p != NULL && strcmp(p->chave, chave)) {
        p = p->proximo;
    }

    // Se a palavra for uma escolhida pelos professores retorna sua pontuação
    if (p != NULL) {
        return p->valor;
    }

    // Retorna -10 caso a palavra não seja uma das escolhidas
    return -10;
}

// Insere as palavras escolhidas na Tabela
void insere(char* chave, int valor) {
    No* p;
    int h = hash(chave);
    p = tabela[h];

    // Percorre a lista para o tratamento de colisões
    while (p != NULL && strcmp(p->chave, chave)) {
        p = p->proximo;
    }

    // Insere o nó no começo da lista
    if (p == NULL) {
        p = (No*)malloc(sizeof(No));
        strcpy(p->chave, chave);
        p->proximo = tabela[h];
        tabela[h] = p;
    }

    p->valor = valor;
}

// Calcula a pontução do texto de um aluno
int calcula_pontuacao(char* texto) {
    int pontuacao = 0;

    // Uso da função strtok para analisar individualmente cada palavra do texto
    char* palavra = strtok(texto, " "); // Separa as palavras através do espaço

    while (palavra != NULL) {
        pontuacao += busca(palavra);
        palavra = strtok(NULL, " ");
    }

    return pontuacao;
}

int main() {
    int N, M;

    // Entrada do número de palavras escolhidas e de textos dos alunos
    scanf("%d %d", &N, &M);

    Palavra palavras_escolhidas[N];
    char** texto_alunos = (char**)malloc(sizeof(char*) * M); // Alocação de um array de strings

    // Entrada das palavras escolhidas e de suas pontuações
    for (int i = 0; i < N; i++) {
        scanf("%s %d", palavras_escolhidas[i].conteudo, &palavras_escolhidas[i].pontuacao);
    }

    // Leitura de cada palavra digitada até que se leia um ponto "." e concatenação das palavras para formar o texto
    for (int i = 0; i < M; i++) {
        texto_alunos[i] = (char*)malloc(sizeof(char));
        char* string_auxiliar = (char*)malloc(sizeof(char));
        int tamanho_string = 0;

        while (strcmp(string_auxiliar, ".") != 0) {
            scanf("%s", string_auxiliar);

            // Alolcação dinâmica de cada palavra no texto
            tamanho_string += strlen(string_auxiliar) + 1;
            texto_alunos[i] = (char*)realloc(texto_alunos[i], sizeof(char) * ++tamanho_string);

            if (strcmp(string_auxiliar, ".") != 0) {
                strcat(texto_alunos[i], string_auxiliar);
                strcat(texto_alunos[i], " "); // Separação das palavras por um espaço
            }
        }
    }

    // Cria a Tabela Hash
    inicia_tabela(N);

    // Inserção das palavras escolhidas na Tabela
    for (int i = 0; i < N; i++) {
        insere(palavras_escolhidas[i].conteudo, palavras_escolhidas[i].pontuacao);
    }

    // Resultado final da pontuação de cada texto dos alunos
    for (int i = 0; i < M; i++) {
        printf("%d\n", calcula_pontuacao(texto_alunos[i]));
    }

    return 0;
}
