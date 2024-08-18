/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_around_elem_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:05:28 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/18 18:12:53 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static	void	put_msg(char c)
{
	write(2, "invalid_position of : ->", 24);
	write(2, &c, 1);
	write(2, "<-\n", 4);
}

static	int	ft_check_elmt_pos(char **map, int i, int j)
{
	if (-1 < ft_strchar(" \t\0", map[i + 1][j]))
		return (put_msg(map[i + 1][j]), -1);
	if (i && (-1 < ft_strchar(" \t\0", map[i - 1][j])))
		return (put_msg(map[i + 1][j]), -1);
	if (-1 < ft_strchar(" \t\0", map[i][j + 1]))
		return (put_msg(map[i + 1][j]), -1);
	if (j && (-1 < ft_strchar(" \t\0", map[i][j - 1])))
		return (put_msg(map[i + 1][j]), -1);
	return (0);
}

int	ft_check_around_elem(char **map)
{
	int	i;
	int	j;
	int	rows;
	int	cols;

	i = -1;
	while (map && map[++i])
	{
		j = -1;
		while (map[i][++j])
			if ((-1 < ft_strchar("0NSWED", map[i][j])) && \
				(ft_check_elmt_pos(map, i, j) != 0))
				return (-1);
	}
	return (0);
}
