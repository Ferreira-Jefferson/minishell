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

## 🧪 Testing

For unit testing, we chose the Check framework — a lightweight and powerful C testing library. It offers a clean syntax, signal handling, and test isolation, making it ideal for low-level projects like this one.

Since 42's environment doesn't allow sudo access for system-wide installations, we opted for a manual setup ("root-style") by compiling Check from source and installing it locally within the project directory. This approach ensures portability and independence from system-level constraints.

---

## ✅ Local Installation of Check (without `sudo`)

```bash
git clone https://github.com/libcheck/check.git
cd check
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local ..
make
make install

cd ..
cp check/src/check.h.in check.h
# remove include with error and @ errors

rm -rf check
```

## 🧪 Simple Test: `test_check.c`

Create a file named `test_check.c` with the following content:

```c
#include <check.h>

START_TEST(test_example) {
    ck_assert_int_eq(2 + 2, 4);
}
END_TEST

Suite *suite(void) {
    Suite *s = suite_create("Example");
    TCase *tc = tcase_create("Core");
    tcase_add_test(tc, test_example);
    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
    SRunner *sr = srunner_create(suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
    return 0;
}
```

## Run Makefile: 

```bash
make test
```

With this setup, you can test C functions using the **Check** framework — even without administrative privileges. Let me know if you'd like to add examples for testing threads, signals, or subprocesses too!

---