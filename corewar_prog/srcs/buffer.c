/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 01:17:03 by moguy             #+#    #+#             */
/*   Updated: 2020/02/27 17:08:19 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				conv_char(t_buf arg, char *buf, int *j)
{
	buf[*j] = arg.c;
	*j += 1;
}

static inline void	help_conv_int(char *buf, char *tmp, int i, int k)
{
	while (--k >= 0)
	{
		buf[i] = tmp[k];
		i++;
	}
}

void				conv_int(t_buf arg, char *buf, int *j)
{
	int				i;
	int				k;
	long			n;
	char			tmp[10];
	static char		dt[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	k = 0;
	n = (long)arg.n;
	i = *j;
	if (n < 0 && (n = -n))
		buf[i++] = '-';
	while (n > 9)
	{
		tmp[k++] = dt[n % 10];
		n /= 10;
	}
	tmp[k++] = dt[n % 10];
	*j = i + k;
	help_conv_int(&buf[0], &tmp[0], i, k);
}

void				conv_uint(t_buf arg, char *buf, int *j)
{
	int				i;
	int				k;
	unsigned int	n;
	char			tmp[10];
	static char		deci_tab[10] = {'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9'};

	k = 0;
	i = *j;
	n = arg.u;
	while (n > 9)
	{
		tmp[k] = deci_tab[n % 10];
		n /= 10;
		k++;
	}
	tmp[k++] = deci_tab[n % 10];
	*j = i + k;
	help_conv_int(&buf[0], &tmp[0], i, k);
}

void				buffer_cor(t_buf arg, int path, bool flush)
{
	static int		i = 0;
	static char		buf[SHRT_MAX];

	if (path > -1)
		g_conv_tab[path].f(arg, &buf[0], &i);
	if (flush || i > SHRT_MAX - 100)
	{
		write(1, &buf[0], (size_t)i);
		i = 0;
	}
}
