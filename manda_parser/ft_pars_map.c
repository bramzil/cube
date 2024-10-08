/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:01:19 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/18 18:04:16 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static	void	get_longest_line(char **map, int *tab)
{
	int	tmp;

	tab[0] = 0;
	tab[1] = -1;
	while (map && map[tab[0]])
	{
		tmp = ft_strlen(map[tab[0]]);
		if (tab[1] < tmp)
			tab[1] = tmp;
		tab[0]++;
	}
}

static	int	fill_sqr_map(char **sqr_map, char **map, int len)
{
	int	i;
	int	j;

	j = -1;
	while (map && map[++j])
	{
		i = -1;
		sqr_map[j] =  malloc(sizeof(char) * (len + 1));
		if (!sqr_map[j])
			return (write(2, "fail to allocate " \
				"line in sqr_map!!\n", 36), -1);
		while (map[j][++i])
			sqr_map[j][i] = map[j][i];
		while (i < len)
			sqr_map[j][i++] = ' ';
		sqr_map[j][i++] = '\0';
	}
	sqr_map[j] = NULL;
	return (0);
}

static	char	**create_square_map(char *s_map)
{
	int		tab[2];
	char	**tmp;
	char	**sqr_map;

	if (!(tmp = ft_split(s_map, '\n')))
		return (write(2, "splite s_map failed!!\n", 23), NULL);
	get_longest_line(tmp, tab);
	if (!tab[0] || !tab[1])
		return (write(2, "the map is empty!!\n", 20), NULL);
	if (!(sqr_map = malloc(sizeof(char *) * (tab[0] + 1))))
		return (write(2, "fail to allocat sqr_map!!\n", 27), NULL);
	if (fill_sqr_map(sqr_map, tmp, tab[1]))
		return (free_2d_arr(tmp), free_2d_arr(sqr_map),
			write(2, "fail to fill sqr_map!!\n", 24), NULL);
	return (free_2d_arr(tmp), sqr_map);
}

static	int	is_only_allowed_chars(char *s_map)
{
	int	i;

	i = -1;
	while (s_map && s_map[++i])
	{
		if (ft_strchar("10NSWE \n", s_map[i]) == -1)
		{
			write(2, "the : '", 8);
			write(2, &s_map[i], 1);
			write(2, "' is disallowed!!\n", 17);
			return (-1);
		}
	}
	return (0);
}

int	parse_map(t_data *data, char *s_map)
{
	int	i;

	i = -1;
	if (is_only_allowed_chars(s_map))
		return (-1);
	if (!(data->map.arr = create_square_map(s_map)))
		return (-1);
	if ((check_walls(data->map.arr)) != 0)
		return (-1);
	if ((ft_check_around_elem(data->map.arr)) != 0)
		return (-1);
	if (set_player_position(data) != 1)
		return (write(2, "Invalid nbr of plyr!!\n", 23), -1);
	return (0);
}
