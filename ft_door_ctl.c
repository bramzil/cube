# include "cube.h"

static void open_door(t_data *data, t_door *door)
{
    if (2 < door->var)
    {
        door->var -= 1;
        ft_clear_image(data->ddd__img);
        ft_cast_rays(data);
    }
    else
        door->state = 'O';
}

static void close_door(t_data *data, t_door *door)
{
    if (door->var < 32)
    {
        door->var += 1;
        ft_clear_image(data->ddd__img);
        ft_cast_rays(data);
    }
    else
        door->state = 'C';
}

void ft_door_ctl(void *par)
{
    t_data      *data;

    data = (t_data *)par;
    if (data->door)
    {
        if (data->door->counter <= 0)
        {
            if (data->door->state == 'N')
                open_door(data, data->door);
            else if (data->door->state == 'S')
                close_door(data, data->door);
            data->door->counter = 5;
        }
        data->door->counter--;
    }
}

void    fill_doors_array(t_data *data)
{
    int         i;
    int         j;
    int         k;

    k = 0;
    j = -1;
    while (data->map[++j])
    {
        i = -1;
        while (data->map[j][++i] && (k < data->doors_nbr))
        {
            if (data->map[j][i] == 'd')
            {
                data->door_arr[k].i = i;
                data->door_arr[k].j = j;
                data->door_arr[k].var = 32;
                data->door_arr[k].state = 'C';
                data->door_arr[k].counter = 5;
                k++;
            }
        }
    }
}

t_door  *get_door(t_data *data, int i, int j, int bl)
{
    int         k;

    k = -1;
    if (bl)
    {
        i = ((data->plr.x + (80 * \
            cos(data->plr.d))) / data->grd_wd);
        j = ((data->plr.y + (80 * \
            sin(data->plr.d) * -1)) / data->grd_ht);
    }
    if (data->map[j][i] == 'd')
    {
        while (++k < data->doors_nbr)
        {
            if (data->door_arr[k].i == i && \
                data->door_arr[k].j == j)
                return (&data->door_arr[k]);
        }
    }
    return (NULL);
}