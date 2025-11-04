NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

OBJ_DIR	 = objs
SRC_DIR	 = src
UTILS_DIR   = $(SRC_DIR)/utils
LEXER_DIR   = $(SRC_DIR)/lexer
PARSER_DIR   = $(SRC_DIR)/parser
EXPANDER_DIR   = $(SRC_DIR)/expander
BUILT_IN_DIR   = $(SRC_DIR)/built_in

LIB_DIR	 = lib/libft
INCLUDES	= includes

LIBFT	   = $(LIB_DIR)/libft.a

INCLUDE_DIRS = -I$(INCLUDES) -I$(LIB_DIR)

MANDATORY_SRC = main.c signals.c
UTILS_SRC	  = str.c str_utils.c hash_table.c hash_table_utils.c utils.c
LEXER_SRC	  = lexer_utils.c lexer.c lexer_handler.c
PARSER_SRC = constructors.c destructors.c parse_and_or.c parse_cmd_list.c parse_pipeline.c parse_primary.c parse_simple_cmd.c parser_utils.c
EXPANDER_SRC  = expander.c expander_utils.c expander_core.c expander_wildcard.c expander_wildcard_utils.c
BUILT_IN_SRC  = env_built_in.c

MANDATORY_SRC_FULL = $(addprefix $(SRC_DIR)/, $(MANDATORY_SRC))
UTILS_SRC_FULL	 = $(addprefix $(UTILS_DIR)/, $(UTILS_SRC))
LEXER_SRC_FULL	  = $(addprefix $(LEXER_DIR)/, $(LEXER_SRC))
PARSER_SRC_FULL	  = $(addprefix $(PARSER_DIR)/, $(PARSER_SRC))
EXPANDER_SRC_FULL = $(addprefix $(EXPANDER_DIR)/, $(EXPANDER_SRC))
BUILT_IN_SRC_FULL = $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRC))

MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(MANDATORY_SRC_FULL:.c=.o)))
UTILS_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(UTILS_SRC_FULL:.c=.o)))
LEXER_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(LEXER_SRC_FULL:.c=.o)))
PARSER_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(PARSER_SRC_FULL:.c=.o)))
EXPANDER_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(EXPANDER_SRC_FULL:.c=.o)))
BUILT_IN_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(BUILT_IN_SRC_FULL:.c=.o)))

vpath %.c $(SRC_DIR) $(UTILS_DIR) $(LEXER_DIR) $(PARSER_DIR) $(EXPANDER_DIR) $(BUILT_IN_DIR)
OBJS = $(MANDATORY_OBJ) $(UTILS_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(EXPANDER_OBJ) $(BUILT_IN_OBJ)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $(OBJS) -L$(LIB_DIR) -lft -lreadline

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXPANDER_DIR)/%.c 
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)

re: fclean all

run: all
	valgrind --suppressions=readline.sup --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all clean fclean re run
