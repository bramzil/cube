/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:07:07 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/18 18:00:16 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static int	ft_get_first_index(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (i);
		i++;
	}
	return (i);
}

static int	ft_get_last_index(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line && (0 <= i))
	{
		if (line[i] != ' ' || line[i] != '\t')
			return (i);
		i--;
	}
	return (i);
}

static int	is_valid_wall(char *line)
{

	while (line && *line)
	{
		if (ft_strchr("1 \t", *line) < 0)
			return (write(2, "first or last  not" \
				" valid border!!\n", 35), -1);
		line++;
	}
	return (0);
}

int	check_walls(char **map)
{
	int		i;
	int		start;
	int		end;

	i = -1;
	if (is_valid_wall(map[0]))
		return (-1);
	while (map[(++i) + 1])
	{
		start = ft_get_first_index(map[i]);
		end = ft_get_last_index(map[i]);
		if (map[i][start] != '1' || map[i][end] != '1')
			return (write(2, "Map is not closed by " \
				"walls at line \n", 37), -1);
	}
	if (is_valid_wall(map[i]))
		return (-1);
	return (0);
}
