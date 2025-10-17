# tests/Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Diretórios
SRC_DIR = ..
OBJ_DIR = objs
INCLUDES = -I$(SRC_DIR)/includes -I$(SRC_DIR)/libft -I$(HOME)/.local/include
LIBFT = $(SRC_DIR)/libft/libft.a
LDLIBS = -L$(HOME)/.local/lib -lcheck

# Fontes de teste
TEST_NAME = test_check
TEST_SRC = test_check.c utils/str_test.c
TEST_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRC:.c=.o)))

# Fontes reais do projeto
UTILS_SRC = $(SRC_DIR)/utils/str.c $(SRC_DIR)/utils/str_utils.c

# Regras
test: $(LIBFT) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_OBJS) $(UTILS_SRC) $(LIBFT) -o $(TEST_NAME) $(LDLIBS)
	@echo
	@echo
	@LD_LIBRARY_PATH=$(HOME)/.local/lib ./$(TEST_NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: utils/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TEST_NAME)

.PHONY: test clean
