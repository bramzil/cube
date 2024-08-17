/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map_utils_1_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:12:32 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/17 19:18:14 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	only_spaces(char *line)
{
	int	i;

	i = -1;
	while (line && line[++i])
		if ((line[i] != 32) && (line[i] < 9 || 13 < line[i]))
			return (1);
	return (0);
}

static	int	is_valid_id(char *id)
{
	if (ft_strnstr("NO SO WE EA C F", id, 15))
		return (0);
	return (1);
}

static	int	add_texture(char **texture, char *value)
{
	if (!(*texture))
		*texture = ft_strdup(value);
	else
		return (write(2, "A texture is duplicated!!\n", 27), -1);
	return (0);
}

int	add_element(t_data *data, char *id, char *value)
{
	if (value[ft_strlen(value) - 1] == '\n')
		value[ft_strlen(value) - 1] = '\0';
	if (is_valid_id(id))
		return (write(2, \
			"Invalid elemt id!!!\n", 21), -1);
	else if (!ft_strncmp("NO", id, 2)&& \
		add_texture(&data->north_text.path, value))
		return (-1);
	else if (!ft_strncmp("SO", id, 2)&& \
		add_texture(&data->south_text.path, value))
		return (-1);
	else if (!ft_strncmp("C", id, 2) && \
		add_color(&data->c_color, value))
		return (-1);
	else if (!ft_strncmp("F", id, 2) && \
		add_color(&data->f_color, value))
		return (-1);
	else if (!ft_strncmp("WE", id, 2) && \
		add_texture(&data->west_text.path, value))
		return (-1);
	else if (!ft_strncmp("EA", id, 2) && \
		add_texture(&data->east_text.path, value))
		return (-1);
	return (0);
}
