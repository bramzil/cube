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
            mlx_put_pixel(img, i, j, 0x00f0000f);
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
                    data->wall_img, (i * 20), (j * 20));
        }
    }
    return (0);
}

int main()
{
    t_plr   plr;
    char    *map = "1111111111 1000000001 1000011101 \
                    1010000001 1110101111 1010000001 \
                    1000000011 1010110001 1000000001 \
                    1111111111";
    t_data  data;

    plr.d = 0;
    plr.x = 40;
    plr.y = 40;
    data.plr = &plr;
    data.map = ft_split(map, ' ');
    if (!data.map)
        return (printf("ft_split fails!!\n"));
    data.mlx = mlx_init(760, 700, "cube", 0);
    data.wall_img = mlx_new_image(data.mlx, 20, 20);
    data.rays_img = mlx_new_image(data.mlx, 200, 200);
    data.img_3d = mlx_new_image(data.mlx, 760, 700);
    data.array = (t_point *)malloc(sizeof(t_point) * 760);
    mlx_image_to_window(data.mlx, data.img_3d, 0, 0);
    mlx_image_to_window(data.mlx, data.rays_img, 0, 0);
    mlx_key_hook(data.mlx, ft_move_plr, &data);
    ft_fill_img(data.wall_img);
    ft_mini_map(&data);
    mlx_loop(data.mlx);
    return (0);
}