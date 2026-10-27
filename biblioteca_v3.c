/*
 * Sistema de Biblioteca - Versao 3
 * Conteudo em foco: funcoes, parametros, valores de retorno e escopo.
 * Mesmo comportamento da Versao 2, agora organizado em funcoes.
 * As tres descricoes continuam separadas (a Versao 4 resolve com struct).
 */
#include <stdio.h>
#include <string.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 121   /* 120 caracteres + '\0' */

/* ---------- Prototipos ---------- */
int cadastrarTitulo(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
);

void listarTitulos(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
);

int buscarTitulo(
    int codigos[],
    int qtdTitulos,
    int codigoBuscado
);

int calcularQtdExemplares(
    int estoques[],
    int qtdTitulos
);

int disponibilidadeTitulo(
    int qtdEstoque
);

/* Auxiliares */
void limparBuffer(void);
void lerDescricao(char destino[]);

/* ---------- main: roteiro das operacoes ---------- */
int main(void) {
    int codigos[MAX_TITULOS];
    int estoques[MAX_TITULOS];
    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];
    int qtdTitulos = 0;

    int codigoBuscado;
    int posBusca;
    int disponivel;
    int qtdExemplares;

    /* 1. cadastrar os titulos */
    printf("=== Cadastro de titulos ===\n");
    while (qtdTitulos < MAX_TITULOS) {
        printf("\nTitulo %d de %d\n", qtdTitulos + 1, MAX_TITULOS);
        qtdTitulos = cadastrarTitulo(
            codigos,
            estoques,
            descricao1,
            descricao2,
            descricao3,
            qtdTitulos
        );
    }

    /* 2. listar os titulos */
    listarTitulos(
        codigos,
        estoques,
        descricao1,
        descricao2,
        descricao3,
        qtdTitulos
    );

    /* 3. solicitar um codigo para busca */
    printf("\nCodigo para buscar: ");
    scanf("%d", &codigoBuscado);

    /* 4. buscar o titulo */
    posBusca = buscarTitulo(codigos, qtdTitulos, codigoBuscado);

    if (posBusca == -1) {
        printf("Titulo nao encontrado.\n");
    } else {
        printf("Titulo encontrado na posicao %d.\n", posBusca);

        /* 5. verificar a disponibilidade (so acessa o vetor se posBusca != -1) */
        disponivel = disponibilidadeTitulo(estoques[posBusca]);

        if (disponivel == 1) {
            printf("Titulo disponivel.\n");
        } else {
            printf("Titulo temporariamente indisponivel.\n");
        }
    }

    /* 6. calcular e mostrar o total de exemplares */
    qtdExemplares = calcularQtdExemplares(estoques, qtdTitulos);
    printf("\nTotal de exemplares: %d\n", qtdExemplares);

    return 0;
}

/* ---------- Implementacoes ---------- */

int cadastrarTitulo(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
) {
    int codigo, estoque;
    int valido;

    if (qtdTitulos >= MAX_TITULOS) {
        printf("Limite maximo de titulos atingido.\n");
        return qtdTitulos;
    }

    /* Codigo: positivo e unico */
    do {
        valido = 1;
        printf("Codigo do titulo: ");
        scanf("%d", &codigo);

        if (codigo <= 0) {
            printf("Codigo invalido: deve ser um inteiro positivo.\n");
            valido = 0;
        } else if (buscarTitulo(codigos, qtdTitulos, codigo) != -1) {
            printf("Codigo ja cadastrado.\n");
            valido = 0;
        }
    } while (!valido);

    /* Estoque: nao negativo */
    do {
        valido = 1;
        printf("Quantidade em estoque: ");
        scanf("%d", &estoque);

        if (estoque < 0) {
            printf("Estoque invalido: nao pode ser negativo.\n");
            valido = 0;
        }
    } while (!valido);

    limparBuffer();

    printf("Descricao (Titulo; Autor; Ano; Tema): ");
    if (qtdTitulos == 0) {
        lerDescricao(descricao1);
    } else if (qtdTitulos == 1) {
        lerDescricao(descricao2);
    } else {
        lerDescricao(descricao3);
    }

    codigos[qtdTitulos] = codigo;
    estoques[qtdTitulos] = estoque;

    return qtdTitulos + 1;
}

void listarTitulos(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
) {
    int i;

    printf("\n=== Titulos cadastrados ===\n");
    for (i = 0; i < qtdTitulos; i++) {
        printf("Codigo: %d | Estoque: %d | ", codigos[i], estoques[i]);
        if (i == 0) {
            printf("%s\n", descricao1);
        } else if (i == 1) {
            printf("%s\n", descricao2);
        } else {
            printf("%s\n", descricao3);
        }
    }
}

int buscarTitulo(
    int codigos[],
    int qtdTitulos,
    int codigoBuscado
) {
    int i;

    for (i = 0; i < qtdTitulos; i++) {
        if (codigos[i] == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

int calcularQtdExemplares(
    int estoques[],
    int qtdTitulos
) {
    int qtdExemplares = 0;   /* acumulador sempre inicializado */
    int i;

    for (i = 0; i < qtdTitulos; i++) {
        qtdExemplares += estoques[i];
    }
    return qtdExemplares;
}

int disponibilidadeTitulo(
    int qtdEstoque
) {
    if (qtdEstoque > 0) {
        return 1;
    }
    return 0;
}

/* ---------- Auxiliares ---------- */

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void lerDescricao(char destino[]) {
    fgets(destino, TAM_TEXTO, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}
