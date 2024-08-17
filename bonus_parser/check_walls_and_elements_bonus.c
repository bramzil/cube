/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_and_elements_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:07:07 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/17 19:17:47 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static	int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	just_space(char *str)
{
	while (*str)
	{
		if (!is_space((char)*str))
			return (-1);
		str++;
	}
	return (0);
}

int	ft_get_first_index(char *line)
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

int	ft_get_last_index(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line && i >= 0 && (line[i] == ' ' || line[i] == '\t' || \
			line[i] == '\n'))
		i--;
	return (i);
}

int	check_walls_and_elements(char **map)
{
	int		start;
	int		end;
	int		i;
	char	*line;

	i = ft_skip_first_spaces(map);
	while (map[i] != NULL)
	{
		start = ft_get_first_index(map[i]);
		end = ft_get_last_index(map[i]);
		if (map[i][start] != '1' || map[i][end] != '1')
			return (write(2, "Map is not closed by walls at line \n", 37), -1);
		line = ft_substr(map[i], start, end);
		free(line);
		i++;
	}
	return (0);
}
