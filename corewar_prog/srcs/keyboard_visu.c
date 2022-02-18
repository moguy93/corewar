/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_visu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:18:59 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 08:05:37 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	help_keyboard(t_env *env, int key_input)
{
	if ((key_input == '-' && env->ncurses_speed < 100000)
			|| (key_input == '+' && env->ncurses_speed > 0))
	{
		env->ncurses_speed = (unsigned int)((int)env->ncurses_speed + ((
						key_input == '-') ? 2000 : -2000));
		write_info(env);
		refresh();
	}
	else if (key_input == 27 || key_input == 'q' || key_input == 'Q')
	{
		clear();
		refresh();
		endwin();
		return (1);
	}
	return (0);
}

/*
** get keyboard entry and apply the changes, in a pause loop.
** if it is the end of the war, wait for an exit key.
** key_code 410 is the resize of the window.
*/

int					pause_loop(t_env *env)
{
	int		key_input;

	while (env->pause && env->process)
	{
		timeout(-1);
		key_input = getch();
		if (key_input == 410)
			refresh_all(env);
		else if (key_input == ' ')
		{
			write_info(env);
			refresh();
			env->pause = false;
		}
		else if (key_input == 's' && env->pause)
		{
			env->onetime = true;
			return (0);
		}
		if (help_keyboard(env, key_input))
			return (1);
	}
	return (0);
}

/*
** get keyboard entry and apply the changes.
*/

int					keyboard_visu(t_env *env)
{
	int		key_input;

	timeout(1);
	key_input = getch();
	if (key_input == 410)
		refresh_all(env);
	else if (key_input == ' ')
	{
		env->pause = true;
		write_info(env);
		refresh();
		if (pause_loop(env))
			return (1);
	}
	if (help_keyboard(env, key_input))
		return (1);
	return (0);
}
