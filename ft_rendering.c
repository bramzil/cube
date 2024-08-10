# include "cube.h"

static int get_x_offset(t_data *data, t_face *tmp, double x)
{
    int     x_offset;

    x_offset = 0;
    if (data && data->inter_arr && tmp)
    {
        if (tmp->fix == 'X')
            x_offset = ((int)((int)data->inter_arr[(int)x].y % \
                data->grd_ht));
        else if (tmp->fix == 'Y')
            x_offset = ((int)((int)data->inter_arr[(int)x].x % \
                data->grd_wd));
    }
    return (x_offset);
} 

static void indices(t_data *data, t_face *tmp, int *tab, int x)
{
    if (data && data->inter_arr && tab)
    {
        if (tmp && tmp->fix == 'X')
        {
            tab[1] = (data->inter_arr[x].y / data->grd_ht);
            tab[0] = (data->inter_arr[x].x / data->grd_wd) - \
                1 * (data->inter_arr[x].x < data->plr.x);
        }
        else if (tmp && tmp->fix == 'Y')
        {
            tab[0] = (data->inter_arr[x].x / data->grd_wd);
            tab[1] = (data->inter_arr[x].y / data->grd_ht) - \
                1 * (data->inter_arr[x].y < data->plr.y);
        }
    }
}

static void  put_pixel(t_data *data, t_point *pos, int *ind)
{
    char        **map;

    if (data && data->map && data->proj_img)
    {
        map = data->map;
        if (map[ind[1]][ind[0]] == '1')
            mlx_put_pixel(data->proj_img, pos->x, pos->y, \
                data->W_texture[ind[2]]);
        else if (map[ind[1]][ind[0]] == 'd')
            mlx_put_pixel(data->proj_img, pos->x, pos->y, \
                data->D_texture[ind[2]]);
    }
}

static void  colum(t_data *data, t_face *tmp, t_point *offset, int x)
{
    double      top;
    int         ind[3];
    t_point     pixel_pos;

    pixel_pos.x = x;
    indices(data, tmp, ind, x);
    if (data && tmp && offset)
    {
        pixel_pos.y = data->plr.h - (tmp->height / 2.0);
        top = pixel_pos.y;
        while (pixel_pos.y < (data->plr.h + (tmp->height / 2.0)))
        {
            offset->y = (int)((pixel_pos.y - top) * \
                (data->grd_ht / tmp->height));
            if (0 < pixel_pos.y && pixel_pos.y < data->wnd_ht)
            {
                ind[2] = (data->grd_wd * offset->y) + offset->x;
                put_pixel(data, &pixel_pos, ind);
            }
            pixel_pos.y++;
        }
    }
}

void    ft_render_wall(t_data *data)
{
    int         i;
    int         x;
    t_face      *tmp;
    t_point     offset;

    x = 0;
    tmp = data->face_lst;
    while (data && data->proj_img && \
        data->inter_arr && tmp)
    {
        i = -1;
        while ((++i < tmp->rays) && \
            (x < data->wnd_wd))
        {
            offset.x = get_x_offset(data, tmp, x);
            tmp->height = get_height(data, x);
            colum(data, tmp, &offset, x);
            x++;
        }
        tmp = tmp->next;
    }
}
