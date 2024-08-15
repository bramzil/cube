/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:25:36 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/15 13:07:43 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

void    free_2d_arr(char **arr)
{
    int     i;

    i = -1;
    while (arr && arr[++i])
        free (arr[i]);
    free (arr);
}

int check_extention(char *file)
{
    int        len;
    char       *tmp;

    len = ft_strlen(file);
    tmp = ft_substr(file, (len - 4), 4);
    if (!tmp || ft_strncmp(tmp, ".cub", 4))
    {
        ft_putstr_fd("Invalid map file's extention!!\n", 2);
        return (free(tmp), -1);
    }
    return (0);
}

int only_spaces(char *line)
{
    int     i;

    i = -1;
    while (line && line[++i])
        if ((line[i] != 32) && (line[i] < 9 || 13 < line[i]))
            return (1);
    return (0);
}

int is_valid_id(char *id)
{
    if (ft_strnstr("NO SO WE EA C F", id, 15))
        return (0);
    return (1);
}

int add_texture(char **texture, char *value)
{
    if (!(*texture))
            *texture = ft_strdup(value);
    else
        return (ft_putstr_fd("A texture is daplicated!!\n", 2), -1);
    return (0);
}

int is_only_digits(char *s)
{
    while (s && *s)
    {   
        if (*s < '0' || '9' < *s)
            return (1);
        s++;
    }
    return (0);
}

int convert_color(char **clms, int32_t *tab)
{
    int         i;

    i = -1;
    while (clms && clms[++i])
    {
        if (is_only_digits(clms[i]))
            return (ft_putstr_fd("clr mst b only dgts!!\n", 2), -1);
        tab[i] = ft_atoi(clms[i]);
        if ((3 < ft_strlen(clms[i])) || (tab[i] < 0) || (255 < tab[i]))
            return (ft_putstr_fd("clr vl mst b btwn 0 and 255!!\n", 2), -1);
    }
    return (0);
}

int add_color(int32_t *color, char *value)
{
    char        **clms;
    int32_t     tab[3];

    clms = ft_split(value, ',');
    if (!clms)
        return (ft_putstr_fd("splite clms failed!!\n", 2), -1);
    else if (!clms[0] || !clms[1] || !clms[2] || clms[3])
        return (free_2d_arr(clms), \
            ft_putstr_fd("color coloms must be three!!\n", 2), -1);
    if (*color == -1)
    {
        if (convert_color(clms, tab))
            return (free_2d_arr(clms), -1);
        *color = tab[0] << 24 | tab[1] << 16 | tab[2] << 8 | 255;
    }
    else
        return (free_2d_arr(clms), \
            ft_putstr_fd("A color is daplicated!!\n", 2), -1);
    return (free_2d_arr(clms), 0);
}

int add_element(t_data *data, char *id, char *value)
{
    if (is_valid_id(id))
        return (ft_putstr_fd("Invalid elemt id!!!\n", 2), -1);
     if (!ft_strncmp("NO", id, 2)&& \
        add_texture(&data->north_text.path, value))
        return (-1);
    else if (!ft_strncmp("SO", id, 2)&& \
        add_texture(&data->south_text.path, value))
        return (-1);
    else if (!ft_strncmp("WE", id, 2) && \
        add_texture(&data->west_text.path, value))
        return (-1);
    else if (!ft_strncmp("EA", id, 2) && \
        add_texture(&data->east_text.path, value))
        return (-1);
    else if (!ft_strncmp("C", id, 2) && \
        add_color(&data->c_color, value))
        return (-1);
    else if (!ft_strncmp("F", id, 2) && \
        add_color(&data->f_color, value))
        return (-1);
    return (0);
}

int is_all_elmts_there(t_data *data)
{
    if (!data->north_text.path || \
        !data->south_text.path || \
        !data->west_text.path || \
        !data->east_text.path || \
        (data->f_color == -1) || \
        (data->c_color == -1))
        return (-1);
    return (0);
}

int collect_map(t_data *data, char **s_map, char *line)
{
    char        *tmp;

    if (is_all_elmts_there(data))
        return (ft_putstr_fd("an element missed or " \
            "map misordered!!\n", 2), -1);
    tmp = *s_map;
    *s_map = ft_strjoin(*s_map, line);
    if (!(*s_map))
        return (free(tmp), ft_putstr_fd("collect map" \
            " fails!!\n", 2), -1);
    return (free(tmp), 0);
}

int set_element(t_data *data, char **s_map, char *line)
{
    char        *ref;
    char        **tmp;
    
    ref = line;
    line = ft_strtrim(line, "\n");
    if (!only_spaces(line))
        return (0);
    tmp = ft_split(line, ' ');
    if (!tmp)
        return (ft_putstr_fd("splite line failed!!\n", 2), -1);
    if (tmp[1] && tmp[2])
        return (free_2d_arr(tmp), \
            ft_putstr_fd("line elmts more than two!!\n", 2), -1);
    if (tmp[0] && tmp[1] && add_element(data, tmp[0], tmp[1]))
        return (free_2d_arr(tmp), -1);
    else if (tmp[0] && !tmp[1] && collect_map(data, s_map, ref))
        return (free_2d_arr(tmp), -1);
    return (free_2d_arr(tmp), 0);
}

int read_map(t_data *data, char **s_map, char *file)
{
    int         fd;
    char        *line;

    fd = open(file, O_RDONLY, 0222);
    if (fd < 0)
        return (ft_putstr_fd("fail to open map file!!\n", 2), -1);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (set_element(data, s_map, line))
            return (free (line), -1);
        free (line);
    }
    return (0);
}


int ft_parsing(t_data *data, char *file)
{
    char        *s_map;

    s_map = NULL;
    if (check_extention(file))
        return (-1);
    if (read_map(data, &s_map, file))
        return (-1);
    if (is_all_elmts_there(data) || !s_map)
        return (ft_putstr_fd("An element " \
            "is missed!!\n", 2), -1);
    if (parse_map(data, s_map))
        return (-1);
    return (0);
}
int main(int ac, char **av)
{
    t_data      data;
    
    data.c_color = -1;
    data.f_color = -1;
    data.north_text.path = NULL;
    data.south_text.path = NULL;
    data.west_text.path = NULL;
    data.east_text.path = NULL;
    if (ac != 2)
        return (printf("args nbr must be two!!\n"));
    if (ft_parsing(&data, av[1]))
        return (0);
    printf("texture north path, %s\n", data.north_text.path);
    printf("texture south path, %s\n", data.south_text.path);
    printf("texture west path, %s\n", data.west_text.path);
    printf("texture east path, %s\n", data.east_text.path);
    printf("color floor value, %x\n", data.f_color);
    printf("color Ceil value, %x\n", data.c_color);
    return (0);
}