/*
 * Sistema de Biblioteca - Versao 5
 * Conteudo em foco: ponteiros e passagem por endereco.
 * Parte da Versao 4 e acrescenta funcoes que alteram o livro/usuario original
 * recebido por ponteiro (operador ->), sem usar variaveis globais.
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

/* Versao 5: funcoes que recebem o ENDERECO do objeto e alteram o original */
void alterarEstoque(Livro *livro, int valor);
void registrarEmprestimo(Usuario *usuario, int codigoLivro);
void encerrarEmprestimo(Usuario *usuario);

/* Funcoes de consulta (recebem copia, apenas exibem) */
void imprimirLivro(Livro livro);
void imprimirUsuario(Usuario usuario);

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

    /* 7. demonstracao de ponteiros: as alteracoes feitas nas funcoes
          devem continuar visiveis na main depois que a funcao termina */
    int codigoLivro, codigoUsuario;
    int posLivro, posUsuario;

    printf("\n=== Demonstracao de ponteiros ===\n");
    printf("Codigo do livro: ");
    scanf("%d", &codigoLivro);
    printf("Codigo do usuario: ");
    scanf("%d", &codigoUsuario);

    posLivro = buscarLivro(livros, qtdLivros, codigoLivro);
    posUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);

    if (posLivro == -1 || posUsuario == -1) {
        printf("Livro ou usuario nao encontrado.\n");
    } else {
        printf("\nEstado inicial:\n");
        imprimirLivro(livros[posLivro]);
        imprimirUsuario(usuarios[posUsuario]);

        printf("\nalterarEstoque(+1):\n");
        alterarEstoque(&livros[posLivro], 1);
        imprimirLivro(livros[posLivro]);

        printf("\nalterarEstoque(+1) novamente (as alteracoes se acumulam):\n");
        alterarEstoque(&livros[posLivro], 1);
        imprimirLivro(livros[posLivro]);

        printf("\nalterarEstoque(-2) (volta ao valor original):\n");
        alterarEstoque(&livros[posLivro], -2);
        imprimirLivro(livros[posLivro]);

        printf("\nregistrarEmprestimo:\n");
        registrarEmprestimo(&usuarios[posUsuario], livros[posLivro].codigo);
        imprimirUsuario(usuarios[posUsuario]);

        printf("\nencerrarEmprestimo:\n");
        encerrarEmprestimo(&usuarios[posUsuario]);
        imprimirUsuario(usuarios[posUsuario]);
    }

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

/* ---------- Versao 5: ponteiros ---------- */

/* Soma "valor" ao estoque do livro original (use valores negativos para reduzir).
   Nao permite que o estoque fique negativo. */
void alterarEstoque(Livro *livro, int valor) {
    if (livro->estoque + valor < 0) {
        printf("Alteracao recusada: o estoque ficaria negativo.\n");
        return;
    }
    livro->estoque = livro->estoque + valor;
}

/* Registra no usuario original qual livro esta com ele */
void registrarEmprestimo(Usuario *usuario, int codigoLivro) {
    usuario->codigoLivroEmprestado = codigoLivro;
}

/* Libera o usuario original (nenhum livro emprestado) */
void encerrarEmprestimo(Usuario *usuario) {
    usuario->codigoLivroEmprestado = -1;
}

void imprimirLivro(Livro livro) {
    printf("  Livro   -> Codigo: %d | Estoque: %d | %s\n",
           livro.codigo, livro.estoque, livro.descricao);
}

void imprimirUsuario(Usuario usuario) {
    printf("  Usuario -> Codigo: %d | %s | Livro emprestado: %d\n",
           usuario.codigo, usuario.dados, usuario.codigoLivroEmprestado);
}
