# Minishell - 42 School Project

![Minishell](https://img.shields.io/badge/42-Minishell-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-GPLv3-green?style=for-the-badge)

# 🐚 Minishell – 42 School Project

The **Minishell** project was developed as part of the [42 School](https://www.42sp.org.br/) curriculum, with the goal of recreating a minimalist shell in C.  
It aims to reproduce the essential functionalities of a Unix command interpreter, including **process execution**, **redirections**, **pipes**, **environment variables**, and **built-in commands**, while adhering to the school’s standards of good practices and modular design.

This project was a collaboration between me (**Jefferson Ferreira**) and **[João Vitor](https://github.com/joaolive)**, combining efforts to structure, implement, and document each module in a clear and efficient way.

---

- [Project structure](#project-structure)

## 📁 Project Structure 

The **Minishell** project follows a modular "Flat Approach" architecture, which is ideal for small C projects. Each folder encapsulates a specific responsibility, promoting clarity, maintainability, and compliance with the 42 School standards.

Below is a detailed explanation of each folder and file, following the structure of the mandatory part:

```
├── includes
│   ├── ast.h
│   ├── built_in.h
│   ├── executor.h
│   ├── expander.h
│   ├── hash_table.h
│   ├── lexer.h
│   ├── minishell.h
│   ├── signals.h
│   ├── str.h
│   └── utils.h
├── lib
│   └── libft
│       ├── include
│       │   └── libft.h
│       ├── src
│       └── libft.a
├── objs
├── src
│   ├── built_in
│   │   ├── cd.c
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── export.c
│   │   ├── pwd.c
│   │   ├── set.c
│   │   ├── set_export.c
│   │   └── unset.c
│   ├── executor
│   │   ├── heredoc
│   │   │   ├── del_heredoc_files.c
│   │   │   ├── gen_filename.c
│   │   │   ├── handle_traveler_and.c
│   │   │   ├── handle_traveler_cmd.c
│   │   │   ├── handle_traveler_list.c
│   │   │   ├── handle_traveler_or.c
│   │   │   ├── handle_traveler_pipe.c
│   │   │   ├── handle_traveler_subshell.c
│   │   │   └── traveler_handler.c
│   │   ├── utils
│   │   │   ├── child_task.c
│   │   │   ├── convert_env_to_array.c
│   │   │   ├── fake_expander.c
│   │   │   ├── find_command_path.c
│   │   │   ├── parent_wait_task.c
│   │   │   └── print_error.c
│   │   ├── executor.c
│   │   ├── executor_utils.c
│   │   ├── handle_exec_and.c
│   │   ├── handle_exec_cmd.c
│   │   ├── handle_exec_list.c
│   │   ├── handle_exec_or.c
│   │   ├── handle_exec_pipe.c
│   │   └── handle_exec_subshell.c
│   ├── expander
│   │   ├── expander.c
│   │   ├── expander_core.c
│   │   ├── expander_core_vars.c
│   │   ├── expander_utils.c
│   │   ├── expander_wildcard.c
│   │   ├── expander_wildcard_sort.c
│   │   └── expander_wildcard_utils.c
│   ├── lexer
│   │   ├── lexer.c
│   │   ├── lexer_handler.c
│   │   ├── lexer_handler_kind.c
│   │   └── lexer_utils.c
│   ├── parser
│   │   ├── constructors.c
│   │   ├── destructors.c
│   │   ├── parse_and_or.c
│   │   ├── parse_cmd_list.c
│   │   ├── parse_pipeline.c
│   │   ├── parse_primary.c
│   │   ├── parse_simple_cmd.c
│   │   └── parser_utils.c
│   ├── utils
│   │   ├── export_utils.c
│   │   ├── free_utils.c
│   │   ├── hash_table.c
│   │   ├── hash_table_utils.c
│   │   ├── setup_utils.c
│   │   ├── str.c
│   │   ├── str_utils.c
│   │   └── utils.c
│   ├── main.c
│   └── signals.c
├── .gitignore
├── .gitmodules
├── LICENSE
├── Makefile
├── README.md
└── readline.sup
```

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


## Usage

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Ferreira-Jefferson/minishell
   cd minishell
   git clone --recursive git@github.com:joaolive/libftx.git
   ```

2. **Compile the project:**
   ```bash
   make
   ```

3. **Run the program:**
   ```bash
   ./minishell 
   ```

   ```
   ./minishell -c ls
   ```

## Compiling

- To compile the project:
  ```bash
  make
  ```

- To compile with bonus:
  ```bash
  make bonus
  ```

- To clean object files:
  ```bash
  make clean
  ```

- To remove all binaries:
  ```bash
  make fclean
  ```

- To recompile from scratch:
  ```bash
  make re
  ```

## License

This project is licensed under the GNU GENERAL PUBLIC License. See the [LICENSE](LICENSE) file for details.

---

*Project developed as part of the 42*