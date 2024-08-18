/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_player_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:08:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/18 18:11:47 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static	int	is_one_caracter_of_player(char c)
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

static	void	set_number_of_doors(t_data *data)
{
	int	i;
	int	j;
	int	cmp;

	i = -1;
	data->doors_nbr = 0;
	while (data->map.arr && data->map.arr[++i] != NULL)
	{
		j = -1;
		while (data->map.arr[i][++j])
			if (data->map.arr[i][j] == 'D')
				data->doors_nbr++;
	}	
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
			if (is_one_caracter_of_player(data->map.arr[i][j]))
			{
				data->plr.x = (double)(j * 64 + 32);
				data->plr.y = (double)(i * 64 + 32);
				data->plr.d = ft_get_dir(data->map.arr, &i, &j);
				cmp++;
			}
		}
	}
	set_number_of_doors(data);
	return (cmp);
}
