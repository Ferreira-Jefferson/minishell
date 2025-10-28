#include "ast.h"
#include <stdlib.h>
#include <string.h>

// Funções auxiliares para criar nós
/*
NK_LIST
├── NK_OR
│   ├── NK_SUBSHELL
│   │   └── NK_AND
│   │       ├── NK_COMMAND: echo "Hello $USER"
│   │       └── NK_PIPE
│   │           ├── NK_COMMAND: cat file.txt
│   │           └── NK_COMMAND: grep 'pattern' > output.txt
│   └── NK_SUBSHELL
│       └── NK_AND
│           ├── NK_AND
│           │   ├── NK_COMMAND: ls -la "$HOME"
│           │   └── NK_COMMAND: echo 'Single quotes'
│           └── NK_COMMAND: printf "Mix\"ed\" qu'ot'es"
└── NK_AND
    ├── NK_AND
    │   ├── NK_AND
    │   │   ├── NK_COMMAND: export VAR="value with spaces"
    │   │   └── NK_PIPE
    │   │       ├── NK_COMMAND: echo $VAR
    │   │       └── NK_COMMAND: tr 'a-z' 'A-Z' >> result.txt
    │   └── NK_PIPE
    │       ├── NK_COMMAND: cat << EOF
    │       └── NK_COMMAND: wc -l
    └── NK_AND
        ├── NK_COMMAND: echo "Escape: \$VAR \\ \n \t"
        └── NK_SUBSHELL
            └── NK_AND
                ├── NK_OR
                │   ├── NK_AND
                │   │   ├── NK_COMMAND: pwd
                │   │   └── NK_COMMAND: cd /tmp
                │   └── NK_COMMAND: echo "Failed"
                └── NK_COMMAND: ls *.txt 2>&1

*/
static t_cmd_node *create_cmd_node(void)
{
    t_cmd_node *node = malloc(sizeof(t_cmd_node));
    if (!node)
        return (NULL);
    node->base.kind = NK_COMMAND;
    node->args = ft_dlstinit();
    node->redirections = ft_dlstinit();
    if (!node->args || !node->redirections)
    {
        if (node->args)
            ft_dlstdestroy(&node->args, free);
        if (node->redirections)
            ft_dlstdestroy(&node->redirections, free);
        free(node);
        return (NULL);
    }
    return (node);
}

static t_bin_node *create_bin_node(t_node_kind kind, t_node *left, t_node *right)
{
    t_bin_node *node = malloc(sizeof(t_bin_node));
    if (!node)
        return (NULL);
    node->base.kind = kind;
    node->left = left;
    node->right = right;
    return (node);
}

static t_pipe_node *create_pipe_node(void)
{
    t_pipe_node *node = malloc(sizeof(t_pipe_node));
    if (!node)
        return (NULL);
    node->base.kind = NK_PIPE;
    node->commands = ft_dlstinit();
    if (!node->commands)
    {
        free(node);
        return (NULL);
    }
    return (node);
}

static t_sub_node *create_sub_node(t_node *sub_ast)
{
    t_sub_node *node = malloc(sizeof(t_sub_node));
    if (!node)
        return (NULL);
    node->base.kind = NK_SUBSHELL;
    node->sub_ast = sub_ast;
    return (node);
}

static t_redir *create_redir(t_redir_kind kind, const char *filename, int target_fd)
{
    t_redir *redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->kind = kind;
    redir->filename = strdup(filename);
    if (!redir->filename)
    {
        free(redir);
        return (NULL);
    }
    redir->target_fd = target_fd;
    return (redir);
}

// Função auxiliar para adicionar argumento ao comando
static int add_arg(t_cmd_node *cmd, const char *arg)
{
    char *arg_copy = strdup(arg);
    if (!arg_copy)
        return (0);
    
    if (ft_dlstpush_back(cmd->args, arg_copy) != 0)
    {
        free(arg_copy);
        return (0);
    }
    return (1);
}

// Função auxiliar para adicionar redirecionamento
static int add_redir(t_cmd_node *cmd, t_redir *redir)
{
    if (!redir)
        return (0);
    
    if (ft_dlstpush_back(cmd->redirections, redir) != 0)
        return (0);
    
    return (1);
}

// Função auxiliar para adicionar comando ao pipe
static int add_cmd_to_pipe(t_pipe_node *pipe, t_cmd_node *cmd)
{
    if (!cmd)
        return (0);
    
    if (ft_dlstpush_back(pipe->commands, cmd) != 0)
        return (0);
    
    return (1);
}

