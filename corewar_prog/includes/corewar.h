/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:10 by moguy             #+#    #+#             */
/*   Updated: 2020/03/01 20:13:44 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "define.h"
# include "cor_ncurses.h"
# include "op.h"
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <ncurses.h>
# include <curses.h>

/*
** =============================================================================
**						BUFFER
** =============================================================================
*/

typedef union		u_buf
{
	unsigned int	u;
	unsigned int	x;
	int				n;
	char			c;
	char			*str;
}					t_buf;

typedef struct		s_btab
{
	void			(*f)(t_buf arg, char *buf, int *j);
}					t_btab;

/*
** =============================================================================
** 						OPTIONS
** =============================================================================
*/

typedef enum		e_option
{
	O_A,
	O_D,
	O_N,
	O_NCURSES,
	O_STEALTH,
	O_S,
	O_V
}					t_option;

/*
** =============================================================================
** 						OP_CODES
** =============================================================================
*/

typedef enum		e_op_code
{
	OP_NONE,
	OP_LIVE,
	OP_LD,
	OP_ST,
	OP_ADD,
	OP_SUB,
	OP_AND,
	OP_XOR,
	OP_OR,
	OP_ZJMP,
	OP_LDI,
	OP_STI,
	OP_FORK,
	OP_LLD,
	OP_LLDI,
	OP_LFORK,
	OP_AFF,
	OP_MAX
}					t_op_code;

/*
** =============================================================================
** 						REGISTRES
** =============================================================================
*/

typedef enum		e_reg_id
{
	REG_NONE,
	REG_1,
	REG_2,
	REG_3,
	REG_4,
	REG_5,
	REG_6,
	REG_7,
	REG_8,
	REG_9,
	REG_10,
	REG_11,
	REG_12,
	REG_13,
	REG_14,
	REG_15,
	REG_16,
	REG_MAX
}					t_reg_id;

/*
** =============================================================================
** 						PROCESS
** =============================================================================
*/

typedef struct		s_op_arg
{
	unsigned char	type;
	unsigned char	pad[3];
	int32_t			arg;
}					t_op_arg;

typedef struct		s_instruct
{
	t_op_arg		args[MAX_ARGS_NUMBER];
	uint32_t		op;
}					t_instruct;

typedef struct s_process	t_process;

struct				s_process
{
	t_process		*next;
	t_instruct		instruct;
	int32_t			r[REG_NUMBER];
	uint32_t		pc : 12;
	uint32_t		tpc : 12;
	char			carry;
	uint32_t		pctmp : 12;
	uint32_t		pad : 20;
	int				alive;
	int				cycle_to_exec;
	int				rank;
	uint8_t			encoding;
	char			pad2[7];
};

/*
** =============================================================================
** 						VM AND PLAYERS
** =============================================================================
*/

typedef struct		s_arena
{
	int				living;
	short int		living_id;
	int				recent;
	short int		id;
	bool			used;
	uint8_t			value;
	char			pad[4];
}					t_arena;

typedef struct		s_player
{
	char			champ[CHAMP_MAX_SIZE];
	char			com[COMMENT_LENGTH + 1];
	char			name[PROG_NAME_LENGTH + 1];
	char			pad[2][PAD_LENGTH];
	uint32_t		id;
	uint32_t		magic;
	uint32_t		size;
}					t_player;

typedef struct		s_env
{
	t_process		*process;
	t_player		player[MAX_PLAYERS];
	t_arena			arena[MEM_SIZE];
	unsigned long	live_pl[MAX_PLAYERS];
	unsigned long	live_pl_last[MAX_PLAYERS];
	int				last_cycle_live[MAX_PLAYERS];
	int				opt[OPT_MAX];
	int				cycle_curr;
	int				cycle_to_dump;
	int				cycle_to_die;
	int				cycle_tot;
	int				last_cycle_lived;
	int				xmax;
	int				ymax;
	unsigned int	curr_lives;
	unsigned int	last_rank;
	unsigned int	nb_pl;
	unsigned int	ncurses_speed;
	unsigned int	pause;
	uint32_t		last_live;
	bool			onetime;
	char			pad[7];
	t_buf			arg;
}					t_env;

/*
** =============================================================================
** 						PROTOTYPES
** =============================================================================
*/

/*
** VISU
*/

int					keyboard_visu(t_env *env);
void				init_colors(void);
void				init_visu(t_env *env);
int					main_visu(void);
int					pause_loop(t_env *env);
void				refresh_all(t_env *env);
void				write_arena(t_env *env);
void				write_border(t_env *env);
void				write_info(t_env *env);
void				write_info_define(t_env *env, int x, int y);
int					write_lives_breakdown(t_env *env, int x, int y);

