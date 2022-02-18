/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 07:32:57 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 05:00:34 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** draw the border of the ncurses.
*/

void	write_border(t_env *env)
{
	int		x;
	int		y;

	x = 0;
	y = -1;
	attron(COLOR_PAIR(20));
	getmaxyx(stdscr, env->ymax, env->xmax);
	while (++y < END_ARENA_BOTTOM + 1 && y < env->ymax)
	{
		mvaddch(y, x, '*');
		if (env->xmax > END_ARENA_RIGHT)
			mvaddch(y, END_ARENA_RIGHT, '*');
		if (env->xmax > END_INFO_RIGHT)
			mvaddch(y, END_INFO_RIGHT, '*');
	}
	y = 0;
	x = -1;
	while (++x < END_INFO_RIGHT + 1 && y < env->ymax)
	{
		mvaddch(y, x, '*');
		if (env->ymax > END_ARENA_BOTTOM)
			mvaddch(END_ARENA_BOTTOM, x, '*');
	}
	attroff(COLOR_PAIR(20));
}
