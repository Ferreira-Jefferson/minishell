NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

OBJ_DIR	 = objs
SRC_DIR	 = src
UTILS_DIR   = $(SRC_DIR)/utils
LEXER_DIR   = $(SRC_DIR)/lexer
EXPANDER_DIR   = $(SRC_DIR)/expander

LIB_DIR	 = lib/libft
INCLUDES	= includes

LIBFT	   = $(LIB_DIR)/libft.a

INCLUDE_DIRS = -I$(INCLUDES) -I$(LIB_DIR)

MANDATORY_SRC = fake.c main.c signals.c
UTILS_SRC	  = str.c str_utils.c hash_table.c hash_table_utils.c utils.c
LEXER_SRC	  = lexer_utils.c lexer.c lexer_handler.c 
EXPANDER_SRC  = expander.c expander_utils.c 

MANDATORY_SRC_FULL = $(addprefix $(SRC_DIR)/, $(MANDATORY_SRC))
UTILS_SRC_FULL	 = $(addprefix $(UTILS_DIR)/, $(UTILS_SRC))
LEXER_SRC_FULL	 = $(addprefix $(LEXER_DIR)/, $(LEXER_SRC))
EXPANDER_SRC_FULL	 = $(addprefix $(EXPANDER_DIR)/, $(EXPANDER_SRC))

MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(MANDATORY_SRC_FULL:.c=.o)))
UTILS_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(UTILS_SRC_FULL:.c=.o)))
LEXER_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(LEXER_SRC_FULL:.c=.o)))
EXPANDER_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(EXPANDER_SRC_FULL:.c=.o)))

OBJS = $(MANDATORY_OBJ) $(UTILS_OBJ) $(LEXER_OBJ) $(EXPANDER_OBJ)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $(OBJS) -L$(LIB_DIR) -lft -lreadline

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c 
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LEXER_DIR)/%.c 
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
