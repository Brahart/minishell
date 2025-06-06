# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 17:29:24 by oelleaum          #+#    #+#              #
#    Updated: 2025/06/04 23:44:37 by asinsard         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BOLD_GREEN			=	\e[1;32m
BOLD_RED			=	\e[1;31m
BOLD_BLUE			=	\e[1;34m
BOLD_YELLOW			=	\e[1;33m
BOLD_PURPLE			=	\e[1;35m
BOLD_CYAN			=	\e[1;36m
STOP_COLOR			=	\e[0m


DIR_EXEC			=	src/ \
						src/exec \
						src/builtins \
						src/builtins/builtins_utils \
						src/exec/exec_utils \
						src/init \
						src/misc \
						src/builtins \
						src/signals \
						src/env

DIR_PARSING			=	src/parsing \
						src/parsing/expand \
						src/parsing/quote \
						src/parsing/here_doc \
						src/parsing/lexer \
						src/parsing/token \
						src/parsing/quote \
						src/parsing/tree \
						src/parsing/wildcard

vpath %.c $(DIR_EXEC) $(DIR_PARSING) 
vpath %.h include include/parsing include/exec include/init include/misc src/libft/include include/builtins include/misc
vpath %.a src/libft/obj

CC					=	cc
FLAGS				=	-Wall -Wextra -Werror -g3 -MMD -MP -I$(LIBFT_HEAD_DIR) $(INC_HEAD)
NAME				=	minishell

HEAD				=	misc/display.h $(HEAD_EXEC)

HEAD_DIR			=	include

INC_HEAD			=	-I$(HEAD_DIR) -I$(HEAD_DIR)/parsing -I$(HEAD_DIR)/exec -I$(HEAD_DIR)/init -I$(HEAD_DIR)/misc -I$(HEAD_DIR)/builtins 

LIBFT_DIR			=	libft
LIBFT_HEAD_DIR		=	$(LIBFT_DIR)/include
LIB_LIBFT			=	$(LIBFT_DIR)/obj/libft.a
LIBFT_FLAG			=	-L$(LIBFT_DIR)/src/ $(LIB_LIBFT)

SRC					=	main.c \
						delete_useless_space.c \
						expand_utils.c \
						expand.c \
						handle_space.c \
						handle_space_utils.c \
						init_expand.c \
						quote_utils.c \
						quote.c \
						create_here_doc.c \
						handle_here_doc_utils.c \
						here_doc_fork_and_signals_utils.c \
						handle_here_doc.c \
						lexer_utils.c \
						lexer.c \
						concat_args_utils.c \
						concat_args.c \
						handle_cmd_and_path_utils.c \
						handle_cmd_and_path.c \
						handle_utils.c \
						join_token.c \
						new_parse.c \
						settings_syntax_error.c \
						syntax_error_utils.c \
						syntax_error.c \
						token_utils.c \
						tokenize_utils.c \
						tokenize.c \
						create_tokenize_list.c \
						create_tree.c \
						handle_boolop_group_utils.c \
						handle_boolop_group.c \
						handle_parenthesis_utils.c \
						handle_parenthesis.c \
						tree_utils.c \
						display_lexer.c \
						display_list.c \
						display_tree.c \
						handle_wildcard_utils.c \
						handle_wildcard.c \
						infix.c \
						joker.c \
						prefix.c \
						suffix.c \
						wildcard_utils.c \
						parser.c \
					init.c \
					src/signals/signals.c \
					src/signals/signals_here_doc.c \
					src/signals/signals_setup.c \
					exec.c \
					exec_pipe.c \
					exec_pipe_parent_child.c \
					exec_cmd.c \
					exec_cmd_utils.c \
					redirect_stdio.c \
					exec_boolops.c \
					misc/errors.c \
    				builtins/echo.c \
    				builtins/cd.c \
    				builtins/pwd.c \
    				builtins/unset.c \
    				builtins/export.c \
    				builtins/env.c \
    				builtins/exit.c \
					redirections_stdio_utils.c \
					pipe_utils.c \
					builtins/builtins_utils/export_utils.c \
					builtins/builtins_utils/builtins_utils.c \
					builtins/builtins_utils/cd_utils.c \
					builtins/builtins_utils/echo_utils.c \
					builtins/builtins_utils/exit_utils.c \
					src/env/env_utils.c \
					src/env/add_or_update_var.c \
					src/env/update_env.c \
					src/env/update_var.c \
					src/misc/free_fcts.c \
					init_env_utils.c \
					init_utils.c \
					init_env.c \
					init_pwd.c \
					init_lists.c \
					add_back_var.c \
					prints.c \
					prints_bis.c \
					print_sorted_env_utils.c \
					misc.c \
					malloc_error.c \
					malloc_error_bis.c 


DEPS				=	$(SRC:%.c=$(OBJ_DIR)%.d)
OBJ					=	$(SRC:%.c=$(OBJ_DIR)%.o)
OBJ_DIR				=	.objs/

all: lib $(NAME)

$(OBJ_DIR)%.o:%.c Makefile
	@mkdir -p $(@D) 
	@echo "$(BOLD_YELLOW)Compilling" $@ "$(BOLD_PURPLE)"
	@$(CC) $(FLAGS) -c $< -o $@
	@echo -n "$(STOP_COLOR)"

debug:
	@echo "				$(BOLD_BLUE)DEBUG"
	@echo "$(STOP_COLOR)"
	@make re --no-print-directory FLAGS="$(FLAGS) -DDEBUG=1"

lib:
	@echo "$(BOLD_BLUE)Compilling Libft...$(STOP_COLOR)"
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(BOLD_GREEN)SUCCESS !!!$(STOP_COLOR)"

$(NAME): $(OBJ) $(LIB_LIBFT)
	@echo "$(BOLD_BLUE)Creating executable $(NAME)...$(BOLD_PURPLE)"
	$(CC) $(OBJ) "-DDEBUG=0" $(LIBFT_FLAG) -l readline -o $(NAME) 
	@echo "$(STOP_COLOR)$(BOLD_GREEN)SUCCESS !!!$(STOP_COLOR)"


clean:
	@echo "$(BOLD_BLUE)Delete obj...$(STOP_COLOR)"
	@make clean --no-print-directory -sC $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(BOLD_RED)SUCCESS !!!$(STOP_COLOR)"

fclean: clean
	@echo "$(BOLD_BLUE)Make fclean...$(STOP_COLOR)"
	@rm -f $(LIB_LIBFT) $(NAME) $(BONUS) here_doc
	@echo "$(BOLD_RED)SUCCESS !!!$(STOP_COLOR)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re debug lib
