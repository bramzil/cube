/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_around_elem_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:05:28 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/17 19:17:51 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	ft_skip_last_spaces(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (just_space(map[i]) != -1)
			i--;
		else
			break ;
	}
	return (i);
}

int	ft_skip_first_spaces(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		if (just_space(map[i]) != -1)
			i++;
		else
			break ;
	}
	return (i);
}

static	void	put_msg(char c)
{
	write(2, "invalid_position of : ->", 24);
	write(2, &c, 1);
	write(2, "<-\n", 4);
}

static	int	ft_check_position_of_elem(char **cp_map, char c, int *i, int *j)
{
	if (*i > 0 && (cp_map[*i - 1][*j] == ' ' || cp_map[*i - 1][*j] == '\t'
			|| cp_map[*i - 1][*j] == '\0'))
		return (put_msg(c), -1);
	if (cp_map[*i + 1] != NULL && (cp_map[*i + 1][*j] == ' '
		|| cp_map[*i + 1][*j] == '\t' || cp_map[*i + 1][*j] == '\0'))
		return (put_msg(c), -1);
	if (*j > 0 && (cp_map[*i][*j - 1] == ' ' || cp_map[*i][*j - 1] == '\t'
			|| cp_map[*i][*j - 1] == '\0'))
		return (put_msg(c), -1);
	if (cp_map[*i][*j + 1] == ' ' || cp_map[*i][*j + 1] == '\t'
			|| cp_map[*i][*j + 1] == '\0')
		return (put_msg(c), -1);
	return (0);
}

int	ft_check_around_elem(char **map)
{
	int	i;
	int	j;
	int	rows;
	int	cols;

	i = ft_skip_first_spaces(map);
	j = ft_skip_last_spaces(map);
	while (map[i] != NULL && i <= j)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || \
					map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E' \
						|| map[i][j] == 'D')
				if (ft_check_position_of_elem(map, map[i][j], &i, &j) != 0)
					return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
