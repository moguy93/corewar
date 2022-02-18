# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:37:04 by gedemais          #+#    #+#              #
#    Updated: 2020/02/28 13:30:53 by gedemais         ###   ########.fr        #
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

COR_NAME=corewar
ASM_NAME=asm

COR_PATH=corewar_prog/
ASM_PATH=asm_prog/

LIB_PATH=libft/
LIB=$(LIB_PATH)libft.a

all: $(LIB) $(COR_NAME) $(ASM_NAME)

$(COR_NAME): $(COR_PATH)srcs/ $(COR_PATH)includes/
	@echo "Making $(RED)COREWAR virtual machine$(DEF)..."
	@cd $(COR_PATH) && make && mv $(COR_NAME) ../
	@echo "$(GRE)Done !$(DEF)"

$(ASM_NAME): $(ASM_PATH)srcs/ $(ASM_PATH)includes/
	@echo "Making $(RED)ASM Compiler$(DEF)..."
	@cd $(ASM_PATH) && make && mv $(ASM_NAME) ../
	@echo "$(GRE)Done !$(DEF)"

$(LIB): $(LIB_PATH)
	@echo "Making $(CYA)Libft$(DEF)..."
	@make -C $(LIB_PATH)

clean:
	@make -C $(LIB_PATH) clean
	@make -C $(COR_PATH) clean
	@make -C $(ASM_PATH) clean

fclean:
	@make -C $(LIB_PATH) fclean
	@make -C $(COR_PATH) fclean
	@make -C $(ASM_PATH) fclean
	@rm -rf $(COR_NAME)
	@rm -rf $(ASM_NAME)

re: fclean all
