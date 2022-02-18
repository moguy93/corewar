/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_define.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 04:37:07 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 07:53:25 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Check if one live at least has been called and announce the winner.
*/

static inline void	istherealive(t_env *env, int x, int y, int size)
{
	char	str[42];

	if (env->last_live == 0)
	{
		attron(COLOR_PAIR(env->nb_pl));
		sprintf(&str[0], "%s", env->player[env->nb_pl - 1].name);
		if (env->xmax > 14 + (x + (int)ft_strlen(
						env->player[env->nb_pl - 1].name)))
			size = (int)ft_strlen(env->player[env->nb_pl - 1].name);
		else
			size = env->xmax - x - 14;
		mvprintw(y + 17, x + 14, "%.*s", size, &str[0]);
		attroff(COLOR_PAIR(env->nb_pl));
		return ;
	}
	attron(COLOR_PAIR(env->last_live));
	sprintf(&str[0], "%s", env->player[env->last_live - 1].name);
	if (env->xmax > 14 + (x + (int)ft_strlen(
					env->player[env->last_live - 1].name)))
		size = (int)ft_strlen(env->player[env->last_live - 1].name);
	else
		size = env->xmax - x - 14;
	mvprintw(y + 17, x + 14, "%.*s", size, &str[0]);
	attroff(COLOR_PAIR(env->last_live));
}

/*
** Announce the winner in ncurses.
*/

static inline void	help_info_define2(t_env *env, int x, int y)
{
	char	str[42];
	int		size;

	size = 0;
	if (!env->process)
	{
		if ((env->xmax > x || env->ymax > y + 17)
				&& (size = (env->xmax > x + 14) ? 14 : env->xmax - x)
				&& sprintf(&str[0], "The winner is "))
			mvprintw(y + 17, x, "%.*s", size, &str[0]);
		if ((env->xmax > x + 14))
			istherealive(env, x, y, size);
		if ((env->xmax > x || env->ymax > y + 21)
				&& (size = (env->xmax > x + 17) ? 17 : env->xmax - x)
				&& sprintf(&str[0], "Tap a key to exit"))
			mvprintw(y + 21, x, "%.*s", size, &str[0]);
	}
}

/*
** write the options in ncurses.
*/

static inline void	help_info_define(t_env *env, int x, int y)
{
	char	str[42];
	int		size;

	if ((env->xmax > x + 16 || env->ymax > y + 11)
			&& (size = (env->xmax > x + 57) ? 41 : env->xmax - x - 16)
			&& sprintf(&str[0], "- [s] or [S] : pass one cycle if in pause"))
		mvprintw(y + 11, x + 16, "%.*s", size, &str[0]);
	if ((env->xmax > x + 16 || env->ymax > y + 5)
			&& (size = (env->xmax > x + 56) ? 40 : env->xmax - x - 16)
			&& sprintf(&str[0], "- [-] : decrease the cycles/second limit"))
		mvprintw(y + 5, x + 16, "%.*s", size, &str[0]);
	if ((env->xmax > x + 16 || env->ymax > y + 7)
			&& (size = (env->xmax > x + 56) ? 40 : env->xmax - x - 16)
			&& sprintf(&str[0], "- [+] : increase the cycles/second limit"))
		mvprintw(y + 7, x + 16, "%.*s", size, &str[0]);
	if ((env->xmax > x + 16 || env->ymax > y + 9)
			&& (size = (env->xmax > x + 43) ? 27 : env->xmax - x - 16)
			&& sprintf(&str[0], "- [SPACE_BAR] : start/pause"))
		mvprintw(y + 9, x + 16, "%.*s", size, &str[0]);
	if ((env->xmax > x + 16 || env->ymax > y + 13)
			&& (size = (env->xmax > x + 42) ? 26 : env->xmax - x - 16)
			&& sprintf(&str[0], "- [ESC], [Q] or [q] : quit"))
		mvprintw(y + 13, x + 16, "%.*s", size, &str[0]);
}

/*
** write some info and there values in ncurses.
*/

void				write_info_define(t_env *env, int y, int x)
{
	char	str[42];
	int		size;

	if ((env->xmax > x || env->ymax > y)
			&& (size = (env->xmax > x + 20) ? 20 : env->xmax - x)
			&& sprintf(&str[0], "CYCLE_TO_DIE :%5d", env->cycle_to_die))
		mvprintw(y, x, "%.*s", size, &str[0]);
	if ((env->xmax > x || env->ymax > y + 1)
			&& (size = (env->xmax > x + 20) ? 20 : env->xmax - x)
			&& sprintf(&str[0], "CYCLE_DELTA  :%5d", CYCLE_DELTA))
		mvprintw(y + 1, x, "%.*s", size, &str[0]);
	if ((env->xmax > x || env->ymax > y + 2)
			&& (size = (env->xmax > x + 20) ? 20 : env->xmax - x)
			&& sprintf(&str[0], "NBR_LIVE     :%5d", NBR_LIVE))
		mvprintw(y + 2, x, "%.*s", size, &str[0]);
	if ((env->xmax > x || env->ymax > y + 3)
			&& (size = (env->xmax > x + 20) ? 20 : env->xmax - x)
			&& sprintf(&str[0], "MAX_CHECKS   :%5d", MAX_CHECKS))
		mvprintw(y + 3, x, "%.*s", size, &str[0]);
	if ((env->xmax > x || env->ymax > y + 5)
			&& (size = (env->xmax > x + 15) ? 15 : env->xmax - x)
			&& sprintf(&str[0], "COMMANDS     :"))
		mvprintw(y + 5, x, "%.*s", size, &str[0]);
	help_info_define(env, x, y);
	help_info_define2(env, x, y);
}
