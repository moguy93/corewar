/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:56:12 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 07:38:22 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** show the winner.
*/

static inline void	print_winner(t_env *env)
{
	unsigned int	i;

	i = env->last_live - 1;
	env->arg.str = "Contestant ";
	buffer_cor(env->arg, 0, 0);
	if (env->last_live == 0)
		env->arg.u = env->player[env->nb_pl - 1].id;
	else
		env->arg.u = env->player[i].id;
	buffer_cor(env->arg, 2, 0);
	env->arg.str = ", \"";
	buffer_cor(env->arg, 0, 0);
	if (env->last_live == 0)
		env->arg.str = env->player[env->nb_pl - 1].name;
	else
		env->arg.str = env->player[i].name;
	buffer_cor(env->arg, 0, 0);
	env->arg.str = "\", has won !\n";
	buffer_cor(env->arg, 0, 0);
}

/*
** wait for a key then exit.
*/

static inline int	end_loop(t_env *env)
{
	refresh_all(env);
	timeout(-1);
	getch();
	clear();
	refresh();
	endwin();
	return (1);
}

/*
** In case of a ncurses activation.
*/

static inline int	visu_run(t_env *env)
{
	if (!env->pause || (env->pause && env->onetime))
	{
		usleep(env->ncurses_speed);
		env->onetime = false;
		cycle_run(env, env->process);
		if (env->cycle_curr >= env->cycle_to_die)
			check_live(env);
		write_arena(env);
		write_info(env);
		refresh();
	}
	if (env->pause && env->process)
		if (pause_loop(env))
			return (1);
	if (!env->pause && keyboard_visu(env))
		return (1);
	return (0);
}

/*
** In case of a regular war.
*/

static inline int	vm_run(t_env *env)
{
	cycle_run(env, env->process);
	if (env->cycle_curr >= env->cycle_to_die)
		check_live(env);
	if (env->opt[O_D] != 0 && (env->cycle_to_dump -= 1) == 0
			&& env->process)
	{
		dump(env);
		if (!env->opt[O_S])
			return (1);
	}
	return (0);
}

/*
** Simulate the war and announce the winner.
*/

int					cw_loop(t_env *env)
{
	if (env->opt[O_S])
		dump(env);
	while (env->process && env->cycle_tot <= MAX_CYCLE)
	{
		if (env->cycle_to_die <= 0 && cycle_run(env, env->process))
			check_live(env);
		while (env->process && env->cycle_curr < env->cycle_to_die
				&& env->cycle_to_die > 0 && env->cycle_tot <= MAX_CYCLE)
		{
			if (env->opt[O_NCURSES])
				if (visu_run(env))
					return (1);
			if (!env->opt[O_NCURSES])
				if (vm_run(env))
					return (1);
		}
	}
	if (env->opt[O_NCURSES] && end_loop(env))
		return (0);
	print_winner(env);
	buffer_cor(env->arg, -1, 1);
	return (0);
}
