/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_breakdown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 04:35:46 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 07:12:31 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** get the value of the color of the dash for the result of the previous ctd.
*/

static inline int	get_color_last(t_env *env, int j)
{
	int				i;
	unsigned long	value[4];
	unsigned long	tot;

	i = -1;
	tot = 0;
	while (++i < (int)env->nb_pl)
		tot += env->live_pl_last[i];
	value[0] = (tot < 1) ? 0 : env->live_pl_last[0] * 50 / tot;
	value[1] = (i < 2 || tot < 1) ? 0 : env->live_pl_last[1] * 50 / tot;
	value[2] = (i < 3 || tot < 1) ? 0 : env->live_pl_last[2] * 50 / tot;
	value[3] = (i < 4 || tot < 1) ? 0 : env->live_pl_last[3] * 50 / tot;
	if (value[0] > 0 && value[0] > 0 && value[0] >= (unsigned long)j)
		return (COLOR_PAIR(1) | A_BOLD);
	else if (i > 1 && value[1] > 0 && value[1] >= ((unsigned long)j - value[0]))
		return (COLOR_PAIR(2) | A_BOLD);
	else if (i > 2 && value[2] > 0 && value[2] >= (
				unsigned long)(j = j - (int)value[0] - (int)value[1]))
		return (COLOR_PAIR(3) | A_BOLD);
	else if (i > 3 && value[3] > 0 && value[3] >= ((unsigned long)j - value[2]))
		return (COLOR_PAIR(4) | A_BOLD);
	else if (j > 0 && i > 0 && (value[0] > 0 || value[1] > 0 || value[2] > 0
				|| value[3] > 0))
		return (COLOR_PAIR(i) | (int)A_BOLD);
	return (COLOR_PAIR(0));
}

/*
** get the value of the color of the dash.
*/

static inline int	get_color(t_env *env, int j)
{
	int				i;
	unsigned long	value[4];
	unsigned long	tot_lives;

	i = -1;
	tot_lives = 0;
	while (++i < (int)env->nb_pl)
		tot_lives += env->live_pl[i];
	value[0] = (tot_lives < 1) ? 0 : env->live_pl[0] * 50 / tot_lives;
	value[1] = (i < 2 || tot_lives < 1) ? 0 : env->live_pl[1] * 50 / tot_lives;
	value[2] = (i < 3 || tot_lives < 1) ? 0 : env->live_pl[2] * 50 / tot_lives;
	value[3] = (i < 4 || tot_lives < 1) ? 0 : env->live_pl[3] * 50 / tot_lives;
	if (value[0] > 0 && value[0] >= (unsigned long)j)
		return (COLOR_PAIR(1) | A_BOLD);
	else if (i > 1 && value[1] > 0 && value[1] >= ((unsigned long)j - value[0]))
		return (COLOR_PAIR(2) | A_BOLD);
	else if (i > 2 && value[2] > 0 && value[2] >= (
				unsigned long)(j = j - (int)value[0] - (int)value[1]))
		return (COLOR_PAIR(3) | A_BOLD);
	else if (i > 3 && value[3] > 0 && value[3] >= ((unsigned long)j - value[2]))
		return (COLOR_PAIR(4) | A_BOLD);
	else if (j > 0 && i > 0 && (value[0] > 0 || value[1] > 0 || value[2] > 0
				|| value[3] > 0))
		return (COLOR_PAIR(i) | (int)A_BOLD);
	return (COLOR_PAIR(0) | A_NORMAL);
}

/*
** writes the live breakdown with dash for the previous ctd.
*/

static inline void	breakdown_last(t_env *env, int x, int y, int i)
{
	char	str[42];
	int		size;

	attrset(A_BOLD);
	mvaddch(y + 1, x + i + 1, ']');
	if ((env->xmax > x || env->ymax > y + 3)
			&& (size = (env->xmax > x + 33) ? 33 : env->xmax - x)
			&& sprintf(&str[0], "Live breakdown for last period : "))
		mvprintw(y + 3, x, "%.*s", size, &str[0]);
	mvaddch(y + 4, x, '[');
	attroff(A_BOLD);
	i = -1;
	while (++i < 50)
	{
		attrset(get_color_last(env, i));
		mvaddch(y + 4, x + i + 1, '-');
		attrset(COLOR_PAIR(0) | A_BOLD);
	}
	mvaddch(y + 4, x + i + 1, ']');
}

/*
** writes the live breakdown with dash.
*/

int					write_lives_breakdown(t_env *env, int y, int x)
{
	int		i;
	char	str[42];
	int		size;

	if (env->ymax < y || env->xmax < x)
		return (y);
	if ((env->xmax > x || env->ymax > y)
			&& (size = (env->xmax > x + 36) ? 36 : env->xmax - x)
			&& sprintf(&str[0], "Live breakdown for current period : "))
		mvprintw(y, x, "%.*s", size, &str[0]);
	mvaddch(y + 1, x, '[');
	attroff(A_BOLD);
	i = -1;
	while (++i < 50)
	{
		attrset(get_color(env, i));
		mvaddch(y + 1, x + i + 1, '-');
	}
	breakdown_last(env, x, y, i);
	return (y + 6);
}