/**
 * @brief Cria uma AST complexa para testes do minishell
 * 
 * Representa o seguinte comando complexo:
 * (echo "Hello $USER" && cat file.txt | grep 'pattern' > output.txt) || \
 * (ls -la "$HOME" && echo 'Single quotes' && printf "Mix\"ed\" qu'ot'es") ; \
 * export VAR="value with spaces" && echo $VAR | tr 'a-z' 'A-Z' >> result.txt && \
 * cat << EOF | wc -l && echo "Escape: \$VAR \\ \n \t" && \
 * (pwd && cd /tmp || echo "Failed" && ls *.txt 2>&1)
 * 
 * @return t_node* Ponteiro para a raiz da AST (NULL em caso de erro)
 */
t_node *create_complex_test_ast(void)
{
    // ========== PARTE 1: (echo "Hello $USER" && cat file.txt | grep 'pattern' > output.txt) ==========
    // Comando: echo "Hello $USER"
    t_cmd_node *echo1 = create_cmd_node();
    if (!echo1)
        return (NULL);
    add_arg(echo1, "echo");
    add_arg(echo1, "Hello $USER");  // Aspas duplas - expansão de variável
    
    // Comando: cat file.txt
    t_cmd_node *cat1 = create_cmd_node();
    if (!cat1)
        return (NULL);
    add_arg(cat1, "cat");
    add_arg(cat1, "file.txt");
    
    // Comando: grep 'pattern' > output.txt
    t_cmd_node *grep1 = create_cmd_node();
    if (!grep1)
        return (NULL);
    add_arg(grep1, "grep");
    add_arg(grep1, "pattern");  // Aspas simples - sem expansão
    add_redir(grep1, create_redir(RK_OUTPUT, "output.txt", 1));
    
    // Pipe: cat | grep
    t_pipe_node *pipe1 = create_pipe_node();
    if (!pipe1)
        return (NULL);
    add_cmd_to_pipe(pipe1, cat1);
    add_cmd_to_pipe(pipe1, grep1);
    
    // AND: echo && (cat | grep)
    t_bin_node *and1 = create_bin_node(NK_AND, (t_node *)echo1, (t_node *)pipe1);
    if (!and1)
        return (NULL);
    
    // Subshell da primeira parte
    t_sub_node *sub1 = create_sub_node((t_node *)and1);
    if (!sub1)
        return (NULL);
    
    // ========== PARTE 2: (ls -la "$HOME" && echo 'Single quotes' && printf "Mix\"ed\" qu'ot'es") ==========
    
    // Comando: ls -la "$HOME"
    t_cmd_node *ls1 = create_cmd_node();
    if (!ls1)
        return (NULL);
    add_arg(ls1, "ls");
    add_arg(ls1, "-la");
    add_arg(ls1, "$HOME");  // Expansão de variável entre aspas
    
    // Comando: echo 'Single quotes'
    t_cmd_node *echo2 = create_cmd_node();
    if (!echo2)
        return (NULL);
    add_arg(echo2, "echo");
    add_arg(echo2, "Single quotes");  // Aspas simples
    
    // Comando: printf "Mix\"ed\" qu'ot'es"
    t_cmd_node *printf1 = create_cmd_node();
    if (!printf1)
        return (NULL);
    add_arg(printf1, "printf");
    add_arg(printf1, "Mix\"ed\" qu'ot'es");  // Aspas mistas e escapadas
    
    // AND: ls && echo
    t_bin_node *and2 = create_bin_node(NK_AND, (t_node *)ls1, (t_node *)echo2);
    if (!and2)
        return (NULL);
    
    // AND: (ls && echo) && printf
    t_bin_node *and3 = create_bin_node(NK_AND, (t_node *)and2, (t_node *)printf1);
    if (!and3)
        return (NULL);
    
    // Subshell da segunda parte
    t_sub_node *sub2 = create_sub_node((t_node *)and3);
    if (!sub2)
        return (NULL);
    
    // OR: sub1 || sub2
    t_bin_node *or1 = create_bin_node(NK_OR, (t_node *)sub1, (t_node *)sub2);
    if (!or1)
        return (NULL);
    
    // ========== PARTE 3: export VAR="value with spaces" && echo $VAR | tr 'a-z' 'A-Z' >> result.txt ==========
    
    // Comando: export VAR="value with spaces"
    t_cmd_node *export1 = create_cmd_node();
    if (!export1)
        return (NULL);
    add_arg(export1, "export");
    add_arg(export1, "VAR=value with spaces");  // Variável com espaços
    
    // Comando: echo $VAR
    t_cmd_node *echo3 = create_cmd_node();
    if (!echo3)
        return (NULL);
    add_arg(echo3, "echo");
    add_arg(echo3, "$VAR");  // Expansão de variável
    
    // Comando: tr 'a-z' 'A-Z' >> result.txt
    t_cmd_node *tr1 = create_cmd_node();
    if (!tr1)
        return (NULL);
    add_arg(tr1, "tr");
    add_arg(tr1, "a-z");
    add_arg(tr1, "A-Z");
    add_redir(tr1, create_redir(RK_APPEND, "result.txt", 1));
    
    // Pipe: echo | tr
    t_pipe_node *pipe2 = create_pipe_node();
    if (!pipe2)
        return (NULL);
    add_cmd_to_pipe(pipe2, echo3);
    add_cmd_to_pipe(pipe2, tr1);
    
    // AND: export && (echo | tr)
    t_bin_node *and4 = create_bin_node(NK_AND, (t_node *)export1, (t_node *)pipe2);
    if (!and4)
        return (NULL);
    
    // ========== PARTE 4: cat << EOF | wc -l ==========
    
    // Comando: cat << EOF
    t_cmd_node *cat2 = create_cmd_node();
    if (!cat2)
        return (NULL);
    add_arg(cat2, "cat");
    add_redir(cat2, create_redir(RK_HEREDOC, "EOF", 0));
    
    // Comando: wc -l
    t_cmd_node *wc1 = create_cmd_node();
    if (!wc1)
        return (NULL);
    add_arg(wc1, "wc");
    add_arg(wc1, "-l");
    
    // Pipe: cat | wc
    t_pipe_node *pipe3 = create_pipe_node();
    if (!pipe3)
        return (NULL);
    add_cmd_to_pipe(pipe3, cat2);
    add_cmd_to_pipe(pipe3, wc1);
    
    // AND: and4 && pipe3
    t_bin_node *and5 = create_bin_node(NK_AND, (t_node *)and4, (t_node *)pipe3);
    if (!and5)
        return (NULL);
    
    // ========== PARTE 5: echo "Escape: \$VAR \\ \n \t" ==========
    
    // Comando: echo "Escape: \$VAR \\ \n \t"
    t_cmd_node *echo4 = create_cmd_node();
    if (!echo4)
        return (NULL);
    add_arg(echo4, "echo");
    add_arg(echo4, "Escape: \\$VAR \\\\ \\n \\t");  // Caracteres escapados
    
    // AND: and5 && echo4
    t_bin_node *and6 = create_bin_node(NK_AND, (t_node *)and5, (t_node *)echo4);
    if (!and6)
        return (NULL);
    
    // ========== PARTE 6: (pwd && cd /tmp || echo "Failed" && ls *.txt 2>&1) ==========
    
    // Comando: pwd
    t_cmd_node *pwd1 = create_cmd_node();
    if (!pwd1)
        return (NULL);
    add_arg(pwd1, "pwd");
    
    // Comando: cd /tmp
    t_cmd_node *cd1 = create_cmd_node();
    if (!cd1)
        return (NULL);
    add_arg(cd1, "cd");
    add_arg(cd1, "/tmp");
    
    // AND: pwd && cd
    t_bin_node *and7 = create_bin_node(NK_AND, (t_node *)pwd1, (t_node *)cd1);
    if (!and7)
        return (NULL);
    
    // Comando: echo "Failed"
    t_cmd_node *echo5 = create_cmd_node();
    if (!echo5)
        return (NULL);
    add_arg(echo5, "echo");
    add_arg(echo5, "Failed");
    
    // OR: (pwd && cd) || echo
    t_bin_node *or2 = create_bin_node(NK_OR, (t_node *)and7, (t_node *)echo5);
    if (!or2)
        return (NULL);
    
    // Comando: ls *.txt 2>&1
    t_cmd_node *ls2 = create_cmd_node();
    if (!ls2)
        return (NULL);
    add_arg(ls2, "ls");
    add_arg(ls2, "*.txt");  // Wildcard
    add_redir(ls2, create_redir(RK_OUTPUT, "&1", 2));  // Redirecionamento 2>&1
    
    // AND: or2 && ls
    t_bin_node *and8 = create_bin_node(NK_AND, (t_node *)or2, (t_node *)ls2);
    if (!and8)
        return (NULL);
    
    // Subshell da última parte
    t_sub_node *sub3 = create_sub_node((t_node *)and8);
    if (!sub3)
        return (NULL);
    
    // AND: and6 && sub3
    t_bin_node *and9 = create_bin_node(NK_AND, (t_node *)and6, (t_node *)sub3);
    if (!and9)
        return (NULL);
    
    // ========== LIST (;): or1 ; and9 ==========
    
    t_bin_node *list = create_bin_node(NK_LIST, (t_node *)or1, (t_node *)and9);
    if (!list)
        return (NULL);
    
    return ((t_node *)list);
}