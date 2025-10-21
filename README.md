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
│   │   └── quoting.c        # Lógica de aspas (', ") durante a tokenização.
│
│   ├── parser/
│   │   ├── ast_builder.c    # Constrói a AST a partir dos tokens.
│   │   └── struct_init.c    # Funções de alocação de nós da AST (usando malloc).
│
│   ├── expander/
│   │   ├── variable_exp.c   # Expansão de $VAR e $?.
│   │   └── quote_removal.c  # Remoção de aspas após expansão.
│
│   ├── execution/
│   │   ├── executor.c
│   │   ├── process_mgmt.c   # Gerenciamento de fork, execve, waitpid.
│   │   └── search_path.c    # Lógica de busca de binários usando PATH e access.
│
│   ├── io/
│   │   ├── io_redirect.c
│   │   ├── io_pipe.c
│   │   └── here_doc.c       # Implementação de << (here-document).
│	│
│   └── builtins/            # Comandos built-in
│       ├── b_cd.c
│       ├── b_echo.c
│       ├── b_exit.c
│       ├── b_export.c
│       ├── b_pwd.c
│       └── b_unset.c
│
│   └── utils/
│       ├── hash_table.c       	# **Implementação Customizada de Hash Table para ambiente** .
│       ├── hash_table_utils.c      
│       ├── str.c  				# **Funções Customizadas de Buffer/String Dinâmica** (substituindo SDS).    
│       └── str_utils.c 
│
└── Makefile

```

## 📁 Project Structure – Detailed Breakdown

The **Minishell** project follows a modular "Flat Approach" architecture, which is ideal for small C projects. Each folder encapsulates a specific responsibility, promoting clarity, maintainability, and compliance with the 42 School standards.

Below is a detailed explanation of each folder and file, following the structure of the mandatory part:


---

### 📚 `libft/` – Personal Utility Library

This folder contains your custom implementation of the **Libft**, a foundational library required by 42 School. It includes:

- `src/`: Source files for utility functions (e.g., `ft_split`, `ft_strdup`, etc.).
- `include/`: Header files for Libft.
- `Makefile`: Build instructions for compiling Libft.

🔗 **Used Throughout**: Libft functions are used across all modules to avoid relying on external libraries.

---

### 📁 `include/` – Header Files

This folder centralizes all header files, organizing prototypes and structure definitions by module:

- `minishell.h`: Main header file that includes all others.
- `structs.h`: Defines core data structures like `Token`, `ASTNode`, and tagged unions.
- `parser.h`, `executor.h`, `builtins.h`, `expander.h`: Module-specific prototypes.
- `memory.h`: Functions for freeing AST and other dynamically allocated structures.

🔗 **Integration**: Ensures consistent interfaces and type definitions across the entire project.

---

### 🧠 `src/` – Core Logic and Modules

This is the heart of the project, containing all source code organized by functionality.

#### 🔧 `main.c` and `signals.c`

- `main.c`: Entry point of the shell. Initializes environment, sets up signal handling, and starts the main loop.
- `signals.c`: Handles Unix signals like `SIGINT` and `SIGQUIT`, ensuring graceful interruption and shell behavior.

🔗 **Integration**: These files coordinate the shell's lifecycle and responsiveness.

---

#### 🔤 `lexer/` – Lexical Analysis

Responsible for breaking the user input into raw tokens.

- `tokenizer.c`: Splits the input string into tokens (words, operators, redirections).
- `quoting.c`: Handles quote logic (`'`, `"`) during tokenization, preserving grouping and escaping rules.

🔗 **Integration**: First step after reading user input. Prepares data for parsing.

---

#### 🧱 `parser/` – Syntax Analysis

Builds an **Abstract Syntax Tree (AST)** from the tokens, representing the logical structure of the command.

- `ast_builder.c`: Constructs the AST based on token types and grammar rules.
- `struct_init.c`: Allocates and initializes AST nodes using `malloc`.

🔗 **Integration**: Converts flat tokens into a tree structure for execution.

---

#### 💬 `expander/` – Variable Expansion

Handles shell variable expansion and quote removal.

- `variable_exp.c`: Expands environment variables like `$USER`, `$?`, etc.
- `quote_removal.c`: Removes quotes after expansion, preparing clean arguments for execution.

🔗 **Integration**: Acts between parsing and execution, transforming the AST into executable form.

---

#### 🚀 `execution/` – Command Execution

Executes commands based on the AST, managing processes and locating binaries.

- `executor.c`: Orchestrates execution of commands and pipelines.
- `process_mgmt.c`: Manages `fork`, `execve`, and `waitpid` for process control.
- `search_path.c`: Searches for executable binaries using the `PATH` environment variable and `access()`.

🔗 **Integration**: Translates AST nodes into actual system calls and process handling.

---

#### 🔄 `io/` – Input/Output Redirection

Handles file redirection, pipes, and here-documents.

- `io_redirect.c`: Implements `<`, `>`, and `>>` redirections.
- `io_pipe.c`: Sets up pipes (`|`) between commands.
- `here_doc.c`: Implements `<<` (here-document), reading input until a delimiter.

🔗 **Integration**: Works closely with the executor to configure file descriptors before command execution.

---

#### 🏠 `builtins/` – Built-in Commands

Implements shell-native commands that do not require external binaries.

- `b_cd.c`: Changes the current working directory.
- `b_echo.c`: Prints arguments to standard output.
- `b_exit.c`: Exits the shell.
- `b_export.c`: Adds/modifies environment variables.
- `b_pwd.c`: Prints the current working directory.
- `b_unset.c`: Removes environment variables.

🔗 **Integration**: The executor checks if a command is built-in and calls these functions directly.

---

#### 🧰 `utils/` – Custom Utilities

You contributed to this module, which provides reusable components for other parts of the shell.

- `env_hash.c`: Implements a **custom hash table** for storing and accessing environment variables efficiently.
- `dynamic_string.c`: Provides a **dynamic string buffer** system, replacing external libraries like SDS.

🔗 **Integration**: Used by the expander, parser, and executor to manage strings and environment data.

---

### 🛠️ `Makefile`

The root `Makefile` compiles all modules and links them into the final executable. It also handles dependencies and builds `libft`.

---

## 🧵 Execution Flow Summary

1. **User Input** → `main.c`
2. **Lexical Analysis** → `lexer/`
3. **Syntax Parsing** → `parser/`
4. **Variable Expansion** → `expander/`
5. **Execution Preparation** → `io/`, `builtins/`, `utils/`
6. **Command Execution** → `execution/`

