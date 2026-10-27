# 📚 Sistema de Biblioteca em C

<div align="center">

**Projeto acadêmico de Algoritmos e Lógica de Programação**

Desenvolvimento incremental de um sistema de gerenciamento de biblioteca utilizando a linguagem C.

</div>

---

## 📖 Sobre o projeto

O **Sistema de Biblioteca em C** é um projeto acadêmico desenvolvido para aplicar, de forma progressiva, os fundamentos da programação estruturada.

O sistema é construído em seis versões, cada uma introduzindo novos conceitos da linguagem C e aprimorando a organização e as funcionalidades da aplicação.

O objetivo é compreender como os conceitos de programação podem ser utilizados para resolver problemas reais, desde o controle de estoque de livros até o gerenciamento de empréstimos e devoluções.

## 🎯 Objetivos

- Praticar lógica de programação e resolução de problemas.
- Compreender a utilização de vetores e strings.
- Desenvolver funções com responsabilidades específicas.
- Organizar dados utilizando `struct`.
- Aplicar ponteiros e passagem de parâmetros por endereço.
- Integrar os conceitos estudados em um sistema funcional.
- Implementar validações para preservar a consistência dos dados.

## 🛠️ Tecnologias utilizadas

- **Linguagem:** C
- **Compilador:** GCC
- **Versionamento:** Git e GitHub

## 🗂️ Evolução do projeto

O desenvolvimento está organizado em seis versões independentes, que representam a evolução dos conhecimentos aplicados ao sistema.

| Versão | Conceito principal | Objetivo |
|:---:|---|---|
| V1 | Vetores e repetições | Controle de códigos e estoque de livros. |
| V2 | Strings | Armazenamento de título, autor, ano e tema. |
| V3 | Funções | Separação das operações em funções reutilizáveis. |
| V4 | Structs | Organização dos dados de livros e usuários. |
| V5 | Ponteiros | Alteração de dados por meio de endereços de memória. |
| V6 | Integração | Gerenciamento de livros, usuários, empréstimos e devoluções. |

## ⚙️ Funcionalidades previstas

A versão integrada do sistema contempla as seguintes operações:

- Cadastro de livros.
- Cadastro de usuários.
- Listagem do acervo.
- Busca de livros por código.
- Empréstimo de livros.
- Devolução de livros.
- Atualização automática do estoque.
- Controle de livros emprestados por usuário.
- Validação de códigos e quantidades.
- Menu interativo no terminal.

## 📏 Regras de negócio

O projeto segue regras específicas para garantir a consistência das operações:

- Limite de três títulos de livros cadastrados.
- Limite de três usuários cadastrados.
- Códigos inteiros, positivos e únicos para livros e usuários.
- Proibição de estoque negativo.
- Cada usuário pode possuir, no máximo, um livro emprestado por vez.
- O empréstimo exige que exista estoque disponível.
- A devolução deve corresponder ao livro registrado no usuário.
- Operações inválidas não podem alterar os dados do sistema.
- O empréstimo e a devolução devem atualizar corretamente o estoque e o registro do usuário.

## 🧠 Conceitos de programação aplicados

### Vetores e estruturas de repetição
Armazenamento de códigos e estoques, percorrendo posições para cadastrar, listar e localizar livros.

### Strings
Representação textual das informações dos livros e dos dados pessoais dos usuários.

### Funções
Modularização do código para separar cadastro, listagem, busca, cálculos e operações de empréstimo.

### Structs
Criação de estruturas `Livro` e `Usuario` para agrupar informações relacionadas em uma única entidade.

### Ponteiros
Manipulação dos dados originais por meio da passagem de endereços para funções.

### Integração de conceitos
Combinação dos recursos estudados para implementar regras de negócio e manter a consistência dos dados.

## 💻 Como compilar e executar

É necessário ter um compilador C, como o GCC, instalado e configurado.

Considerando que o arquivo principal esteja nomeado como `biblioteca_v6.c`, compile com:

```bash
gcc biblioteca_v6.c -o biblioteca
```

No Windows, execute:

```bash
biblioteca.exe
```

No Linux, execute:

```bash
./biblioteca
```

Para compilar outra versão, substitua `biblioteca_v6.c` pelo nome do arquivo correspondente.

## 📁 Estrutura dos arquivos

A organização proposta para as seis versões é:

```text
sistema-biblioteca-c/
├── biblioteca_v1.c
├── biblioteca_v2.c
├── biblioteca_v3.c
├── biblioteca_v4.c
├── biblioteca_v5.c
├── biblioteca_v6.c
├── README.md
└── .gitignore
```

Cada arquivo representa uma etapa do desenvolvimento e preserva a evolução do sistema ao longo da atividade.

## 🧪 Testes e validações

O roteiro da atividade prevê testes para verificar:

- Cadastro de códigos válidos e rejeição de duplicados.
- Busca de livros existentes e inexistentes.
- Cálculo correto do estoque total.
- Tratamento de estoques iguais a zero e negativos.
- Associação correta entre livros e suas informações.
- Rejeição de empréstimos sem estoque disponível.
- Bloqueio de empréstimos adicionais para usuários ocupados.
- Atualização correta do estoque durante empréstimos e devoluções.
- Preservação dos dados após operações inválidas.

A conclusão de cada versão depende da compilação, da execução correta e da aprovação dos testes correspondentes.

## 🚀 Possíveis melhorias futuras

Como proposta de continuidade, o sistema poderá evoluir com:

- Armazenamento permanente em arquivos.
- Ampliação da capacidade de livros e usuários.
- Pesquisa por título e autor.
- Histórico de empréstimos e devoluções.
- Datas de empréstimo e prazo para devolução.
- Relatórios do acervo e dos empréstimos.

Essas melhorias são sugestões para versões futuras, não funcionalidades garantidas pela atividade atual.

## 👨‍💻 Autor

**Leandro Nascimento Lucatelli**

Projeto acadêmico desenvolvido para praticar os fundamentos da linguagem C e aprofundar os conhecimentos em algoritmos e lógica de programação.

---

<div align="center">

**Desenvolvido em C | Algoritmos e Lógica de Programação**

*Aprendizado contínuo, uma versão de cada vez.*

</div>
