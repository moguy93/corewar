/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:48:51 by gedemais          #+#    #+#             */
/*   Updated: 2020/02/20 19:13:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../libft/libft.h"
# include "../corewar_prog/includes/op.h"
# include <error.h>
# include <globals.h>
# include <stdbool.h>
# include <errno.h>

# define BUFF_READ 65536
# define BUFF_WRITE 4096

# define HEADER_SIZE 2180

# define MAX_TYPE_SIZE 32

# define NB_TOKENS_FUNCS 13
# define NB_LEX_FUNCS 4
# define NB_LEX_LOAD_FUNCS 4

# define LBE_BUFFER 4
# define PADDING_VALUE 0

typedef union			u_args
{
	char						*str;
	int							reg;
	unsigned int				stick;
	long long int				nb;
	bool						label;
}						t_args;

typedef struct			s_lexem
{
	unsigned int		start;
	unsigned int		start_byte;
	char				opcode;
	char				type;
	unsigned char		encoding;
	char				dir_size;
	bool				code;
	char				pad[3];
	int					label[MAX_ARGS_NUMBER];
	t_args				args[MAX_ARGS_NUMBER];
}						t_lexem;

typedef struct s_token	t_token;

struct					s_token
{
	t_token				*next;
	t_token				*prev;
	char				*ptr;
	unsigned int		line;
	unsigned int		col;
	unsigned int		len;
	unsigned int		index;
	int					label;
	char				type;
	char				pad[3];
};

typedef struct			s_tokenizer
{
	unsigned int		line;
	unsigned int		col;
	unsigned int		i;
	unsigned int		len;
	unsigned int		line_start;
	unsigned int		index;
	char				ret;
	char				pad[3];
}						t_tokenizer;

typedef struct			s_label
{
	char				*ptr;
	unsigned int		stick;
	unsigned int		len;
}						t_label;

typedef	struct			s_env
{
	t_tokenizer			tok;
	char				pad[4];
	char				*file;
	char				*bin_name;
	char				*file_name;
	char				*p_name;
	char				*p_comment;
	t_token				*tokens;
	t_lexem				*lexemes;
	t_label				*labels;
	unsigned int		lab_i;
	unsigned int		nb_tokens;
	unsigned int		nb_labels;
	unsigned int		nb_lex;
	unsigned int		c_param;
	int					bin_size;
}						t_env;

/*
** Mains
*/
void					print_lst(t_token *lst);
int						loader(t_env *env, char *file_name);
int						tokenizer(t_env *env);

/*
** Tokenizer
*/
void					cross_whitespaces(char *stream, unsigned int *i);

int						init_labels(t_env *env);
bool					is_label(t_env *env, char *label);
int						find_label_index(t_label *labs, t_token *tok,
														unsigned int nb_labels);
bool					is_label_char(char c);

t_token					*token_lstnew(t_env *env, t_tokenizer *tok);
int						token_pushfront(t_token **lst, t_token *new);
void					token_snap_node(t_token **lst, t_token *node);
void					token_free_lst(t_token *lst);

char					get_tok_p_name(t_env *env, char *str, unsigned int *i);
char					get_tok_p_com(t_env *env, char *str, unsigned int *i);
char					get_tok_string(t_env *env, char *str, unsigned int *i);
char					get_tok_reg(t_env *env, char *str, unsigned int *i);
char					get_tok_number(t_env *env, char *str, unsigned int *i);
char					get_tok_lnumber(t_env *env, char *str, unsigned int *i);
char					get_tok_dlaba(t_env *env, char *str, unsigned int *i);
char					get_tok_indlaba(t_env *env, char *str, unsigned int *i);
char					get_tok_opcode(t_env *env, char *str, unsigned int *i);
char					get_tok_separator(t_env *env, char *s, unsigned int *i);
char					get_tok_newline(t_env *env, char *str, unsigned int *i);
char					get_tok_comment(t_env *env, char *str, unsigned int *i);
char					get_tok_label(t_env *env, char *str, unsigned int *i);

static char				(*g_token_fts[NB_TOKENS_FUNCS])
						(t_env*, char*, unsigned int*) = {
	[TOK_P_NAME - 1] = &get_tok_p_name,
	[TOK_P_COM - 1] = &get_tok_p_com,
	[TOK_STRING - 1] = &get_tok_string,
	[TOK_REG - 1] = &get_tok_reg,
	[TOK_LABEL - 1] = &get_tok_label,
	[TOK_NUMBER - 1] = &get_tok_number,
	[TOK_LNUMBER - 1] = &get_tok_lnumber,
	[TOK_DLABA - 1] = &get_tok_dlaba,
	[TOK_INDLABA - 1] = &get_tok_indlaba,
	[TOK_OPCODE - 1] = &get_tok_opcode,
	[TOK_SEPARATOR - 1] = &get_tok_separator,
	[TOK_NEWLINE - 1] = &get_tok_newline,
	[TOK_COMMENT - 1] = &get_tok_comment};

/*
** Lexer
*/
int						lexer(t_env *env);
char					find_op(char *op);
unsigned char			encoding_byte(unsigned char b, unsigned int p, int t);
bool					encoding_byte_pres(char type);

char					get_lex_name_prop(t_env *env, t_token *tok);
char					get_lex_comment_prop(t_env *env, t_token *tok);
char					get_lex_label(t_env *env, t_token *tok);
char					get_lex_opcode(t_env *env, t_token *tok);
int						check_opcode_params(t_token *tok, int op, int n_p);

bool					check_after(t_token *tok);
int						load_lex_name_prop(t_env *e, t_lexem *lex, t_token **t);
int						load_lex_comment_prop(t_env *env, t_lexem *lex,
																t_token **tok);
int						load_lex_label(t_env *env, t_lexem *lex, t_token **tok);
int						load_lex_opcode(t_env *env, t_lexem *lex, t_token **t);

/*
** Bytecode translating
*/
void					reverse_bits(char buff[LBE_BUFFER], int n);
unsigned char			rev_bits(unsigned char b, bool shift);

int						write_bytecode(t_env *env);
int						write_header(t_env *env, int *fd);

void					write_indirect_number(t_env *env, int fd, t_lexem lex,
																	int param);
void					write_direct_number(t_env *e, int fd, t_lexem l, int p);
void					write_register(int fd, t_lexem lex, int param);

/*
** Errors reporting
*/
int						invalid_syntax_err(t_env *env, t_tokenizer *tok);
int						expected_newline_err(t_token *tok);
int						invalid_op_parameter(t_token *tok, int op);
int						too_few_op_args(t_token *tok, int op);
int						not_eno_args(t_token *tok, int op);
int						invalid_label_err(t_token *tok);
int						undefined_label_err(t_env *env);
int						dup_label_err(char *l, unsigned int i, unsigned int f);
int						unknown_properity(char *stream);
int						property_error(char *file, t_token *tok);
int						missing_properity(bool name, bool comment);
int						dup_properity_err(char *file, unsigned int i);
int						unex_token(t_token *tok);

int						free_env(t_env *env);

/*
** Utils
*/
void					cross_whitespaces(char *stream, unsigned int *i);
void					cross_whitespace(char *stream, unsigned int *i);
void					cross_names(char *stream, unsigned int *i);
void					cross_line(char *stream, unsigned int *i);
void					swap_short_bytes(short *val);
int						reverse_int_bytes(int val);

void					free_lexemes(t_env *env);
#endif
