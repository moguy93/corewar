# **************************************************************************** # # :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/23 03:23:53 by gedemais          #+#    #+#              #
#    Updated: 2020/02/20 19:39:17 by gedemais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF = \033[0m
GRA = \033[1m
SOU = \033[4m
BLI = \033[5m
BLA = \033[30m
RED = \033[31m
GRE = \033[32m
YEL = \033[33m
BLU = \033[34m
PUR = \033[35m
CYA = \033[36m
WHI = \033[37m
ORG = \033[1;31m

NAME=asm

CC=gcc
FLAGS= -Weverything -Wall -Werror -Wextra

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    FLAGS += -g3 -fsanitize=address
endif

LIB_PATH=../libft/
LIB=$(LIB_PATH)libft.a

INC_PATH=includes/
INC_NAME=	asm.h\
			error.h\
			globals.h

INC=$(addprefix $(INC_PATH), $(INC_NAME))

SRCS_PATH=srcs/
SRCS_NAME=	main.c\
			loader.c\
			tokenizer.c\
			token_lst.c\
			tokens_fts.c\
			tokens_fts_bis.c\
			tokens_fts_ter.c\
			init_labels.c\
			labels.c\
			lexer.c\
			bits.c\
			write_bytecode.c\
			write_values.c\
			encoding_byte.c\
			lexer_fts.c\
			lexer_loader.c\
			lexer_utils.c\
			error.c\
			error_utils.c\
			label_errors.c\
			op_errors.c\
			header.c\
			utils.c\
			free.c

SRCS=$(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS=$(SRCS:.c=.o)

all: $(LIB) $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(FLAGS) -I$(INC_PATH) -I $(LIB_PATH) -o $(NAME) $(OBJS) $(LIB)

$(SRCS_PATH)%.o: $(SRCS_PATH)%.c $(INC) ../corewar_prog/includes/op.h
	@$(CC) $(FLAGS) -I$(INC_PATH) -I$(LIB_PATH) -o $@ -c $<

$(LIB): $(LIB_PATH)
	@make -C $(LIB_PATH)
	
clean:
	@rm -rf $(OBJS)
	@make -C $(LIB_PATH) clean

fclean: clean
	@make -C $(LIB_PATH) fclean
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean all
