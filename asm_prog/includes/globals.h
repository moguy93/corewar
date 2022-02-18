/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 21:26:48 by gedemais          #+#    #+#             */
/*   Updated: 2020/02/20 04:29:01 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_H
# define GLOBALS_H

# define NB_OPS 16
# define MAX_PARAM_NB 3

static char			*g_opnames[NB_OPS] = {"add", "aff", "and", "fork", "lfork",
	"ld", "ldi", "lld", "lldi", "live",
	"or", "st", "sti", "sub", "xor", "zjmp"};

static char			g_opcodes[NB_OPS] = {4, 16, 6, 12, 15, 2,
	10, 13, 14, 1, 7, 3, 11,
	5, 8, 9};

static int			g_direct_size[NB_OPS] = {4, 4, 4, 2, 2, 4, 2,
	4, 2, 4, 4, 4, 2, 4,
	4, 2};

typedef enum		e_token_type
{
	TOK_NONE,
	TOK_P_NAME,
	TOK_P_COM,
	TOK_STRING,
	TOK_LABEL,
	TOK_REG,
	TOK_NUMBER,
	TOK_LNUMBER,
	TOK_DLABA,
	TOK_INDLABA,
	TOK_OPCODE,
	TOK_SEPARATOR,
	TOK_NEWLINE,
	TOK_COMMENT,
	TOK_MAX
}					t_token_type;

static int			g_op_args[NB_OPS][MAX_ARGS_NUMBER * MAX_PARAM_NB] = {

	{TOK_REG, 0, 0,
		TOK_REG, 0, 0,
		TOK_REG, 0, 0},

	{TOK_REG, 0, 0,
		0, 0, 0,
		0, 0, 0},

	{TOK_REG, TOK_NUMBER, TOK_LNUMBER,
		TOK_REG, TOK_NUMBER, TOK_LNUMBER,
		TOK_REG, 0, 0},

	{TOK_LNUMBER, 0, 0,
		0, 0, 0,
		0, 0, 0},

	{TOK_LNUMBER, 0, 0,
		0, 0, 0,
		0, 0, 0},

	{TOK_NUMBER, TOK_LNUMBER, 0,
		TOK_REG, 0, 0,
		0, 0, 0},

	{TOK_REG, TOK_NUMBER, TOK_LNUMBER,
		TOK_REG, TOK_LNUMBER, 0,
		TOK_REG, 0, 0},

	{TOK_NUMBER, TOK_LNUMBER, 0,
		TOK_REG, 0, 0,
		0, 0, 0},

	{TOK_REG, TOK_NUMBER, TOK_LNUMBER,
		TOK_LNUMBER, TOK_REG, 0,
		TOK_REG, 0, 0},

	{TOK_LNUMBER, 0, 0,
		0, 0, 0,
		0, 0, 0},

	{TOK_REG, TOK_NUMBER, TOK_LNUMBER,
		TOK_REG, TOK_NUMBER, TOK_LNUMBER,
		TOK_REG, 0, 0},

	{TOK_REG, 0, 0,
		TOK_REG, TOK_NUMBER, 0,
		0, 0, 0},

	{TOK_REG, 0, 0,
		TOK_REG, TOK_LNUMBER, TOK_NUMBER,
		TOK_LNUMBER, TOK_REG},

	{TOK_REG, 0, 0,
		TOK_REG, 0, 0,
		TOK_REG, 0, 0},

	{TOK_REG, TOK_LNUMBER, TOK_NUMBER,
		TOK_REG, TOK_LNUMBER, TOK_NUMBER,
		TOK_REG, 0, 0},

	{TOK_LNUMBER, 0, 0,
		0, 0, 0,
		0, 0, 0}
};

typedef enum		e_lexemes_type
{
	LEX_NONE,
	LEX_NAME_PROP,
	LEX_COMMENT_PROP,
	LEX_LABEL,
	LEX_OP,
	LEX_MAX
}					t_lexemes_type;

#endif
