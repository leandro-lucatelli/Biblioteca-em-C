/*
 * Sistema de Biblioteca - Versao 4
 * Conteudo em foco: structs e vetores de structs.
 * Cada posicao de livros[] e um livro completo (codigo, descricao, estoque).
 * Os usuarios tambem passam a ser representados por uma struct.
 */
#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 3
#define MAX_USUARIOS 3
#define TAM_TEXTO 121   /* 120 caracteres + '\0' */

typedef struct {
    int codigo;
    char descricao[TAM_TEXTO];
    int estoque;
} Livro;

typedef struct {
    int codigo;
    char dados[TAM_TEXTO];
    int codigoLivroEmprestado;   /* -1 = nenhum livro emprestado */
} Usuario;

/* ---------- Prototipos ---------- */
int cadastrarLivro(Livro livros[], int qtdLivros);
void listarLivros(Livro livros[], int qtdLivros);
int buscarLivro(Livro livros[], int qtdLivros, int codigoBuscado);
int calcularQtdExemplares(Livro livros[], int qtdLivros);
int disponibilidadeLivro(int qtdEstoque);

int cadastrarUsuario(Usuario usuarios[], int qtdUsuarios);
void listarUsuarios(Usuario usuarios[], int qtdUsuarios);
int buscarUsuario(Usuario usuarios[], int qtdUsuarios, int codigoBuscado);

void limparBuffer(void);
void lerTexto(char destino[]);

/* ---------- main: roteiro das operacoes ---------- */
int main(void) {
    Livro livros[MAX_LIVROS];
    Usuario usuarios[MAX_USUARIOS];
    int qtdLivros = 0;
    int qtdUsuarios = 0;

    int codigoBuscado;
    int posBusca;

    /* 1. cadastrar os livros */
    printf("=== Cadastro de livros ===\n");
    while (qtdLivros < MAX_LIVROS) {
        printf("\nLivro %d de %d\n", qtdLivros + 1, MAX_LIVROS);
        qtdLivros = cadastrarLivro(livros, qtdLivros);
    }

    /* 2. listar os livros */
    listarLivros(livros, qtdLivros);

    /* 3. buscar um livro e mostrar todos os seus dados */
    printf("\nCodigo do livro para buscar: ");
    scanf("%d", &codigoBuscado);
    posBusca = buscarLivro(livros, qtdLivros, codigoBuscado);

    if (posBusca == -1) {
        printf("Livro nao encontrado.\n");
    } else {
        printf("Livro encontrado:\n");
        printf("  Codigo: %d\n", livros[posBusca].codigo);
        printf("  Descricao: %s\n", livros[posBusca].descricao);
        printf("  Estoque: %d\n", livros[posBusca].estoque);
        if (disponibilidadeLivro(livros[posBusca].estoque) == 1) {
            printf("  Situacao: disponivel.\n");
        } else {
            printf("  Situacao: temporariamente indisponivel.\n");
        }
    }

    /* 4. total de exemplares */
    printf("\nTotal de exemplares: %d\n", calcularQtdExemplares(livros, qtdLivros));

    /* 5. cadastrar os usuarios */
    printf("\n=== Cadastro de usuarios ===\n");
    while (qtdUsuarios < MAX_USUARIOS) {
        printf("\nUsuario %d de %d\n", qtdUsuarios + 1, MAX_USUARIOS);
        qtdUsuarios = cadastrarUsuario(usuarios, qtdUsuarios);
    }

    /* 6. listar os usuarios (todos devem iniciar com -1) */
    listarUsuarios(usuarios, qtdUsuarios);

    /* fim do roteiro */
    return 0;
}

/* ---------- Livros ---------- */

int cadastrarLivro(Livro livros[], int qtdLivros) {
    int codigo, estoque;
    int valido;

    if (qtdLivros >= MAX_LIVROS) {
        printf("Limite maximo de livros atingido.\n");
        return qtdLivros;
    }

    do {
        valido = 1;
        printf("Codigo do livro: ");
        scanf("%d", &codigo);

        if (codigo <= 0) {
            printf("Codigo invalido: deve ser um inteiro positivo.\n");
            valido = 0;
        } else if (buscarLivro(livros, qtdLivros, codigo) != -1) {
            printf("Codigo ja cadastrado.\n");
            valido = 0;
        }
    } while (!valido);

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
    lerTexto(livros[qtdLivros].descricao);

    livros[qtdLivros].codigo = codigo;
    livros[qtdLivros].estoque = estoque;

    return qtdLivros + 1;
}

void listarLivros(Livro livros[], int qtdLivros) {
    int i;

    printf("\n=== Livros cadastrados ===\n");
    for (i = 0; i < qtdLivros; i++) {
        printf("Codigo: %d | Estoque: %d | %s\n",
               livros[i].codigo, livros[i].estoque, livros[i].descricao);
    }
}

int buscarLivro(Livro livros[], int qtdLivros, int codigoBuscado) {
    int i;

    for (i = 0; i < qtdLivros; i++) {
        if (livros[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

int calcularQtdExemplares(Livro livros[], int qtdLivros) {
    int qtdExemplares = 0;
    int i;

    for (i = 0; i < qtdLivros; i++) {
        qtdExemplares += livros[i].estoque;
    }
    return qtdExemplares;
}

int disponibilidadeLivro(int qtdEstoque) {
    if (qtdEstoque > 0) {
        return 1;
    }
    return 0;
}

/* ---------- Usuarios ---------- */

int cadastrarUsuario(Usuario usuarios[], int qtdUsuarios) {
    int codigo;
    int valido;

    if (qtdUsuarios >= MAX_USUARIOS) {
        printf("Limite maximo de usuarios atingido.\n");
        return qtdUsuarios;
    }

    do {
        valido = 1;
        printf("Codigo do usuario: ");
        scanf("%d", &codigo);

        if (codigo <= 0) {
            printf("Codigo invalido: deve ser um inteiro positivo.\n");
            valido = 0;
        } else if (buscarUsuario(usuarios, qtdUsuarios, codigo) != -1) {
            printf("Codigo ja cadastrado.\n");
            valido = 0;
        }
    } while (!valido);

    limparBuffer();

    printf("Dados do usuario (nome, contato...): ");
    lerTexto(usuarios[qtdUsuarios].dados);

    usuarios[qtdUsuarios].codigo = codigo;
    usuarios[qtdUsuarios].codigoLivroEmprestado = -1;   /* nenhum emprestimo */

    return qtdUsuarios + 1;
}

void listarUsuarios(Usuario usuarios[], int qtdUsuarios) {
    int i;

    printf("\n=== Usuarios cadastrados ===\n");
    for (i = 0; i < qtdUsuarios; i++) {
        printf("Codigo: %d | %s | Livro emprestado: %d\n",
               usuarios[i].codigo, usuarios[i].dados,
               usuarios[i].codigoLivroEmprestado);
    }
}

int buscarUsuario(Usuario usuarios[], int qtdUsuarios, int codigoBuscado) {
    int i;

    for (i = 0; i < qtdUsuarios; i++) {
        if (usuarios[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

/* ---------- Auxiliares ---------- */

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void lerTexto(char destino[]) {
    fgets(destino, TAM_TEXTO, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}
