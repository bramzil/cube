# include "cube.h"

static int  ft_draw_cercle(mlx_image_t *img, double i, double j)
{
    double      x;
    double      y;
    double      incr;
    double      angle;

    angle = 0;
    incr = ((2 * M_PI) / 360);
    while (angle < (2 * M_PI))
    {
        x = i + (1.5 * cos(angle));
        y = j + (1.5 * sin(angle));
        mlx_put_pixel(img, x, y, 0x00ff00ff);
        angle += incr;
    }
    return (0);
}

int ft_mini_map(t_data *data)
{
    int     i;
    int     j;
    int     i_ref;
    int     j_ref;

    j_ref = (int)(data->plr.y - 60);
    i_ref = (int)(data->plr.x - 60);
    j = j_ref;
    while (++j < (int)(data->plr.y + 60))
    {
        i = i_ref;
        while (++i < ((int)data->plr.x + 60))
        {
            if ((0 < j) && (j < (data->grd_ht * 22)) && (0 < i) && \
                (i < (data->grd_wd * 10)) && \
                (data->map[(int)(j / data->grd_ht)][(int)(i / data->grd_wd)] == '1'))
                mlx_put_pixel(data->rays_img, i - i_ref, j - j_ref, 0xff0000aa);
        }
    }
    ft_draw_cercle(data->rays_img, (data->rays_img->width / 2), \
        (data->rays_img->height / 2));
    return (0);
}