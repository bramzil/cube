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
    data->gun.arr = (char **)malloc(sizeof(char *) * 4);
    if (!data->gun.arr)
        return (-1);
    data->gun.arr[0] = "gun/gun0.png";
    data->gun.arr[1] = "gun/gun1.png";
    data->gun.arr[2] = "gun/gun2.png";
    data->gun.arr[3] = "gun/gun3.png";
    data->gun.img = load_gun_sprite(data->mlx, \
        data->gun.arr[0]);
    return (0);
}

void    shut(t_data *data)
{
    if (data->gun.sht == 'S')
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
            data->gun.sht = 'N';
            data->gun.i = 0;
        }
    }
}
