# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 16:35:09 by naal-jen          #+#    #+#              #
#    Updated: 2023/10/25 17:04:34 by lpollini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -g
FLAGS = -Wall -Wextra -Werror
FILES = ft_atoi ft_calloc ft_isalnum ft_itoa ft_memmove ft_putstr_fd ft_split \
ft_strchr ft_strdup ft_strlen ft_strncmp ft_strnstr get_next_line
SRC = $(addsuffix .c, $(FILES))
OBJ = $(SRC:.c=.o)
INC = -I .
SLIB = ar rcs
NAME = libft.a
OBJDIR = obj

all: $(OBJDIR) $(NAME)

$(NAME) : $(addprefix $(OBJDIR)/, $(OBJ))
	@$(SLIB) $(NAME) $(addprefix $(OBJDIR)/, $(OBJ))

$(OBJDIR) :
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

