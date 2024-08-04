/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gun_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:22:31 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/04 15:30:28 by bramzil          ###   ########.fr       */
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
    char    *str = {
                    "gun/gun0.png " \
                    "gun/gun1.png " \
                    "gun/gun2.png " \
                    "gun/gun3.png " \
                    "gun/gun4.png " \
                    "gun/gun5.png " \
                    "gun/gun6.png " \
                    "gun/gun7.png " \
                    "gun/gun8.png " \
                    "gun/gun9.png " \
                    "gun/gun10.png " \
                    "gun/gun11.png " \
                    "gun/gun12.png"};
    data->gun.i = 0;
    data->gun.sht = 'N';
    data->gun.nbr_sht = 10;
    data->gun.arr = ft_split(str, ' ');
    if (!data->gun.arr)
        return (-1);
    data->gun.img = load_gun_sprite(data->mlx, \
        data->gun.arr[0]);
    return (0);
}

void    reload(t_data *data)
{
    static int      i;
    static int      counter;

    if (!data->gun.nbr_sht && !counter)
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
        counter = 2;
    }
    counter--;
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
