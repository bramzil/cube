# include "cube.h"

void    ft_fill_img(mlx_image_t *img)
{
    int     i;
    int     j;

    j = -1;
    while (++j < img->height)
    {
        i = -1;
        while (++i < img->width)
            mlx_put_pixel(img, i, j, 0xff0000ff);
    }

}

static int ft_mini_map(t_data *data)
{
    int     i;
    int     j;

    j = -1;
    while (data->map[++j])
    {
        i = -1;
        while (data->map[j][++i])
        {
            if (data->map[j][i] == '1')
                mlx_image_to_window(data->mlx, \
                    data->wall_img, (i * 50), (j * 50));

        }
    }
    return (0);
}

int main()
{
    t_plr   plr;
    char    *map = "1111111111 1000000001 1000011111 \
                    1110000001 1110111111 1110000001 \
                    1100000011 1011110001 1000000001 \
                    1111111111";
    t_data  data;

    plr.d = 0;
    plr.x = 100;
    plr.y = 100;
    data.plr = &plr;
    data.map = ft_split(map, ' ');
    if (!data.map)
        return (printf("ft_split fails!!\n"));
    data.mlx = mlx_init(500, 500, "cube", 0);
    data.wall_img = mlx_new_image(data.mlx, 50, 50);
    data.rays_img = mlx_new_image(data.mlx, 500, 500);
    mlx_image_to_window(data.mlx, data.rays_img, 0, 0);
    ft_fill_img(data.wall_img);
    mlx_key_hook(data.mlx, ft_move_plr, &data);
    ft_mini_map(&data);
    mlx_loop(data.mlx);
    return (0);
}