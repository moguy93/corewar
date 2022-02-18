# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/23 03:23:53 by gedemais          #+#    #+#              #
#    Updated: 2020/02/28 13:17:56 by gedemais         ###   ########.fr        #
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

NAME=corewar

CC=gcc
CFLAGS= -Wall -Werror -Wextra

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g3 -fsanitize=address
endif

LIB_PATH=../libft/
LIB=$(LIB_PATH)libft.a

INC_PATH=includes/
INC_NAME=corewar.h\
		 cor_ncurses.h\
		 op.h\
		 libft.h\
		 define.h

INC=$(addprefix $(INC_PATH), $(INC_NAME))

SRCS_PATH=srcs/
SRCS_NAME=after_space.c\
		  after_word.c\
		  buffer.c\
		  buffer_help.c\
		  check_lives.c\
		  create_launch.c\
		  cycle_run.c\
		  cw_loop.c\
		  dump.c\
		  free_env.c\
		  get_data.c\
		  help_get_data.c\
		  get_name_len.c\
		  help_verbose.c\
		  init_arena.c\
		  load_args.c\
		  loader.c\
		  lst.c\
		  main.c\
		  merge_args.c\
		  reverse_bits.c\
		  utils.c\
		  verbose_op.c\
		  verbose_pc_op_help.c\
		  write_mem_cell.c\
		  op_add.c\
		  op_aff.c\
		  op_and.c\
		  op_fork.c\
		  op_ld.c\
		  op_ldi.c\
		  op_lfork.c\
		  op_live.c\
		  op_lld.c\
		  op_lldi.c\
		  op_or.c\
		  op_st.c\
		  op_sti.c\
		  op_sub.c\
		  op_xor.c\
		  op_zjmp.c\
		  init_ncurses.c\
		  keyboard_visu.c\
		  refresh_all.c\
		  write_arena.c\
		  write_border.c\
		  write_info.c\
		  write_define.c\
		  write_breakdown.c

SRCS=$(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS=$(SRCS:.c=.o)

all: $(LIB) $(NAME)

$(NAME) : $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) -I $(INC_PATH) $(OBJS) $(LIB) -lncurses

$(SRCS_PATH)%.o : $(SRCS_PATH)%.c $(INC)
	@$(CC) $(FLAGS) -I$(INC_PATH) -I$(LIB_PATH) -o $@ -c $<

$(LIB): $(LIB_PATH)
	@make -C $(LIB_PATH)

clean:
	@rm -rf $(OBJS)
	@make -C $(LIB_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM
	@make -C $(LIB_PATH) fclean

re: fclean all
