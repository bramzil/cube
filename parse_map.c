# include "parsing.h"

int is_only_allowed_chars(char *s_map)
{
    int         i;

    i = -1;
    while (s_map && s_map[++i])
        if (!ft_strchar("10NSWE \n", s_map[i]))
            return (ft_putstr_fd("there is an allowed" \
                "charecter in the map", 2), -1);
    return (0);
}

void get_longest_line(char **map, int *tab)
{
    int        tmp;

    tab[0] = 0;
    tab[1] = -1;
    while (map && map[tab[0]])
    {
        tmp = ft_strlen(map[tab[0]]);
        if (tab[1] < tmp)
            tab[1] = tmp;
        tab[0]++;
    }
}

int fill_sqr_map(char **sqr_map, char **map, int len)
{
    int         i;
    int         j;

    j = -1;
    while (map && map[++j])
    {
        i = -1;
        sqr_map[j] = malloc(sizeof(char) * (len + 1));
        if (!sqr_map)
            return (ft_putstr_fd("fail to allocate " \
                "line in sqr_map!!\n", 2), -1);
        while (map[j][++i])
            sqr_map[j][i] = map[j][i];
        while (i < len)
            sqr_map[j][i++] = ' ';
        sqr_map[j][i++] = '\0';
    }
    sqr_map[j] = NULL;
    return (0);
}

char    **create_square_map(char *s_map)
{
    int         tab[2];
    char        **tmp;
    char        **sqr_map;

    tmp = ft_split(s_map, '\n');
    if (!tmp)
        return (ft_putstr_fd("splite s_map failed!!\n", 2), NULL);
    get_longest_line(tmp, tab);
    if (!tab[0] || !tab[1])
        return (ft_putstr_fd("the map is empty!!\n", 2), NULL);
    sqr_map = malloc(sizeof(char *) * (tab[0] + 1));
    if (!sqr_map)
        return (ft_putstr_fd("fail to allocat sqr_map!!\n", 2), NULL);
    if (fill_sqr_map(sqr_map, tmp, tab[1]))
        return (free_2d_arr(tmp), free_2d_arr(sqr_map),
            ft_putstr_fd("fail to fill sqr_map!!\n", 2), NULL);
    return (free_2d_arr(tmp), sqr_map);
}

int parse_map(t_data *data, char *s_map)
{
    int         i;
    

    i = -1;
    if (is_only_allowed_chars(s_map))
        return (-1);
    data->map.arr = create_square_map(s_map);
    if (!data->map.arr)
        return (-1);
    while (data->map.arr[++i])
        printf("|%s|\n", data->map.arr[i]);
    return (0);
}