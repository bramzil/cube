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

mlx_keyfunc ft_move_plr(mlx_key_data_t key, t_data *data)
{
    if (key.key == 65)
        data->plr->x -= 10;
    else if (key.key == 68)
        data->plr->x += 10;
    else if (key.key == 83)
        data->plr->y += 10;
    else if (key.key == 87)
        data->plr->y -= 10;
    else if (key.key == 262)
    {
        data->plr->d -= 10;
        if (data->plr->d < 0)
            data->plr->d -= 360;
    }
    else if (key.key == 263)
    {
        data->plr->d += 10;
        data->plr->d %= 360;
    }
    ft_clear_image(data->rays_img);
    ft_drop_rays(data);
}