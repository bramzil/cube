# include "cube.h"

int ft_create_window(t_data  *data)
{
    if (!(data->mlx = mlx_init(data->wnd_wd, data->wnd_ht, \
        "cube", 0)))
        return (printf("init mlx fails!!\n"));
    if (!(data->map_img = mlx_new_image(data->mlx, 120, 120)))
        return (printf("data->map_img fails!!\n"));
    if (!(data->proj_img = mlx_new_image(data->mlx, \
        data->wnd_wd, data->wnd_ht)))
        return (printf("data->proj_img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->proj_img, 0, 0))
        return (printf("data->proj_img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->map_img, 10, 10))
        return (printf("data->wall__img fails!!\n"));
    if (init_gun_arr(data))
        return (printf("init gun array fails!!"));
    return (0);
}

int main()
{
    t_data  data;
    char    *map = "1111111111 1000000001 1000010101 \
                    1100000001 10101d11d1 1010000001 \
                    1000000011 1011d10001 1000000001 \
                    1111111111";

    data.fact = 4.0;
    data.plr.d = 0;
    data.plr.x = 370;
    data.plr.y = 370;
    data.grd_ht = 64;
    data.grd_wd = 64;
    data.wnd_ht = 700;
    data.wnd_wd = 1100;
    data.doors_nbr = 3;
    data.face_lst = NULL;
    data.w_text.wd = 64;
    data.w_text.ht = 64;
    data.gun.i = 0;
    data.gun.sht = 'N';
    data.gun.nbr_sht = 10;
    data.plr.h = data.wnd_ht / 2;
    data.d_text.wd = 64;
    data.d_text.ht = 64;
    data.map = ft_split(map, ' ');
    if (!data.map)
        return (printf("ft_split fails!!\n"));
    if (ft_create_window(&data))
        return (-1);
    data.d_text.tb = get_texture_arr(&data, "door.png");
    data.w_text.tb = get_texture_arr(&data, "wall.png");
    data.inter_arr = malloc(sizeof(t_point) * data.wnd_wd);
    if (!data.inter_arr)
        return (printf("inter_arr allocation fails!!\n"));
    data.door_arr = malloc(sizeof(t_door) * data.doors_nbr);
    if (!data.door_arr)
        return (printf("door_arr allocation fails!!\n"));
    fill_door_array(&data);
    ft_mini_map(&data);
    mlx_loop_hook(data.mlx, animation, &data);
    mlx_loop(data.mlx);
    return (0);
}