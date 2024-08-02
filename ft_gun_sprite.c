/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gun_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:22:31 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/03 12:21:50 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

mlx_image_t *load_gun_sprite(mlx_t *mlx, char *path)
{
    mlx_image_t     *image;
    mlx_texture_t   *texture;

    image = NULL;
    texture = mlx_load_png(path);
    if (texture)
        image = mlx_texture_to_image(mlx, texture);
    return (image);
}

int init_gun(t_data *data)
{
    data->gun.i = 0;
    data->gun.sht = 'N';
    data->gun.nbr_sht = 10;
    data->gun.arr = (char **)malloc(sizeof(char *) * 13);
    if (!data->gun.arr)
        return (-1);
    data->gun.arr[0] = "gun/gun0.png";
    data->gun.arr[1] = "gun/gun1.png";
    data->gun.arr[2] = "gun/gun2.png";
    data->gun.arr[3] = "gun/gun3.png";
    data->gun.arr[4] = "gun/gun4.png";
    data->gun.arr[5] = "gun/gun5.png";
    data->gun.arr[6] = "gun/gun6.png";
    data->gun.arr[7] = "gun/gun7.png";
    data->gun.arr[8] = "gun/gun8.png";
    data->gun.arr[9] = "gun/gun9.png";
    data->gun.arr[10] = "gun/gun10.png";
    data->gun.arr[11] = "gun/gun11.png";
    data->gun.arr[12] = "gun/gun12.png";
    data->gun.img = load_gun_sprite(data->mlx, \
        data->gun.arr[0]);
    return (0);
}

void    reload(t_data *data)
{
    static int      i;

    if (data->gun.nbr_sht == 0)
    {
        i++;
        mlx_delete_image(data->mlx, data->gun.img);
        data->gun.img = load_gun_sprite(data->mlx, \
            data->gun.arr[(i + 3)]);
        mlx_image_to_window(data->mlx, data->gun.img, \
            ((data->wnd_wd / 2) - (data->gun.img->width / 2)), \
            (data->wnd_ht - data->gun.img->height));
        if (i == 8)
        {
            i = 0;
            data->gun.nbr_sht = 10;
        }
    }
}

void    shut(t_data *data)
{
    if (data->gun.sht == 'S')
    {
        if (data->gun.nbr_sht == 0)
            reload(data);
        else
        {
            data->gun.i++;
            mlx_delete_image(data->mlx, data->gun.img);
            data->gun.img = load_gun_sprite(data->mlx, \
                data->gun.arr[data->gun.i % 4]);
            mlx_image_to_window(data->mlx, data->gun.img, \
                ((data->wnd_wd / 2) - (data->gun.img->width / 2)), \
                (data->wnd_ht - data->gun.img->height));
            if (data->gun.i == 4)
            {
                data->gun.i = 0;
                data->gun.nbr_sht--;
                data->gun.sht = 'N';
            }
        }
    }
}
