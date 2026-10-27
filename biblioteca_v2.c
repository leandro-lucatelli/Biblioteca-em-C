/*
 * Sistema de Biblioteca - Versao 2
 * Conteudo em foco: strings como vetores de caracteres.
 * Acrescenta a descricao "Titulo; Autor; Ano; Tema" (ate 120 caracteres).
 * A repeticao de descricao1/2/3 e intencional: a Versao 4 resolve com struct.
 */
#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 3
#define TAM_TEXTO 121   /* 120 caracteres + '\0' */

int main(void) {
    int codigos[MAX_LIVROS];
    int estoques[MAX_LIVROS];
    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];
    int qtdLivros = 0;
    int estoqueTotal = 0;

    int codigo, estoque;
    int i, valido, c;

    /* ---------- Cadastro dos 3 livros ---------- */
    printf("=== Cadastro de livros ===\n");
    while (qtdLivros < MAX_LIVROS) {
        printf("\nLivro %d de %d\n", qtdLivros + 1, MAX_LIVROS);

        /* Codigo: inteiro positivo e unico */
        do {
            valido = 1;
            printf("Codigo do livro: ");
            scanf("%d", &codigo);

            if (codigo <= 0) {
                printf("Codigo invalido: deve ser um inteiro positivo.\n");
                valido = 0;
            } else {
                for (i = 0; i < qtdLivros; i++) {
                    if (codigos[i] == codigo) {
                        printf("Codigo ja cadastrado.\n");
                        valido = 0;
                        break;
                    }
                }
            }
        } while (!valido);

        /* Estoque: nao pode ser negativo */
        do {
            valido = 1;
            printf("Quantidade em estoque: ");
            scanf("%d", &estoque);

            if (estoque < 0) {
                printf("Estoque invalido: nao pode ser negativo.\n");
                valido = 0;
            }
        } while (!valido);

        /* Descarta o '\n' que o scanf deixou no teclado antes do fgets */
        while ((c = getchar()) != '\n' && c != EOF) { }

        printf("Descricao (Titulo; Autor; Ano; Tema): ");
        if (qtdLivros == 0) {
            fgets(descricao1, TAM_TEXTO, stdin);
            descricao1[strcspn(descricao1, "\n")] = '\0';
        } else if (qtdLivros == 1) {
            fgets(descricao2, TAM_TEXTO, stdin);
            descricao2[strcspn(descricao2, "\n")] = '\0';
        } else {
            fgets(descricao3, TAM_TEXTO, stdin);
            descricao3[strcspn(descricao3, "\n")] = '\0';
        }

        codigos[qtdLivros] = codigo;
        estoques[qtdLivros] = estoque;
        qtdLivros++;
    }

    /* ---------- Listagem ---------- */
    printf("\n=== Livros cadastrados ===\n");
    for (i = 0; i < qtdLivros; i++) {
        printf("Codigo: %d | Estoque: %d | ", codigos[i], estoques[i]);
        if (i == 0) {
            printf("%s\n", descricao1);
        } else if (i == 1) {
            printf("%s\n", descricao2);
        } else {
            printf("%s\n", descricao3);
        }
    }

    /* ---------- Total de exemplares ---------- */
    for (i = 0; i < qtdLivros; i++) {
        estoqueTotal += estoques[i];
    }
    printf("\nTotal de exemplares: %d\n", estoqueTotal);

    /* ---------- Busca por codigo ---------- */
    printf("\nCodigo para buscar: ");
    scanf("%d", &codigo);

    int posBusca = -1;
    for (i = 0; i < qtdLivros; i++) {
        if (codigos[i] == codigo) {
            posBusca = i;
            break;
        }
    }

    if (posBusca == -1) {
        printf("Codigo nao encontrado.\n");
    } else {
        printf("Livro encontrado: Codigo %d | Estoque %d | ",
               codigos[posBusca], estoques[posBusca]);
        if (posBusca == 0) {
            printf("%s\n", descricao1);
        } else if (posBusca == 1) {
            printf("%s\n", descricao2);
        } else {
            printf("%s\n", descricao3);
        }

        if (estoques[posBusca] > 0) {
            printf("Situacao: disponivel.\n");
        } else {
            printf("Situacao: indisponivel.\n");
        }
    }

    return 0;
}
