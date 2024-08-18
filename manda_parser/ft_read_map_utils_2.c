/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:43:35 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/18 16:54:20 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static	int	is_only_digits(char *s)
{
	while (s && *s)
	{   
		if (*s < '0' || '9' < *s)
			return (1);
		s++;
	}
	return (0);
}

static	int	convert_color(char **clms, int32_t *tab)
{
	int	i;

	i = -1;
	while (clms && clms[++i])
	{
		if (is_only_digits(clms[i]))
			return (write(2, "clr mst b only dgts!!\n", 23), -1);
		tab[i] = ft_atoi(clms[i]);
		if ((3 < ft_strlen(clms[i])) || (tab[i] < 0) || (255 < tab[i]))
			return (write(2, "clr vl mst b btwn 0 and 255!!\n", 31), -1);
	}
	return (0);
}

int	add_color(int32_t *color, char *value)
{
	char	**clms;
	int32_t	tab[3];

	if (!(clms = ft_split(value, ',')))
		return (write(2, "ft_splite failed in " \
			"add_color!!\n", 33), -1);
	else if (!clms[0] || !clms[1] || !clms[2] || clms[3])
		return (free_2d_arr(clms), \
			write(2, "color coloms must be three!!\n", 30), -1);
	if (*color == -1)
	{
		if (convert_color(clms, tab))
			return (free_2d_arr(clms), -1);
		*color = tab[0] << 24 | tab[1] << 16 | tab[2] << 8 | 255;
	}
	else
		return (free_2d_arr(clms), \
			write(2, "A color is duplicated!!\n", 25), -1);
	return (free_2d_arr(clms), 0);
}
