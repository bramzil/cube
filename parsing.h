/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:27:04 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/15 11:18:01 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft/libft.h"

typedef struct  s_plr
{
    double          d;
    double          x;
    double          y;
}               t_plr;

typedef struct  map
{
	int         wd;
	int         ht;
	char		**arr;
}               t_map;

typedef struct  s_texture
{
    char        *path;
    int32_t     *arr;
}               t_texture;

typedef struct  s_data
{

	int32_t         c_color;
	int32_t         f_color;
    
    t_plr           plr;
	t_map			map;
    
    t_texture       north_text;
    t_texture       west_text;
    t_texture       east_text;
    t_texture       south_text;
}               t_data;

void    free_2d_arr(char **arr);
int     parse_map(t_data *data, char *s_map);

# endif