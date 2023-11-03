# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 08:42:40 by lpollini          #+#    #+#              #
#    Updated: 2023/11/04 00:37:41 by lpollini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
	
CC			= cc -g 
FLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

OBJDIR = .objFiles

FILES		= env_stuff executor executor_utils ft_split_1 ft_split_2 ft_split_utils ft_split_utils_1 \
	main main_check main_init pipex_main_helper_1 pipex_main_helper_2 pipex_main_helper_3 pipex_main_helper \
	pipex_main prompt_stuff_export shft_cmds_cd_2 shft_cmds_echo_exit_env_helper shft_cmds_echo_exit_env \
	shft_cmds_export_unset shft_cmds_pwd str_stuff utils_bonus utils_bonus_1 utils_bonus_2 parenthesis_parser_bonus \
	operator_checker_bonus wildcard/parse_bonus parenthesis_bonus wildcard/utils_bonus wildcard/utils_1_bonus \
	new_parentheses_1 new_parentheses_2 new_parentheses_3 new_parentheses_4 new_parentheses utils_1

BONUS_FILES = \


SRC			= $(FILES:=.c)
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER		= minishell.h
LDFLAGS		= -Llibft

BONUS_SRC	= $(BONUS_FILES:=.c)
BONUS_OBJ	= $(addprefix $(OBJDIR)/, $(BONUS_FILES:=.o))

#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m 
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

#Debug 
ifeq ($(DEBUG), 1)
   OPTS = -g -Wall -Wextra -Werror
endif

all: libft $(NAME)

libft:
	$(MAKE) -C libft

bonus: BONUS=true
bonus: libft $(NAME)

ifeq ($(BONUS),true)
$(NAME): $(OBJ) $(BONUS_OBJ) $(HEADER)
	@$(CC) $(OBJ) $(BONUS_OBJ) -lreadline -lft $(OPTS) $(LDFLAGS) -o $(NAME)
	@printf "$(_SUCCESS) $(GREEN)- Executable with bonus ready.\n$(RESET)"
else
$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(OBJ) -lreadline -lft $(OPTS) $(LDFLAGS) -o $(NAME)
	@printf "$(_SUCCESS) $(GREEN)- Executable ready.\n$(RESET)"
endif

$(OBJDIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(OPTS) -c $< -o $@

clean:
	@$(RM) $(OBJDIR) $(OBJ)
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re: fclean all

.PHONY: all libft clean fclean re bonus norm