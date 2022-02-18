/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:35:07 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 06:57:52 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** initialize the COLOR_PAIR possible.
*/

void	init_colors(void)
{
	init_color(50, 234, 236, 238);
	init_pair(0, 50, COLOR_BLACK);
	init_pair(20, 50, 50);
	init_pair(10, 50, 50);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_RED);
	init_pair(21, COLOR_WHITE, COLOR_RED);
	init_pair(31, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_CYAN);
	init_pair(22, COLOR_WHITE, COLOR_CYAN);
	init_pair(32, COLOR_CYAN, COLOR_WHITE);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(13, COLOR_BLACK, COLOR_YELLOW);
	init_pair(23, COLOR_WHITE, COLOR_YELLOW);
	init_pair(33, COLOR_YELLOW, COLOR_WHITE);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(14, COLOR_BLACK, COLOR_GREEN);
	init_pair(24, COLOR_WHITE, COLOR_GREEN);
	init_pair(34, COLOR_GREEN, COLOR_WHITE);
}

/*
** initialize the ncurses environnement.
*/

void	init_visu(t_env *env)
{
	initscr();
	start_color();
	init_colors();
	cbreak();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);
	env->ncurses_speed = 20000;
	env->pause = true;
	write_border(env);
	write_arena(env);
	write_info(env);
	refresh();
}
