/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:02:06 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 05:04:44 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** write some info and there values in ncurses.
*/

static inline void	info_top(t_env *env, int x, int y)
{
	char	str[42];
	int		size;

	attrset(A_BOLD);
	if (!env->pause && (env->xmax > x || env->ymax > y)
			&& (size = (env->xmax > x + 13) ? 13 : env->xmax - x)
			&& sprintf(&str[0], "** RUNNING **"))
		mvprintw(y, x, "%.*s", size, &str[0]);
	if (env->pause && (env->xmax > x || env->ymax > y)
			&& (size = (env->xmax > x + 12) ? 12 : env->xmax - x)
			&& sprintf(&str[0], "** PAUSED **"))
		mvprintw(y, x, "%.*s", size, &str[0]);
	if ((env->xmax > x || env->ymax > y + 2)
			&& (size = (env->xmax > x + 25) ? 25 : env->xmax - x)
			&& sprintf(&str[0], "Cycles/second limit :%4u",
				((env->ncurses_speed > 0) ? (SEC / env->ncurses_speed) : 600)))
		mvprintw(y + 2, x, "%.*s", size, &str[0]);
	if ((env->xmax > x || env->ymax > y + 5)
			&& (size = (env->xmax > x + 14) ? 14 : env->xmax - x)
			&& sprintf(&str[0], "Cycle :%7d", env->cycle_curr + env->cycle_tot))
		mvprintw(y + 5, x, "%.*s", size, &str[0]);
	if ((env->xmax > x || env->ymax > y + 7)
			&& (size = (env->xmax > x + 22) ? 22 : env->xmax - x)
			&& sprintf(&str[0], "Processes : %10u", env->last_rank))
		mvprintw(y + 7, x, "%.*s", size, &str[0]);
}

/*
** write the players and there info in the war, in ncurses.
*/

static inline void	info_player(t_env *env, int y, int i, int j)
{
	int		x;
	char	str[42];
	int		size;

	x = START_INFO;
	attron(COLOR_PAIR(i + 1));
	if ((env->xmax > x || env->ymax > y + j) && sprintf(&str[0],
				"Player %d : %s", env->player[i].id, &env->player[i].name[0]))
	{
		if (env->xmax > (x + 11 + (int)ft_strlen(&env->player[i].name[0])))
			size = 11 + (int)ft_strlen(&env->player[i].name[0]);
		else
			size = env->xmax - x;
		mvprintw(y + j, x, "%.*s", size, &str[0]);
	}
	if ((env->xmax > x + 2 || env->ymax > y + j + 1)
			&& (size = (env->xmax > x + 35) ? 33 : env->xmax - x - 2)
			&& sprintf(&str[0], "Last live : %21d", env->last_cycle_live[i]))
		mvprintw(y + j + 1, x + 2, "%.*s", size, &str[0]);
	if ((env->xmax > x + 2 || env->ymax > y + j + 2)
			&& (size = (env->xmax > x + 35) ? 33 : env->xmax - x - 2)
			&& sprintf(&str[0], "Lives in current period : %7lu",
				env->live_pl[i]))
		mvprintw(y + j + 2, x + 2, "%.*s", size, &str[0]);
	attroff(COLOR_PAIR(i + 1));
}

/*
** loop to write the info and the players.
*/

void				write_info(t_env *env)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = -1;
	j = 0;
	y = 2;
	x = START_INFO;
	if (env->xmax < x || env->ymax < y)
		return ;
	info_top(env, x, y);
	y += 9;
	while (++i < (int)env->nb_pl)
	{
		info_player(env, y, i, j);
		j += 4;
	}
	y = y + j;
	y = write_lives_breakdown(env, y, x);
	write_info_define(env, y, x);
	attroff(A_BOLD);
}
