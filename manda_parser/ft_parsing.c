/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:59:40 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/17 19:19:52 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_elements(t_data *data)
{
	free(data->north_text.path);
	free(data->south_text.path);
	free(data->west_text.path);
	free(data->east_text.path);
	free_2d_arr(data->map.arr);
}

static	int	check_extention(char *file)
{
	int		len;
	char	*tmp;

	len = ft_strlen(file);
	tmp = ft_substr(file, (len - 4), 4);
	if (!tmp || ft_strncmp(tmp, ".cub", 4))
		return (free(tmp), write(2, "Invalid " \
			"map file's extention!!\n", 32), -1);
	return (free(tmp), 0);
}

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

int	ft_parsing(t_data *data, char *file)
{
	char	*s_map;

	s_map = NULL;
	if (check_extention(file))
		return (-1);
	if (read_map(data, &s_map, file))
		return (-1);
	if (is_other_elmts_set(data) || !s_map)
		return (write(2, "An element is missed!!\n", 24), -1);
	if (parse_map(data, s_map))
		return (free_elements(data), free(s_map), -1);
	return (free(s_map), 0);
}

void    leak(void)
{
	system("leaks       a.out");
}

int main(int ac, char **av)
{
	t_data      data;
	
	atexit(leak);
	data.c_color = -1;
	data.f_color = -1;
	data.north_text.path = NULL;
	data.south_text.path = NULL;
	data.west_text.path = NULL;
	data.east_text.path = NULL;
	if (ac != 2)
		return (printf("Pass only map file as arg!!\n"));
	if (ft_parsing(&data, av[1]))
		return (0);
	printf("-----> POS PLAYER  : \n");
	printf("->x : %f\n", data.plr.x);
	printf("->y : %f\n", data.plr.y);
	printf("\n-----> TEXTURES : \n");
	printf("->texture north path, %s\n", data.north_text.path);
	printf("->texture south path, %s\n", data.south_text.path);
	printf("->texture west path, %s\n", data.west_text.path);
	printf("->texture east path, %s\n", data.east_text.path);
	printf("\n-----> COLORS : \n");
	printf("->color floor value, %x\n", data.f_color);
	printf("->color Ceil value, %x\n", data.c_color);
	printf("\n-----> MAP : \n");
	int i = 0;
	while (data.map.arr[i])
		printf("|%s|\n", data.map.arr[i++]);
	free_elements(&data);
	return (0);
}
