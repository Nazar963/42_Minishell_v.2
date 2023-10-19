# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 08:42:40 by lpollini          #+#    #+#              #
#    Updated: 2023/10/19 15:46:19 by naal-jen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
	
CC			= cc -g 
FLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

OBJDIR = .objFiles

FILES		= env_stuff executor executor_utils ft_split_1 ft_split_2 ft_split_utils ft_split_utils_1 \
	main main_check main_init operator_checker_bonus parenthesis_bonus parenthesis_parser pipex_main_helper_1 \
	pipex_main_helper_2 pipex_main_helper_3 pipex_main_helper pipex_main prompt_stuff shft_cmds_cd_2 \
	shft_cmds_echo_exit_env_helper shft_cmds_echo_exit_env shft_cmds_export_unset shft_cmds_pwd str_stuff \
	utils_bonus utils_bonus_1 utils_bonus_2 wildcard/parse wildcard/utils wildcard/utils_1

SRC			= $(FILES:=.c)
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER		= minishell.h
LDFLAGS		= -Llibft

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

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(OBJ) -lreadline -lft $(OPTS) $(LDFLAGS) -o $(NAME)
	@printf "$(_SUCCESS) $(GREEN)- Executable ready.\n$(RESET)"

$(OBJDIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(OPTS) -c $< -o $@

bonus: all

clean:
	@$(RM) $(OBJDIR) $(OBJ)
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re: fclean all

.PHONY: all libft clean fclean re bonus norm