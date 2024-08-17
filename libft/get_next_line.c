/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:27:09 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/17 14:30:59 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include <fcntl.h>


# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

static char    *read_line(char *rst, int fd)
{
    char    *all;
    char    *tmp;
    int     r_bytes;
    char    buf[BUFFER_SIZE + 1];

    all = rst;
    r_bytes = 1;
    while (0 < r_bytes)
    {
        tmp = all;
        if ((r_bytes = read(fd, buf, BUFFER_SIZE)) == -1)
            return (free(tmp), write(2, "read fun failed!!\n", 19), NULL);
        if (!r_bytes)
            return (all);
        buf[r_bytes] = '\0';
        if (!(all = ft_strjoin(all, buf)))
            return (free(tmp), write(2, "ft_strjoin failed!!\n", 21), NULL);
        free (tmp);
        if (-1 < ft_strchar(all, '\n'))
            break;
    }
    return (all);
}


char *get_next_line(int fd)
{
    char        *all;
    int         l_end;
    char        *line;
    static char *rst[255];

    if ((fd < 0) || (255 < fd) || (BUFFER_SIZE <= 0))
        return (NULL);
    all = read_line(rst[fd], fd);
    rst[fd] = NULL;
    l_end = ft_strchar(all, '\n');
    if (-1 < l_end && all[l_end + 1])
    {
        if (!(rst[fd] = ft_substr(all, (l_end  + 1), \
            (ft_strlen(all) - l_end - 1))))
            return (free(all), write(2, "ft_substr " \
                "failed!!\n", 20), NULL);
        if (!(line = ft_substr(all, 0, (l_end + 1))))
            return (free(all), free(rst[fd]), \
                write(2, "ft_substr failed!!\n", 20), NULL);
        free (all);
    }
    else
        line = all;
    return (line);
}
