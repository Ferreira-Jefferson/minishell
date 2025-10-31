/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/31 11:11:45 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "ast.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * ==================================================================
 * FUNÇÃO DE HOOK
 * ==================================================================
 */

int	ft_event_hook(void)
{
	if (get_g_signal_status() != 0)
	{
		write(1, "^C", 2);
		rl_done = 1;
		reset_g_signal_status();
	}
	return (0);
}

/*
 * ==================================================================
 * FUNÇÃO DE PRINT DE TOKEN
 * ==================================================================
 */

void	print_token(void *content)
{
	t_token *token = (t_token *)content;
	const char *token_kind_names[] = {
		"TK_WORD", "TK_PIPE", "TK_AND", "TK_OR", "TK_LIST",
		"TK_LPAREN", "TK_RPAREN", "TK_REDIR_IN", "TK_REDIR_OUT",
		"TK_HEREDOC", "TK_APPEND", "TK_EOF"
	};
	ft_printf("  Token: Lexeme = [%s], Type = %s\n",
		token->lexeme, token_kind_names[token->kind]);
}

/*
 * ==================================================================
 * FUNÇÕES DE PRINT DA AST (PARA DEBUG)
 * ==================================================================
 */

static void	print_indent(int indent)
{
	int	i = 0;
	while (i < indent)
	{
		printf("  ");
		i++;
	}
}

/**
 * @brief Imprime o conteúdo de um nó de comando simples (args e redirs).
 * * CORREÇÃO: Usa t_dnode em vez de t_dlist_node.
 */
static void	print_simple_cmd(t_cmd_node *node, int indent)
{
	t_dnode			*arg_node; // <-- CORRIGIDO
	t_dnode			*redir_node; // <-- CORRIGIDO
	t_redir			*redir;

	print_indent(indent);
	printf("CMD:\n");
	arg_node = node->args->head;
	while (arg_node)
	{
		print_indent(indent + 1);
		printf("ARG: [%s]\n", (char *)arg_node->content);
		arg_node = arg_node->next;
	}
	redir_node = node->redirections->head;
	while (redir_node)
	{
		redir = (t_redir *)redir_node->content;
		print_indent(indent + 1);
		printf("REDIR (KIND %d) FILE: [%s]\n", redir->kind, redir->filename);
		redir_node = redir_node->next;
	}
}

/**
 * @brief Função recursiva principal para imprimir a AST.
 * * CORREÇÃO: Usa t_dnode em vez de t_dlist_node.
 */
static void	print_ast(t_node *node, int indent)
{
	t_pipe_node	*pipe_node;
	t_bin_node	*bin_node;
	t_sub_node	*sub_node;

	if (!node)
		return ;
	if (node->kind == NK_COMMAND)
		print_simple_cmd((t_cmd_node *)node, indent);
	else if (node->kind == NK_PIPE)
	{
		pipe_node = (t_pipe_node *)node;
		print_indent(indent);
		printf("PIPE:\n");
		t_dnode *cmd_list = pipe_node->commands->head; // <-- CORRIGIDO
		while (cmd_list) {
			print_ast((t_node *)cmd_list->content, indent + 1);
			cmd_list = cmd_list->next;
		}
	}
	else if (node->kind == NK_AND || node->kind == NK_OR || node->kind == NK_LIST)
	{
		bin_node = (t_bin_node *)node;
		print_indent(indent);
		if (node->kind == NK_AND) printf("&&\n");
		if (node->kind == NK_OR) printf("||\n");
		if (node->kind == NK_LIST) printf(";\n");
		print_ast(bin_node->left, indent + 1);
		print_ast(bin_node->right, indent + 1);
	}
	else if (node->kind == NK_SUBSHELL) // Assumindo NK_SUB pela sua ast.h
	{
		sub_node = (t_sub_node *)node;
		print_indent(indent);
		printf("SUB-SHELL:\n");
		print_ast(sub_node->sub_ast, indent + 1);
	}
}

/*
 * ==================================================================
 * MAIN DE TESTE (LEXER + PARSER)
 * ==================================================================
 */

int	main(int argc, char *argv[], char **envp)
{
	t_hash_table    *table;
	char            *input;
	t_dlist         *lst;
	t_node          *ast;
	int             i;

	(void)argc;
	(void)argv;
	setup_signals();
	rl_catch_signals = 0;
	rl_event_hook = ft_event_hook;
	table = env_load(envp);
	while (1)
	{
		input = readline("teste> ");
		if (!input && get_g_signal_status() == 0)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (input && input[0] != '\0') // Verifica se input não é NULL
			add_history(input);

		if (!input) // Se input for NULL (Ctrl+D), saia do loop
			continue;

		// --- 1. LEXER ---
		i = 0;
		lst = tokenize(input, i);
		if (!lst)
		{
			free(input);
			continue;
		}

		// --- 2. PRINT TOKENS ---
		printf("--- TOKENS ---\n");
		ft_dlstiter(lst, print_token);
		printf("--------------\n");

		// --- 3. PARSER ---
		ast = parse_cmd_list(lst);

		// --- 4. PRINT AST ---
		if (!ast)
		{
			printf("Erro de Sintaxe.\n");
		}
		else
		{
			printf("--- AST ---\n");
			print_ast(ast, 0);
			printf("-------------\n");
		}

		// --- 5. LIMPEZA ---
		free(input);
		free_node(ast);
		ft_dlstdestroy(&lst, free_token);
	}
	ht_free(table);
	rl_clear_history();
	return (0);
}

