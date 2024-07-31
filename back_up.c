# include "cube.h"

static int new_face(t_data *data, t_face **tmp, int i)
{
    (*tmp)->next = new_node(data->array[i].x, \
        data->array[i].y);
    if (!(*tmp)->next)
        return (-1);
    (*tmp) = (*tmp)->next;
    return (0);
}

static void update_x_face(t_data *data, t_face *tmp, int i)
{
    int         x;
    int         y;
    int         z;

    z = 0;
    x = (int)data->array[i].x;
    y = (int)data->array[i].y;
    if ((data->array[i].x - data->plr.x) < 0)
        (tmp->dir = 'E', z--);
    else if (0 < (data->array[i].x - data->plr.x))
        tmp->dir = 'W';
    if ((i == (data->wnd_wd - 1)) || (data->array[i + 1].x != \
        tmp->x_ref))
        tmp->height_2 = get_height(data, i);
    if (data->map[(y / data->grd_ht)][(x / data->grd_wd) + z] == '1')
        tmp->typ = 'W';
    if (data->map[(y / data->grd_ht)][(x / data->grd_wd) + z] == 'd')
        tmp->typ = 'D';
}

static void update_y_face(t_data *data, t_face *tmp, int i)
{
    int         x;
    int         y;
    int         z;

    z = 0;
    x = (int)data->array[i].x;
    y = (int)data->array[i].y;
    if ((data->array[i].y - data->plr.y) < 0)
        (tmp->dir = 'N', z--);
    else if (0 < (data->array[i].y - data->plr.y))
        tmp->dir = 'S';
    if ((i == (data->wnd_wd - 1)) || (data->array[i + 1].y != \
        tmp->y_ref))
        tmp->height_2 = get_height(data, i);
    if (data->map[(y / data->grd_ht) + z][(x / data->grd_wd)] == '1')
        tmp->typ = 'W';
    if (data->map[(y / data->grd_ht) + z][(x / data->grd_wd)] == 'd')
        tmp->typ = 'D';
}

static void init_face(t_data *data, t_face *tmp, int i)
{
    if (data->array[i].x != tmp->x_ref)
        tmp->fix = 'Y';
    else if (data->array[i].y != tmp->y_ref)
        tmp->fix = 'X';
    if (tmp->height_1 == -1)
        tmp->height_1 = get_height(data, i);
    if ((i == (data->wnd_wd - 1)) || \
        (data->array[i + 1].x != tmp->x_ref))
        tmp->height_2 = get_height(data, i);
}

t_face  *ft_create_list(t_data *data)
{
    int         i;
    t_face      *tmp[2];

    i = -1;
    tmp[0] = new_node(data->array[0].x, \
        data->array[0].y);
    tmp[1] = tmp[0];
    while (++i < data->wnd_wd)
    {
        if (tmp[0]->fix == 'U')
            init_face(data, tmp[0], i);
        else if ((tmp[0]->fix == 'X') && \
            (data->array[i].x == tmp[0]->x_ref))
            update_x_face(data, tmp[0], i);  
        else if ((tmp[0]->fix == 'Y') && \
            (data->array[i].y == tmp[0]->y_ref))
            update_y_face(data, tmp[0], i);
        else if (new_face(data, &tmp[0], i))
            return (ft_free_lst(tmp[1]), NULL);
        tmp[0]->rays++;
    }
    return (tmp[1]);
}

####################

# include "cube.h"

static int new_face(t_data *data, t_face **tmp, int i)
{
    (*tmp)->next = new_node(data->array[i].x, \
        data->array[i].y);
    if (!(*tmp)->next)
        return (-1);
    (*tmp) = (*tmp)->next;
    return (0);
}

static void update_x_face(t_data *data, t_face *tmp, int i)
{  
    if ((i == (data->wnd_wd - 1)) || \
        (data->array[i + 1].x != tmp->x_ref))
        tmp->height_2 = get_height(data, i);
    else if (tmp->dir == 'U' && \
        ((data->array[i].x - data->plr.x) < 0))
        tmp->dir = 'N';
    else
        tmp->dir = 'S';
    
}

static void update_y_face(t_data *data, t_face *tmp, int i)
{ 
    if ((i == (data->wnd_wd - 1)) || \
        (data->array[i + 1].y != tmp->y_ref))
        tmp->height_2 = get_height(data, i);
    else if (tmp->dir == 'U' && \
        ((data->array[i].y - data->plr.y) < 0))
        tmp->dir = 'E';
    else
        tmp->dir = 'W';
}

static void init_face(t_data *data, t_face *tmp, int i)
{
    if (data->array[i].x != tmp->x_ref)
        tmp->fix = 'Y';
    else if (data->array[i].y != tmp->y_ref)
        tmp->fix = 'X';
    if (tmp->height_1 == -1)
        tmp->height_1 = get_height(data, i);
    if ((i == (data->wnd_wd - 1)) || \
        (data->array[i + 1].x != tmp->x_ref))
        tmp->height_2 = get_height(data, i);
}

t_face  *ft_create_list(t_data *data)
{
    int         i;
    t_face      *tmp[2];

    i = -1;
    tmp[0] = new_node(data->array[0].x, \
        data->array[0].y);
    tmp[1] = tmp[0];
    while (++i < data->wnd_wd)
    {
        if (tmp[0]->fix == 'U')
            init_face(data, tmp[0], i);
        else if ((tmp[0]->fix == 'X') && \
            (data->array[i].x == tmp[0]->x_ref))
            update_x_face(data, tmp[0], i);  
        else if ((tmp[0]->fix == 'Y') && \
            (data->array[i].y == tmp[0]->y_ref))
            update_y_face(data, tmp[0], i);
        else if (new_face(data, &tmp, i))
            retrun (ft_free_lst(tmp[1]), NULL);
        tmp[0]->rays++;
    }
    return (tmp[1]);
}