/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:11:16 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/18 16:52:59 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static	int	is_other_elmts_set(t_data *data)
{
	if (!data->north_text.path || \
		!data->west_text.path || \
		!data->east_text.path || \
		!data->south_text.path || \
		(data->f_color == -1) || \
		(data->c_color == -1))
		return (-1);
	return (0);
}

static	int	collect_map(t_data *data, char **s_map, char *line)
{
	char	*tmp;

	if (is_other_elmts_set(data))
		return (write(2, "an element missed or " \
			"map misordered!!\n", 39), -1);
	tmp = *s_map;
	if (!(*s_map = ft_strjoin(*s_map, line)))
		return (free(tmp), write(2, "collect map" \
			" failed!!\n", 22), -1);
	return (free(tmp), 0);
}

static	int	is_there_an_ident(char *line)
{
	if (ft_strnstr(line, "NO ", ft_strlen(line)))
		return (1);
	else if (ft_strnstr(line, "SO ", ft_strlen(line)))
		return (1);
	else if (ft_strnstr(line, "WE ", ft_strlen(line)))
		return (1);
	else if (ft_strnstr(line, "EA ", ft_strlen(line)))
		return (1);
	else if (ft_strnstr(line, "F ", ft_strlen(line)))
		return (1);
	else if (ft_strnstr(line, "C ", ft_strlen(line)))
		return (1);
	return (0);
}

static	int	set_elements(t_data *data, char **s_map, char *line)
{
	int		t[2];
	char	*ptr;
	char	**pair;

	pair = NULL;
	t[0] = t[1] = 0;
	if (!(ptr = ft_strtrim(line, "\n")))
		return (write(2, "ft_str_trim failed in " \
			"set_elements!!\n", 38), -1);
	else if (!only_spaces(ptr))
		return (free(ptr), 0);
	else if (is_there_an_ident(ptr))
	{
		if (!(pair = ft_split_ky_vl(ptr)))
			return (free(ptr), -1);
		if (add_element(data, pair[0], pair[1]))
			return (free_2d_arr(pair), free(ptr), -1);
	}
	else if (collect_map(data, s_map, line))
		return (free(ptr), -1);
	return (free_2d_arr(pair), free(ptr), 0);
}

int	read_map(t_data *data, char **s_map, char *file)
{
	int         fd;
	char        *line;

	if ((fd = open(file, O_RDONLY, 0222)) < 0)
		return (write(2, "open failed in " \
			"read_map!!\n", 27), -1);
	while (1)
	{
		if (!(line = get_next_line(fd)))
			break;

		if (set_elements(data, s_map, line))
			return (free(line), -1);
		free(line);
	}
	return (0);
}
