/*
 * Sistema de Biblioteca - Versao 6
 * Integracao de vetores, strings, funcoes, structs e ponteiros.
 *
 * Regras gerais:
 *  - no maximo 3 livros e 3 usuarios;
 *  - codigos inteiros, positivos e unicos;
 *  - cada usuario pode ter no maximo 1 livro emprestado (-1 = nenhum);
 *  - se qualquer regra falhar: mostra mensagem, NAO altera nenhum dado e
 *    volta ao menu.
 */
#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 3
#define MAX_USUARIOS 3
#define TAM_TEXTO 121          /* 120 caracteres + '\0' */
#define SEM_EMPRESTIMO -1

typedef struct {
    int codigo;
    char descricao[TAM_TEXTO];
    int estoque;
} Livro;

typedef struct {
    int codigo;
    char dados[TAM_TEXTO];
    int codigoLivroEmprestado;
} Usuario;

/* ---------- Prototipos ---------- */

/* Menu e entrada de dados */
void exibirMenu(void);
void limparBuffer(void);
int lerInteiro(const char mensagem[], int *valor);
void lerTexto(char destino[]);

/* Cadastro (devolvem 1 = sucesso, 0 = nada foi alterado) */
int cadastrarLivro(Livro livros[], int *qtdLivros);
int cadastrarUsuario(Usuario usuarios[], int *qtdUsuarios);

/* Consultas */
void listarLivros(Livro livros[], int qtdLivros);
void listarUsuarios(Usuario usuarios[], int qtdUsuarios);
int buscarLivro(Livro livros[], int qtd, int codigo);
int buscarUsuario(Usuario usuarios[], int qtd, int codigo);
void imprimirLivro(const Livro *livro);
void imprimirUsuario(const Usuario *usuario);

/* Operacoes que alteram os originais (1 = sucesso, 0 = nao realizada) */
int emprestarLivro(Livro *livro, Usuario *usuario);
int devolverLivro(Livro *livro, Usuario *usuario);

/* Acoes do menu */
void opcaoBuscarLivro(Livro livros[], int qtdLivros);
void opcaoBuscarUsuario(Usuario usuarios[], int qtdUsuarios);
void opcaoEmprestar(Livro livros[], int qtdLivros,
                    Usuario usuarios[], int qtdUsuarios);
void opcaoDevolver(Livro livros[], int qtdLivros,
                   Usuario usuarios[], int qtdUsuarios);

/* ---------- main ---------- */
int main(void) {
    Livro livros[MAX_LIVROS];
    Usuario usuarios[MAX_USUARIOS];
    int qtdLivros = 0;
    int qtdUsuarios = 0;
    int opcao;

    do {
        exibirMenu();

        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
            /* entrada nao numerica: opcao invalida (ou fim da entrada) */
            opcao = feof(stdin) ? 0 : -1;
        }

        switch (opcao) {
            case 1:
                if (cadastrarLivro(livros, &qtdLivros)) {
                    printf("Livro cadastrado com sucesso.\n");
                }
                break;
            case 2:
                if (cadastrarUsuario(usuarios, &qtdUsuarios)) {
                    printf("Usuario cadastrado com sucesso.\n");
                }
                break;
            case 3:
                listarLivros(livros, qtdLivros);
                break;
            case 4:
                opcaoBuscarLivro(livros, qtdLivros);
                break;
            case 5:
                opcaoEmprestar(livros, qtdLivros, usuarios, qtdUsuarios);
                break;
            case 6:
                opcaoDevolver(livros, qtdLivros, usuarios, qtdUsuarios);
                break;
            case 7:
                listarUsuarios(usuarios, qtdUsuarios);
                break;
            case 8:
                opcaoBuscarUsuario(usuarios, qtdUsuarios);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Escolha um numero do menu.\n");
        }
    } while (opcao != 0);

    return 0;
}

/* ---------- Menu e entrada de dados ---------- */

void exibirMenu(void) {
    printf("\n=== Sistema de Biblioteca ===\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Cadastrar usuario\n");
    printf("3 - Listar livros\n");
    printf("4 - Buscar livro\n");
    printf("5 - Emprestar livro\n");
    printf("6 - Devolver livro\n");
    printf("7 - Listar usuarios\n");
    printf("8 - Buscar usuario\n");
    printf("0 - Sair\n");
}

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Le um inteiro e descarta o resto da linha (deixa o teclado pronto para fgets).
   Devolve 1 se leu um numero e 0 caso contrario. */
int lerInteiro(const char mensagem[], int *valor) {
    int lidos;

    printf("%s", mensagem);
    lidos = scanf("%d", valor);
    limparBuffer();
    return lidos == 1;
}

