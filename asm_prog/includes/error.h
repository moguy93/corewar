/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:34:26 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/15 21:28:28 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

# define BLACK "\033[22;30m"
# define BLUE "\033[1;36m"
# define RED "\033[1;31m"
# define L_RED "\033[1;31m"
# define L_GREEN "\033[1;32m"
# define GRA "\033[1m"
# define STOP "\033[0m"

# define USAGE "usage: ./asm [champion.s]"

# define FILE_EXT_ERR "Invalid file_name / .s extension"
# define EMPTY_OP_SECTION "Empty instruction section"

# define COMMENT_CMD_ERR "Invalid parameter for comment property"
# define NAME_CMD_ERR "Invalid parameter for name property"
# define MISSING_PROPERITY "properity(s) missing "
# define UNKNOWN_PROPERITY "Unknown properity "
# define DUP_PROPERITY "Duplicate properity "

# define INVALID_SYNTAX "Invalid syntax "
# define UNEX_TOKEN "Unexpected token "
# define EX_NEWLINE "Expected newline "

# define UNDEFINED_LABEL "Reference to undefined label "
# define INVALID_LABEL "Invalid label declaration "
# define DUP_LABEL "Duplicate label declaration :"

# define LINE "on line "
# define COL " at col "

# define NAME_LENGTH_ERR "Program name length exceed "
# define COMMENT_LENGTH_ERR "Comment length exceed "

# define INVALID_OP_PARAM "Invalid operation parameter "
# define TOO_FEW_ARGS "Too few arguments for operation "
# define NOT_ENO_ARGS "Not enough arguments for operation "

void	print_err_name(char *err);
void	print_cursor(char *line, unsigned int col);
void	print_line_n_col(unsigned int line, unsigned int col, bool colon);
int		get_type_str(int id, char *buff);
void	op_usage(int op);

#endif
