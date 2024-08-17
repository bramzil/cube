/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_last_line_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:02:58 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/17 19:17:40 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	free_2d_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free (arr[i]);
	free (arr);
}

static	int	check_line_content(char *line, int start, int end)
{
	while (start <= end)
	{
		if (line[start] == '1' || line[start] == ' ' || line[start] == '\t')
			start++;
		else
			return (write(2, "First and Last line must be just ones!!!!\n",
				49), -1);
	}
	return (0);
}

static	int	check_first_last_line_content(char **map, int i)
{
	int	start;
	int	end;

	if (!map)
		return (-1);
	if (!map[i])
		return (-1);
	start = ft_get_first_index(map[i]);
	end = ft_get_last_index(map[i]);
	return (check_line_content(map[i], start, end));
}

int	ft_get_rows(char **map)
{
	int	rows;

	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
}

int	check_first_last_line(char **map)
{
	int	result;

	result = check_first_last_line_content(map, 0);
	if (result != 0)
		return (result);
	result = check_first_last_line_content(map, ft_get_rows(map) - 1);
	return (result);
}
