# include "cube.h"

void    ft_clear_image(mlx_image_t *img)
{
    int     i;
    int     j;

    j = -1;
    while (++j < img->height)
    {
        i = -1;
        while (++i < img->width)
            mlx_put_pixel(img, i, j, 0x00);
    }
}

static void ft_for_back_ward(t_data *data, int keycode)
{
    double      x;
    double      y;

    if (keycode == 87)
    {
        x = data->plr.x + (10 * cos(data->plr.d));
        y = data->plr.y + (10 * sin(data->plr.d) * -1);
    }
    else if (keycode == 83)
    {
        x = data->plr.x + (10 * cos(data->plr.d) * -1);
        y = data->plr.y + (10 * sin(data->plr.d));
    }
    if (!ft_check_next(data, x, y))
        (data->plr.x = x, data->plr.y = y);
}

static void ft_go_left_right(t_data *data, int keycode)
{
    double       x;
    double       y;
    double       angle;

    if (keycode == 65)
    {
        angle = real_angle(data->plr.d + \
            (M_PI / 2));
        x = data->plr.x + (double)(10 * cos(angle));
        y = data->plr.y + (double)(10 * sin(angle) * -1);
    }
    else if (keycode == 68)
    {
        angle = real_angle(data->plr.d + \
            (M_PI + (M_PI / 2)));
        x = data->plr.x + (double)(10 * cos(angle));
        y = data->plr.y + (double)(10 * sin(angle) * -1);
    }
    if (!ft_check_next(data, x, y))
        (data->plr.x = x, data->plr.y = y);
}

void ft_move_plr(mlx_key_data_t hook, void *arg)
{
    t_data      *data;

    data = (t_data *)arg;
    if (hook.key == 32)
        data->gun.sht = 'S';
    else
    {
        if (hook.key == 65 || hook.key == 68)
            ft_go_left_right(data, hook.key);
        else if ((hook.key == 83) || (hook.key == 87))
            ft_for_back_ward(data, hook.key);
        else if (hook.key == 262)
            data->plr.d = real_angle(data->plr.d - \
                (double)(6 * (M_PI / 180)));
        else if (hook.key == 263)
            data->plr.d = real_angle(data->plr.d + \
                (double)(6 * (M_PI / 180)));
        ft_clear_image(data->rays_img);
        ft_clear_image(data->ddd__img);
        ft_cast_rays(data);
    }
}

