NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

OBJ_DIR	 = objs
SRC_DIR	 = src
UTILS_DIR   = utils
LIB_DIR	 = lib/libftx
INCLUDES	= includes

LIBFT	   = $(LIB_DIR)/libft.a

INCLUDE_DIRS = -I$(INCLUDES) -I$(LIB_DIR)

MANDATORY_SRC = main.c
UTILS_SRC	 = str.c str_utils.c hash_table.c hash_table_utils.c

MANDATORY_SRC_FULL = $(addprefix $(SRC_DIR)/, $(MANDATORY_SRC))
UTILS_SRC_FULL	 = $(addprefix $(UTILS_DIR)/, $(UTILS_SRC))

MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(MANDATORY_SRC_FULL:.c=.o)))
UTILS_OBJ	 = $(addprefix $(OBJ_DIR)/, $(notdir $(UTILS_SRC_FULL:.c=.o)))

OBJS = $(MANDATORY_OBJ) $(UTILS_OBJ)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $(OBJS) -L$(LIB_DIR) -lft

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re