void lerTexto(char destino[]) {
    if (fgets(destino, TAM_TEXTO, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }
    destino[strcspn(destino, "\n")] = '\0';
}

/* ---------- Cadastro ---------- */

/* Todos os dados sao lidos e validados ANTES de gravar no vetor,
   assim uma falha nunca deixa um cadastro pela metade. */
int cadastrarLivro(Livro livros[], int *qtdLivros) {
    int codigo, estoque;
    char descricao[TAM_TEXTO];

    if (*qtdLivros >= MAX_LIVROS) {
        printf("Limite de %d livros atingido.\n", MAX_LIVROS);
        return 0;
    }

    if (!lerInteiro("Codigo do livro: ", &codigo) || codigo <= 0) {
        printf("Codigo invalido: informe um inteiro positivo.\n");
        return 0;
    }
    if (buscarLivro(livros, *qtdLivros, codigo) != -1) {
        printf("Ja existe um livro com o codigo %d.\n", codigo);
        return 0;
    }

    if (!lerInteiro("Quantidade em estoque: ", &estoque) || estoque < 0) {
        printf("Estoque invalido: informe um inteiro maior ou igual a zero.\n");
        return 0;
    }

    printf("Descricao (Titulo; Autor; Ano; Tema): ");
    lerTexto(descricao);
    if (descricao[0] == '\0') {
        printf("A descricao nao pode ficar vazia.\n");
        return 0;
    }

    livros[*qtdLivros].codigo = codigo;
    livros[*qtdLivros].estoque = estoque;
    strcpy(livros[*qtdLivros].descricao, descricao);
    (*qtdLivros)++;
    return 1;
}

int cadastrarUsuario(Usuario usuarios[], int *qtdUsuarios) {
    int codigo;
    char dados[TAM_TEXTO];

    if (*qtdUsuarios >= MAX_USUARIOS) {
        printf("Limite de %d usuarios atingido.\n", MAX_USUARIOS);
        return 0;
    }

    if (!lerInteiro("Codigo do usuario: ", &codigo) || codigo <= 0) {
        printf("Codigo invalido: informe um inteiro positivo.\n");
        return 0;
    }
    if (buscarUsuario(usuarios, *qtdUsuarios, codigo) != -1) {
        printf("Ja existe um usuario com o codigo %d.\n", codigo);
        return 0;
    }

    printf("Dados do usuario (nome, contato...): ");
    lerTexto(dados);
    if (dados[0] == '\0') {
        printf("Os dados do usuario nao podem ficar vazios.\n");
        return 0;
    }

    usuarios[*qtdUsuarios].codigo = codigo;
    strcpy(usuarios[*qtdUsuarios].dados, dados);
    usuarios[*qtdUsuarios].codigoLivroEmprestado = SEM_EMPRESTIMO;
    (*qtdUsuarios)++;
    return 1;
}

/* ---------- Consultas ---------- */

void listarLivros(Livro livros[], int qtdLivros) {
    int i;

    if (qtdLivros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    printf("\n=== Livros cadastrados ===\n");
    for (i = 0; i < qtdLivros; i++) {
        imprimirLivro(&livros[i]);
    }
}

void listarUsuarios(Usuario usuarios[], int qtdUsuarios) {
    int i;

    if (qtdUsuarios == 0) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }
    printf("\n=== Usuarios cadastrados ===\n");
    for (i = 0; i < qtdUsuarios; i++) {
        imprimirUsuario(&usuarios[i]);
    }
}

int buscarLivro(Livro livros[], int qtd, int codigo) {
    int i;

    for (i = 0; i < qtd; i++) {
        if (livros[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscarUsuario(Usuario usuarios[], int qtd, int codigo) {
    int i;

    for (i = 0; i < qtd; i++) {
        if (usuarios[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void imprimirLivro(const Livro *livro) {
    printf("Codigo: %d | Estoque: %d (%s) | %s\n",
           livro->codigo, livro->estoque,
           livro->estoque > 0 ? "disponivel" : "indisponivel",
           livro->descricao);
}

void imprimirUsuario(const Usuario *usuario) {
    printf("Codigo: %d | %s | ", usuario->codigo, usuario->dados);
    if (usuario->codigoLivroEmprestado == SEM_EMPRESTIMO) {
        printf("Sem livro emprestado\n");
    } else {
        printf("Livro emprestado: %d\n", usuario->codigoLivroEmprestado);
    }
}

/* ---------- Emprestimo e devolucao ---------- */

/* As duas mudancas (livro e usuario) so acontecem juntas, depois de
   TODAS as validacoes. */
int emprestarLivro(Livro *livro, Usuario *usuario) {
    if (livro == NULL || usuario == NULL) {
        return 0;
    }
    if (livro->estoque <= 0) {
        printf("O livro %d nao tem exemplares disponiveis.\n", livro->codigo);
        return 0;
    }
    if (usuario->codigoLivroEmprestado != SEM_EMPRESTIMO) {
        printf("O usuario %d ja possui o livro %d emprestado.\n",
               usuario->codigo, usuario->codigoLivroEmprestado);
        return 0;
    }

    livro->estoque--;
    usuario->codigoLivroEmprestado = livro->codigo;
    return 1;
}

int devolverLivro(Livro *livro, Usuario *usuario) {
    if (livro == NULL || usuario == NULL) {
        return 0;
    }
    if (usuario->codigoLivroEmprestado == SEM_EMPRESTIMO) {
        printf("O usuario %d nao possui livro emprestado.\n", usuario->codigo);
        return 0;
    }
    if (usuario->codigoLivroEmprestado != livro->codigo) {
        printf("O usuario %d esta com o livro %d, e nao com o livro %d.\n",
               usuario->codigo, usuario->codigoLivroEmprestado, livro->codigo);
        return 0;
    }

    livro->estoque++;
    usuario->codigoLivroEmprestado = SEM_EMPRESTIMO;
    return 1;
}

/* ---------- Acoes do menu ---------- */

void opcaoBuscarLivro(Livro livros[], int qtdLivros) {
    int codigo, pos;

    if (!lerInteiro("Codigo do livro: ", &codigo)) {
        printf("Codigo invalido.\n");
        return;
    }
    pos = buscarLivro(livros, qtdLivros, codigo);
    if (pos == -1) {
        printf("Livro %d nao encontrado.\n", codigo);
    } else {
        printf("Livro encontrado:\n");
        imprimirLivro(&livros[pos]);
    }
}

void opcaoBuscarUsuario(Usuario usuarios[], int qtdUsuarios) {
    int codigo, pos;

    if (!lerInteiro("Codigo do usuario: ", &codigo)) {
        printf("Codigo invalido.\n");
        return;
    }
    pos = buscarUsuario(usuarios, qtdUsuarios, codigo);
    if (pos == -1) {
        printf("Usuario %d nao encontrado.\n", codigo);
    } else {
        printf("Usuario encontrado:\n");
        imprimirUsuario(&usuarios[pos]);
    }
}

void opcaoEmprestar(Livro livros[], int qtdLivros,
                    Usuario usuarios[], int qtdUsuarios) {
    int codigoUsuario, codigoLivro;
    int indiceUsuario, indiceLivro;

    if (!lerInteiro("Codigo do usuario: ", &codigoUsuario) ||
        !lerInteiro("Codigo do livro: ", &codigoLivro)) {
        printf("Codigo invalido. Nao foi possivel realizar o emprestimo.\n");
        return;
    }

    indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);
    if (indiceUsuario == -1) {
        printf("Usuario %d nao encontrado. Nao foi possivel realizar o emprestimo.\n",
               codigoUsuario);
        return;
    }
    indiceLivro = buscarLivro(livros, qtdLivros, codigoLivro);
    if (indiceLivro == -1) {
        printf("Livro %d nao encontrado. Nao foi possivel realizar o emprestimo.\n",
               codigoLivro);
        return;
    }

    if (emprestarLivro(&livros[indiceLivro], &usuarios[indiceUsuario])) {
        printf("Emprestimo realizado.\n");
    } else {
        printf("Nao foi possivel realizar o emprestimo.\n");
    }
}

void opcaoDevolver(Livro livros[], int qtdLivros,
                   Usuario usuarios[], int qtdUsuarios) {
    int codigoUsuario, codigoLivro;
    int indiceUsuario, indiceLivro;

    if (!lerInteiro("Codigo do usuario: ", &codigoUsuario) ||
        !lerInteiro("Codigo do livro: ", &codigoLivro)) {
        printf("Codigo invalido. Nao foi possivel realizar a devolucao.\n");
        return;
    }

    indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);
    if (indiceUsuario == -1) {
        printf("Usuario %d nao encontrado. Nao foi possivel realizar a devolucao.\n",
               codigoUsuario);
        return;
    }
    indiceLivro = buscarLivro(livros, qtdLivros, codigoLivro);
    if (indiceLivro == -1) {
        printf("Livro %d nao encontrado. Nao foi possivel realizar a devolucao.\n",
               codigoLivro);
        return;
    }

    if (devolverLivro(&livros[indiceLivro], &usuarios[indiceUsuario])) {
        printf("Devolucao realizada.\n");
    } else {
        printf("Nao foi possivel realizar a devolucao.\n");
    }
}
