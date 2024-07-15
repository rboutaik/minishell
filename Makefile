# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 11:29:39 by aachalla          #+#    #+#              #
#    Updated: 2024/06/02 19:31:20 by rboutaik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAGS = -Wall -Werror -Wextra

NAME = minishell

SRCS =  main.c \
		Builtins/wild_card.c Builtins/builtins_1.c Builtins/builtins_2.c \
		Builtins/builtins_3.c Builtins/builtins_4.c Builtins/builtins_5.c Builtins/builtins_6.c \
		Builtins/builtins_7.c Builtins/builtins_8.c Builtins/here_doc.c Builtins/here_doc_utils.c \
		envr/env_1.c envr/env_2.c envr/env_3.c \
		executer/executer_.c executer/executer_1.c executer/executer_2.c \
		Execution/global_exec_1.c Execution/global_exec_2.c \
		Execution/global_exec_3.c Execution/global_exec_4.c Execution/global_exec_5.c \
		Execution/global_exec_6.c Execution/global_exec_7.c Execution/global_exec_8.c \
		Expanding/expander_utils.c Expanding/expander_utils_2.c \
		Expanding/expander.c Expanding/expander_var_.c \
		fill/fill_.c fill/fill_space.c fill/fill_utils_1.c \
		fill/fill_utils_2.c fill/fill_inou_file.c fill/fill_cmd_and_opt.c \
		ft_utils/ft_split.c ft_utils/ft_split1.c ft_utils/ft_split2.c ft_utils/ft_split3.c ft_utils/ft_2.c ft_utils/ft_3.c ft_utils/ft_.c \
		ft_utils/get_line_utils.c ft_utils/get_line.c \
		parser/parser_.c parser/parser_accol.c parser/parser_sq_dq_red_app_herd.c parser/parser_error_.c \
		token/token_.c token/token_utils_1.c token/token_utils_2.c \

OBJS = $(SRCS:.c=.o)

READLINEDIR = $(shell brew --prefix readline)

HEADER = minishell.h

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -L $(READLINEDIR)/lib -lreadline -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -I $(READLINEDIR)/include -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean