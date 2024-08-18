/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ky_vl_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:46:14 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/18 18:13:34 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing_bonus.h"

static int count_components(char *line)
{
    int     nbr;

    nbr = 0;
    while (line && *line)
    {
        while (*line && (-1 < ft_strchar(" \t", *line)))
            line++;
        ((*line) && nbr++);
        while (*line && (ft_strchar(" \t", *line) < 0))
            line++;
    }
    if (nbr != 2)
        return (write(2, "line must not contains more " \
            "that two components!!\n", 51), 0);
    return (nbr);
}

char **ft_split_ky_vl(char *line)
{
    int     nbr;
    int     t[3];
    char    **pair;
    
    pair = NULL;
    t[0] = t[1] = t[2] = 0;
    if (!(nbr = count_components(line)))
        return (NULL);
    if (!(pair = malloc(sizeof(char *) * 3)))
        return (write(2, "malloc failed in split " \
            "key value!!\n", 36), NULL);
    while (line && line[t[1]] && nbr--)
    {
        while (line[t[1]] && (-1 < ft_strchar(" \t", line[t[1]])))
            t[0] = ++t[1];
        while (line[t[1]] && (ft_strchar(" \t", line[t[1]]) < 0))
            t[1]++;
        if (!(pair[t[2]++] = ft_substr(line, t[0], t[1] - t[0])))
            return (write(2, "substr fails in split key " \
                "value!!\n", 35), free_2d_arr(pair), NULL);
    }
    pair[t[2]] = NULL;
    return (pair);
}
