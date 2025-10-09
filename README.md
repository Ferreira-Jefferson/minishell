# Minishell - 42 School Project

![Minishell](https://img.shields.io/badge/42-Minishell-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-GPLv3-green?style=for-the-badge)

- [Project structure](#project-structure)

## Project structure

The Minishell project structure should follow the modularly organized "Flat Approach" standard, according to best practices for small C projects, prioritizing the separation of responsibilities (Lexer, Parser, Executor, Built-ins) to ensure compliance with the **Standard** and maintainability.

Below is the directory structure for the **Mandatory Part**, detailing the function of each main file:

```
.
├── libft/                   # Biblioteca Pessoal (Libft)
│   ├── src/
│   ├── include/
│   └── Makefile
│
├── include/
│   ├── minishell.h          # Header principal e inclusões.
│   ├── structs.h            # Definição das estruturas principais (Token, AST - Tagged Union).
│   ├── parser.h
│   ├── executor.h
│   ├── builtins.h
│   ├── expander.h
│   └── memory.h             # Protótipos para liberação da AST e outras estruturas.
│
├── src/
│   ├── main.c
│   ├── signals.c
│
│   ├── lexer/
│   │   ├── tokenizer.c      # Tokenização da entrada em tokens brutos.
│   │   └── quoting.c        # Lógica de aspas (', ") durante a tokenização [2].
│
│   ├── parser/
│   │   ├── ast_builder.c    # Constrói a AST a partir dos tokens [3-5].
│   │   └── struct_init.c    # Funções de alocação de nós da AST (usando malloc) [6].
│
│   ├── expander/
│   │   ├── variable_exp.c   # Expansão de $VAR e $? [7].
│   │   └── quote_removal.c  # Remoção de aspas após expansão [8].
│
│   ├── execution/
│   │   ├── executor.c
│   │   ├── process_mgmt.c   # Gerenciamento de fork, execve, waitpid [1].
│   │   └── search_path.c    # Lógica de busca de binários usando PATH e access [1, 9].
│
│   ├── io/
│   │   ├── io_redirect.c
│   │   ├── io_pipe.c
│   │   └── here_doc.c       # Implementação de << (here-document) [7].
│	│
│   └── builtins/              # Comandos built-in
│       ├── b_cd.c
│       ├── b_echo.c
│       ├── b_exit.c
│       ├── b_export.c
│       ├── b_pwd.c
│       └── b_unset.c
│
│   └── utils/
│       ├── env_hash.c       # **Implementação Customizada de Hash Table para ambiente** [10].
│       └── dynamic_string.c # **Funções Customizadas de Buffer/String Dinâmica** (substituindo SDS).
│
└── Makefile

```