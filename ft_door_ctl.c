# include "cube.h"

static void open_door(t_data *data, t_door *door)
{
    if (2 < door->var)
    {
        door->var -= 1;
        door->state = 'M';
    }
    else
        door->state = 'O';
}

static void close_door(t_data *data, t_door *door)
{
    if (door->var < 32)
    {
        door->state = 'M';
        door->var += 1;
    }
    else
        door->state = 'C';
}

static double get_distance(t_data *data, int i)
{
    double      adja;
    double      oppo;
    t_point     center;

    center.x = (data->door_arr[i].i  * \
        data->grd_wd) + 32;
    center.y = (data->door_arr[i].j * \
        data->grd_ht) + 32;
    adja = fabs(data->plr.x - center.x);
    oppo = fabs(data->plr.y - center.y);
    return (sqrt((adja * adja) + (oppo * oppo)));
}

t_door  *get_door(t_data *data, int i, int j)
{
    int         k;

    k = -1;
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

int ft_door_ctl(t_data *data)
{
    int         i;
    int         bl;
    double      dist;
    t_door      *array;

    i = -1;
    bl = 0;
    array = data->door_arr;
    while (++i < data->doors_nbr)
    {
        dist = get_distance(data, i);
        if ((dist < 70) && (array[i].state != 'O') && ++bl)
            open_door(data, &array[i]);
        else if ((70 < dist) && (array[i].state != 'C') && ++bl)
            close_door(data, &array[i]);
        if (bl)
        {
            ft_clear_image(data->proj_img);
            ft_clear_image(data->map_img);
            ft_cast_rays(data);
        }
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