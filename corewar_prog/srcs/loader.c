/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:53:41 by gedemais          #+#    #+#             */
/*   Updated: 2020/02/21 07:03:27 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				read_big_endian(t_env *env, int fd, bool magic)
{
	ssize_t		ret;
	int			reverse;

	if ((ret = read(fd, (void*)&reverse, 4)) < 1)
		return (error(BAD_FILE, NULL, NULL));
	reverse = rev_bits(reverse);
	if (magic)
	{
		env->player[env->nb_pl].magic = (uint32_t)reverse;
		if (env->player[env->nb_pl].magic != COREWAR_EXEC_MAGIC)
			return (error(singleton_str(0), NULL, NULL));
	}
	else
	{
		env->player[env->nb_pl].size = (uint32_t)reverse;
		if (env->player[env->nb_pl].size > CHAMP_MAX_SIZE)
			return (error(singleton_str(1), NULL, NULL));
	}
	return (0);
}

/*
** get and verify the header of the file and it's code.
*/

int				loader(t_env *env, char *arg, unsigned int *j)
{
	char			*file_name;
	int				fd;
	ssize_t			ret;

	if (!(file_name = ft_strndup(&arg[*j], (int)get_name_len(&arg[*j]))))
		return (error(MALLOC_ERR, NULL, NULL));
	if ((fd = open(file_name, O_RDONLY)) < 1)
		return (error(BAD_FILE_OPEN, USAGE, file_name));
	ft_strdel(&file_name);
	if (read_big_endian(env, fd, true))
		return (1);
	if ((ret = read(fd, &env->player[env->nb_pl].name[0], PROG_NAME_LENGTH)) < 1
		|| (ret = read(fd, &env->player[env->nb_pl].pad[0][0], 4)) < 1
		|| env->player[env->nb_pl].pad[0][0] != 0)
		return (error(BAD_FILE, NULL, NULL));
	if (read_big_endian(env, fd, false))
		return (1);
	if ((ret = read(fd, &env->player[env->nb_pl].com[0], COMMENT_LENGTH)) < 1
		|| (ret = read(fd, &env->player[env->nb_pl].pad[1][0], 4)) < 1
		|| env->player[env->nb_pl].pad[1][0] != 0
		|| (ret = read(fd, &env->player[env->nb_pl].champ[0],
				env->player[env->nb_pl].size + 1)) < 1
		|| ret != env->player[env->nb_pl].size)
		return (error((ret < 1) ? BAD_FILE : singleton_str(2), NULL, NULL));
	return (0);
}
