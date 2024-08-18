/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:27:04 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/18 18:12:43 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include <math.h>
# include "../libft/libft.h"

typedef	struct s_plr
{
	double	d;
	double	x;
	double	y;
}	t_plr;

typedef struct map
{
	int		wd;
	int		ht;
	char	**arr;
}	t_map;

typedef struct s_texture
{
	char	*path;
	int32_t	*arr;
}	t_texture;

typedef struct s_door
{
	int		i;
	int		j;
	int		var;
	char	state;
}	t_door;

typedef struct  s_data
{
	int			doors_nbr;

	int32_t		c_color;
	int32_t		f_color;
	
	t_plr		plr;
	t_map		map;
	t_texture	north_text;
	t_texture	west_text;
	t_texture	east_text;
	t_texture	south_text;
}	t_data;

void	free_2d_arr(char **arr);
char 	**ft_split_ky_vl(char *line);
int		ft_parsing(t_data *data, char *file);
int		parse_map(t_data *data, char *s_map);
int		ft_check_around_elem(char **map);
int		check_walls(char **map);
int		set_player_position(t_data *data);
int		only_spaces(char *line);
int		read_map(t_data *data, char **s_map, char *file);
int		add_element(t_data *data, char *id, char *value);
int		add_color(int32_t *color, char *value);
void	free_elements(t_data *data);

# endif