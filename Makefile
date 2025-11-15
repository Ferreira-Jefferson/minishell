NAME = minishell
NAME_BONUS = minishell_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SAN_FLAGS = -fsanitize=address,leak,undefined -fno-omit-frame-pointer -fsanitize-address-use-after-scope
ASAN_ENV = ASAN_OPTIONS="detect_leaks=1:halt_on_error=0:verbosity=2:log_path=asan.log" UBSAN_OPTIONS="print_stacktrace=1"

OBJ_DIR	 = objs
SRC_DIR	 = src
UTILS_DIR   = $(SRC_DIR)/utils
LEXER_DIR   = $(SRC_DIR)/lexer
PARSER_DIR   = $(SRC_DIR)/parser
EXPANDER_DIR   = $(SRC_DIR)/expander
BUILT_IN_DIR   = $(SRC_DIR)/built_in
EXECUTOR_DIR   = $(SRC_DIR)/executor
EXECUTOR_UTILS_DIR   = $(EXECUTOR_DIR)/utils
EXECUTOR_HEREDOC_DIR   = $(EXECUTOR_DIR)/heredoc

LIB_DIR	 = lib/libft
INCLUDES	= includes

LIBFT	   = $(LIB_DIR)/libft.a

INCLUDE_DIRS = -I$(INCLUDES) -I$(LIB_DIR)

MANDATORY_SRC = main.c signals.c
UTILS_SRC	  = str.c str_utils.c hash_table.c hash_table_utils.c utils.c export_utils.c setup_utils.c free_utils.c
LEXER_SRC	  = lexer_utils.c lexer.c lexer_handler.c lexer_handler_kind.c
PARSER_SRC = constructors.c destructors.c parse_and_or.c parse_cmd_list.c parse_pipeline.c parse_primary.c parse_simple_cmd.c parser_utils.c
EXPANDER_SRC  = expander.c expander_utils.c expander_core.c expander_wildcard.c expander_wildcard_utils.c expander_core_vars.c expander_wildcard_sort.c
BUILT_IN_SRC  = env.c export.c echo.c unset.c set_export.c cd.c exit.c pwd.c set.c
EXECUTOR_SRC = executor_utils.c executor.c handle_exec_and.c handle_exec_cmd.c handle_exec_list.c handle_exec_or.c \
				handle_exec_pipe.c handle_exec_subshell.c
EXECUTOR_UTILS_SRC =  child_task.c convert_env_to_array.c find_command_path.c parent_wait_task.c print_error.c fake_expander.c
EXECUTOR_HEREDOC_SRC = del_heredoc_files.c gen_filename.c  handle_traveler_and.c handle_traveler_cmd.c handle_traveler_list.c \
						handle_traveler_or.c handle_traveler_pipe.c handle_traveler_subshell.c traveler_handler.c

MANDATORY_SRC_FULL = $(addprefix $(SRC_DIR)/, $(MANDATORY_SRC))
UTILS_SRC_FULL	 = $(addprefix $(UTILS_DIR)/, $(UTILS_SRC))
LEXER_SRC_FULL	  = $(addprefix $(LEXER_DIR)/, $(LEXER_SRC))
PARSER_SRC_FULL	  = $(addprefix $(PARSER_DIR)/, $(PARSER_SRC))
EXPANDER_SRC_FULL = $(addprefix $(EXPANDER_DIR)/, $(EXPANDER_SRC))
BUILT_IN_SRC_FULL = $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRC))
EXECUTOR_SRC_FULL = $(addprefix $(EXECUTOR_DIR)/, $(EXECUTOR_SRC))
EXECUTOR_UTILS_SRC_FULL = $(addprefix $(EXECUTOR_UTILS_DIR)/, $(EXECUTOR_UTILS_SRC))
EXECUTOR_HEREDOC_SRC_FULL = $(addprefix $(EXECUTOR_HEREDOC_DIR)/, $(EXECUTOR_HEREDOC_SRC))

MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(MANDATORY_SRC_FULL:.c=.o)))
UTILS_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(UTILS_SRC_FULL:.c=.o)))
LEXER_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(LEXER_SRC_FULL:.c=.o)))
PARSER_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(PARSER_SRC_FULL:.c=.o)))
EXPANDER_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(EXPANDER_SRC_FULL:.c=.o)))
BUILT_IN_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(BUILT_IN_SRC_FULL:.c=.o)))
EXECUTOR_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(EXECUTOR_SRC_FULL:.c=.o)))
EXECUTOR_UTILS_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(EXECUTOR_UTILS_SRC_FULL:.c=.o)))
EXECUTOR_HEREDOC_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(EXECUTOR_HEREDOC_SRC_FULL:.c=.o)))

vpath %.c $(SRC_DIR) $(UTILS_DIR) $(LEXER_DIR) $(PARSER_DIR) $(EXPANDER_DIR) $(BUILT_IN_DIR) $(EXECUTOR_DIR) $(EXECUTOR_UTILS_DIR) $(EXECUTOR_HEREDOC_DIR)
OBJS = $(MANDATORY_OBJ) $(UTILS_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(EXPANDER_OBJ) $(BUILT_IN_OBJ) $(EXECUTOR_OBJ) $(EXECUTOR_UTILS_OBJ) $(EXECUTOR_HEREDOC_OBJ)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $(OBJS) -L$(LIB_DIR) -lft -lreadline

$(NAME_BONUS): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $(OBJS) -L$(LIB_DIR) -lft -lreadline

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME)_asan
	$(MAKE) fclean -C $(LIB_DIR)

re: fclean all

run: all
	valgrind --suppressions=readline.sup --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell

asan: CFLAGS += $(SAN_FLAGS)
asan: fclean $(NAME)
	@mv $(NAME) $(NAME)_asan
	@echo "\033[1;32m[OK]\033[0m Executando com sanitizers...\n"
	$(ASAN_ENV) ./$(NAME)_asan

.PHONY: all clean fclean re run asan
