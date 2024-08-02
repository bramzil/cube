# include "cube.h"


int ft_mini_map(t_data *data)
{
    int     i;
    int     j;
    int     i_ref;
    int     j_ref;
    int     grd_wd;
    int     grd_ht;

    grd_wd = data->grd_wd / data->fact;
    grd_ht = data->grd_ht / data->fact;
    j_ref = (int)((data->plr.y / data->fact) - 60);
    i_ref = (int)((data->plr.x / data->fact) - 60);
    j = j_ref;
    i = i_ref - 1;
    while (j < (int)((data->plr.y / data->fact) + 60))
    {
        i++;
        if ((0 < j) && (j < (grd_ht * 10)) && (0 < i) && \
            (i < (grd_wd * 10)) && (data->map[(int)(j / \
            grd_ht)][(int)(i / grd_wd)] != '0'))
            mlx_put_pixel(data->map_img, (i - i_ref), (j - \
                j_ref), 0xf0f0f0aa);
        if ((int)((data->plr.x / data->fact) + 60) <= i)
            (i = i_ref - 1, j++);
    }
    return (0);
}
