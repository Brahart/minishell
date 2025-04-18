BOLD_GREEN			=	\e[1;32m
BOLD_RED			=	\e[1;31m
BOLD_BLUE			=	\e[1;34m
BOLD_YELLOW			=	\e[1;33m
BOLD_PURPLE			=	\e[1;35m
BOLD_CYAN			=	\e[1;36m
STOP_COLOR			=	\e[0m

-include $(DEPS) $(DEPS_BONUS)
vpath %.c src/parsing/token:src/parsing/lexer:src/parsing/tree:src:src/parsing/handle_quote
vpath %.h include:src/libft/include
vpath %.a src/libft/obj

CC					=	cc
FLAG				=	-Wall -Wextra -Werror -g -MMD -MP -I$(LIBFT_HEAD_DIR) -I$(HEAD_DIR)
NAME				=	parsing
HEAD				=	token.h list.h display.h lexer.h
HEAD_DIR			=	include/

LIBFT_DIR			=	src/libft/
LIBFT_HEAD_DIR		=	src/libft/include/
LIB_LIBFT			=	$(LIBFT_DIR)obj/libft.a
LIBFT_FLAG			=	-L$(LIBFT_DIR)src/ $(LIB_LIBFT)
LIBFT_HEAD			=	libft.h get_next_line.h ft_printf.h

SRC					=	concat_args.c \
						create_tokenize_list.c \
						create_tree.c \
						display_list.c \
						display_tree.c \
						handle_cmd_and_path_utils.c \
						handle_cmd_and_path.c \
						quote.c \
						tokenize_utils.c \
						tokenize.c \
						tree_utils.c \
						lexer.c \
						main.c

DEPS				=	$(SRC:%.c=$(OBJ_DIR)%.d)
OBJ					=	$(SRC:%.c=$(OBJ_DIR)%.o)
OBJ_DIR				=	.objs/

$(OBJ_DIR)%.o:%.c $(HEAD) $(LIBFT_HEAD) Makefile $(LIBFT_DIR)Makefile
	@mkdir -p $(OBJ_DIR)
	@echo "$(BOLD_PURPLE)"
	$(CC) $(FLAG) -c $< -o $@
	@echo "$(STOP_COLOR)"

all: lib $(NAME)

lib:
	@echo "$(BOLD_BLUE)Compilling Libft...$(STOP_COLOR)"
	@make -C $(LIBFT_DIR)
	@echo "$(BOLD_GREEN)SUCCESS !!!$(STOP_COLOR)"

$(NAME): $(OBJ) $(LIB_LIBFT)
	@echo "$(BOLD_BLUE)Creating executable $(NAME)...$(BOLD_PURPLE)"
	$(CC) $(OBJ) $(PIPEX_FLAG) $(LIBFT_FLAG) -o $(NAME)
	@echo "$(STOP_COLOR)$(BOLD_GREEN)SUCCESS !!!$(STOP_COLOR)"

clean:
	@echo "$(BOLD_BLUE)Delete obj...$(STOP_COLOR)"
	@make clean -sC $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(BOLD_RED)SUCCESS !!!$(STOP_COLOR)"

fclean: clean
	@echo "$(BOLD_BLUE)Make fclean...$(STOP_COLOR)"
	@rm -f $(LIB_LIBFT) $(NAME) $(BONUS) here_doc
	@echo "$(BOLD_RED)SUCCESS !!!$(STOP_COLOR)"

re: fclean all

.PHONY: all clean fclean re bonus