/*
** UTILS
*/

unsigned int		after_space(char *arg, unsigned int i);
unsigned int		after_word(char *arg, unsigned int i);
void				buffer_cor(t_buf arg, int path, bool flush);
void				conv_char(t_buf arg, char *buf, int *j);
void				conv_hex(t_buf arg, char *buf, int *j);
void				conv_int(t_buf arg, char *buf, int *j);
void				conv_uint(t_buf arg, char *buf, int *j);
void				conv_str(t_buf arg, char *buf, int *j);
unsigned int		get_name_len(char *name);
char				hex_tab(uint8_t quartet);
char				*merge_args(int ac, char **av);
int					rev_bits(int num);

/*
** OPTIONS UTILS
*/

int					get_dump(char *arg, unsigned int *j);
void				verbose_pc(t_env *env, t_process *p);
void				verbose_op(t_env *env, t_process *p);
void				help_verbose_op(t_env *env, t_process *p, uint32_t op);
void				help_verbose2(t_env *env, t_process *p, uint32_t op, int i);
void				help_verbose3(t_env *env, t_process *p, uint32_t op, int i);

/*
** OPTIONS
*/

void				dump(t_env *env);

/*
** UTILS AND PARSING
*/

int					check_too_high_id(t_env *env);
int					error(char *error_msg, char *err_msg, char *junk);
void				free_env(t_env *env, char *arg);
int					get_data(t_env *env, char *arg);
int					help_get_data(t_env *env, char *arg, unsigned int *j);
int					get_id(t_env *env, char *arg, unsigned int *j, bool end);
int					init_arena(t_env *env);
int					loader(t_env *env, char *arg, unsigned int *j);
int					read_big_endian(t_env *env, int fd, bool magic);
char				*singleton_str(int error);

/*
** FUNCTIONS OF THE COREWAR LOOP
*/

int					add_instruction(t_env *env, t_process *process);
void				check_live(t_env *env);
void				create_instruct(t_env *env, t_process *process);
int					create_pro(t_env *env, unsigned int i, unsigned int offset);
int					cycle_run(t_env *env, t_process *p);
int					cw_loop(t_env *env);
int32_t				get_arg_value(t_env *v, t_process *p, int i, bool mod);
int32_t				get_mem_cell(t_env *v, t_process *p, size_t siz);
void				launch_instruct(t_env *env, t_process *process);
void				load_args(t_env *env, t_process *p, bool enco, bool dir);
bool				reg_is_valid(t_process *p, t_op_arg arg[MAX_ARGS_NUMBER]);
void				write_mem_cell(t_env *v, t_process *p, int32_t value);

/*
** LISTS
*/

t_process			*new_lst(uint32_t id, uint32_t pc);
t_process			*push_lst(t_env *env, uint32_t id, uint32_t pc);
t_process			*pop_lst(t_process *process, t_process *prev);

/*
** OP_FUNCTIONS
*/

void				live(t_env *env, t_process *process);
void				ld(t_env *env, t_process *process);
void				st(t_env *env, t_process *process);
void				add(t_env *env, t_process *process);
void				sub(t_env *env, t_process *process);
void				and(t_env *env, t_process *process);
void				xor(t_env *env, t_process *process);
void				or(t_env *env, t_process *process);
void				zjmp(t_env *env, t_process *process);
void				ldi(t_env *env, t_process *process);
void				sti(t_env *env, t_process *process);
void				op_fork(t_env *env, t_process *process);
void				lld(t_env *env, t_process *process);
void				lldi(t_env *env, t_process *process);
void				lfork(t_env *env, t_process *process);
void				aff(t_env *env, t_process *process);

/*
** =============================================================================
** 						FUNCTION_TABLE
** =============================================================================
*/

static const t_btab g_conv_tab[5] =
{
	{&conv_str},
	{&conv_hex},
	{&conv_uint},
	{&conv_int},
	{&conv_char},
};

typedef struct		s_op
{
	char			*name;
	unsigned char	nb_arg;
	unsigned char	args[3];
	unsigned int	op_code;
	uint64_t		wait_cycles;
	char			*description;
	unsigned int	encoding;
	unsigned int	direct;
	void			(*f)(t_env *env, t_process *p);
}					t_op;

static const t_op	g_func_tab[NB_FUNC] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, &live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, &ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, &st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, &add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, &sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, &and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, &or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, &xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, &zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, &ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, &sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, &op_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, &lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, &lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, &lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, &aff},
};

#endif
