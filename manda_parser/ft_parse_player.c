/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:08:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/18 18:11:16 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static	int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

static	double	ft_get_dir(char **map, int *i, int *j)
{
	double	angle;

	if (map[*i][*j] == 'N')
		angle = 90 * (M_PI / 180.0);
	else if (map[*i][*j] == 'S')
		angle = 270 * (M_PI / 180.0);
	else if (map[*i][*j] == 'W')
		angle = 180 * (M_PI / 180.0);
	else if (map[*i][*j] == 'E')
		angle = 0 * (M_PI / 180.0);
	return (angle);
}

int	set_player_position(t_data *data)
{
	int	i;
	int	j;
	int	cmp;

	i = -1;
	cmp = 0;
	while (data->map.arr && data->map.arr[++i] != NULL)
	{
		j = -1;
		while (data->map.arr[i][++j])
		{
			if (is_player_char(data->map.arr[i][j]))
			{
				data->plr.x = (double)(j * 64 + 32);
				data->plr.y = (double)(i * 64 + 32);
				data->plr.d = ft_get_dir(data->map.arr, &i, &j);
				cmp++;
			}
		}
	}
	printf("the nbr of players are: %d\n", cmp);
	return (cmp);
}
