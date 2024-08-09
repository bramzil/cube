# include "cube.h"

mlx_image_t *load_image(t_data *data, char *path)
{
    mlx_image_t         *image;
    mlx_texture_t       *texture;

    texture = mlx_load_png(path);
    if (!texture)
        return (NULL);
    image = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_textur(texture);
    return (image);
}

int32_t *get_texture_arr(t_data *data, char *path)
{
    int         i;
    int         j;
    int         byte[4];
    int32_t     *pix_arr;
    mlx_image_t *image;

    j = 0;
    i = -1;
    image = load_image(data, path);
    if (!image)
        return (NULL);
    pix_arr = malloc(sizeof(int32_t) * image->width * \
        image->height);
    if (!pix_arr)
        return (NULL);
    while (++i < (image->width * image->height * 4))
    {
        byte[0] = image->pixels[i];
        byte[1] += image->pixels[++i];
        byte[2] += image->pixels[++i];
        byte[3] += image->pixels[++i];
        pix_arr[j++] = (byte[0] << 24 | \
            byte[1] << 16 | byte[2] << 8 | byte[3]);
    }
    mlx_delete_image(data->mlx, image);
    return (pix_arr);
}