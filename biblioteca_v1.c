/*
 * Sistema de Biblioteca - Versao 1
 * Conteudo em foco: vetores, for, while e estruturas de decisao.
 * Cada livro e identificado somente por codigo e estoque.
 */
#include <stdio.h>

#define MAX_LIVROS 3

int main(void) {
    int codigos[MAX_LIVROS];
    int estoques[MAX_LIVROS];
    int qtdLivros = 0;
    int estoqueTotal = 0;

    int codigo, estoque;
    int i, valido;

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

        /* So grava nos vetores depois de validar tudo */
        codigos[qtdLivros] = codigo;
        estoques[qtdLivros] = estoque;
        qtdLivros++;
    }

    /* ---------- Listagem ---------- */
    printf("\n=== Livros cadastrados ===\n");
    for (i = 0; i < qtdLivros; i++) {
        printf("Codigo: %d | Estoque: %d\n", codigos[i], estoques[i]);
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
        printf("Livro encontrado: Codigo %d | Estoque %d\n",
               codigos[posBusca], estoques[posBusca]);

        if (estoques[posBusca] > 0) {
            printf("Situacao: disponivel.\n");
        } else {
            printf("Situacao: indisponivel.\n");
        }
    }

    return 0;
}
