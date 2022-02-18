/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:16 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 06:40:24 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** give an id to the players who doesn't already have one.
*/

static inline void		give_id(t_env *env, unsigned int i, unsigned int j,
		uint8_t opt_n)
{
	while (i < env->nb_pl)
	{
		if (env->player[i].id == 0)
		{
			while (j < 5)
			{
				if (!(opt_n & (1 << j)))
				{
					env->player[i].id = (uint32_t)j;
					j++;
					break ;
				}
				j++;
			}
		}
		i++;
	}
}

static inline uint8_t	ft_power_cor(uint8_t nb, uint8_t pow)
{
	uint8_t	tmp;

	tmp = nb;
	if (pow < 1)
		return (0);
	while (pow > 1)
	{
		tmp *= nb;
		pow--;
	}
	return (tmp);
}

/*
** sort the players by id.
*/

static inline void		sort_players(t_env *env)
{
	t_player		tmp;
	unsigned int	i;

	i = 0;
	while (i < env->nb_pl - 1)
	{
		if (env->player[i].id > env->player[i + 1].id)
		{
			ft_memcpy(&tmp, &env->player[i], sizeof(t_player));
			ft_memcpy(&env->player[i], &env->player[i + 1], sizeof(t_player));
			ft_memcpy(&env->player[i + 1], &tmp, sizeof(t_player));
			i = 0;
		}
		else
			i++;
	}
}

/*
** get the -n designated id.
*/

int						get_id(t_env *env, char *arg, unsigned int *j, bool end)
{
	static uint8_t	opt_n = 0;
	long long int	id;
	unsigned int	i;

	if (end)
	{
		give_id(env, 0, 1, opt_n);
		sort_players(env);
		return (0);
	}
	i = after_space(arg, *j + 3);
	if (!ft_isdigit(arg[i]) || (id = ft_atoi(&arg[i])) < 1 || id > 4)
		return (error(BAD_ID, USAGE, NULL));
	env->player[env->nb_pl].id = (uint32_t)id;
	*j = i + 1;
	if (!(opt_n & (1 << env->player[env->nb_pl].id)))
		opt_n |= ft_power_cor(2, (uint8_t)id);
	else
		return (error(SAME_ID, USAGE, NULL));
	return (0);
}

/*
** process the argv, get option and file.
*/

int						get_data(t_env *env, char *arg)
{
	unsigned int	i;

	i = after_space(arg, 0);
	while (arg[i])
		if (help_get_data(env, arg, &i))
			return (1);
	if (env->opt[O_NCURSES] == 1)
	{
		if (env->opt[O_STEALTH])
		{
			ft_memset(&env->opt[0], 0, sizeof(int) * OPT_MAX);
			env->opt[O_STEALTH] = true;
		}
		else
			ft_memset(&env->opt[0], 0, sizeof(int) * OPT_MAX);
		env->opt[O_NCURSES] = 1;
	}
	if (get_id(env, arg, 0, true))
		return (1);
	if (check_too_high_id(env))
		return (error(BAD_ID, USAGE, NULL));
	return (0);
}
