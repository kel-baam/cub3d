/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:46:05 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/16 21:27:04 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void line_of_spaces(t_player *player, int *i, char *line)
{
    int len;

    len = ft_strlen(line);
    player->map_cpy[*i] = malloc(sizeof(char) * (len + 3));
    ft_memset(player->map_cpy[*i], ' ', len+2);
    player->map_cpy[*i][len + 2] = '\0';
    (*i)++;
}

void add_spaces_to_line(t_player *player, int *i, char *line)
{
    char *str;
    char *tmp;

    str = ft_strjoin(" ",line);
    tmp = str;
    str = ft_strjoin(str," ");
    ft_free(tmp);
    player->map_cpy[*i] = str;
    (*i)++;
}

void map_cpy(char *line, t_player *player, int *i, int height)
{
    if(*i == 0)
    {
       line_of_spaces(player, i, line);
       add_spaces_to_line(player, i, line);
    }
    else if (*i == height)
    {
       add_spaces_to_line(player, i, line);
       line_of_spaces(player, i, line);
    }
    else
       add_spaces_to_line(player, i, line);
}

void fillArray(t_map *map, t_player *player, char *fileName)
{
    char *line;
    int i;
    int fd;
    int j;
    int count;

    i = 0;
    j = 0;
    count = 0;
    fd = open (fileName,O_RDONLY);
    line = ft_strdup("");
    map->map = malloc(sizeof(char*) * (map->map_height + 1));
    player->map_cpy = malloc(sizeof(char*) * (map->map_height + 3));
    while(line)
    {
       ft_free(line);
       line = getLine(fd);
       if(line)
       {
            if(count >= map->total_height - map->map_height-1)
            {
                map->map[i] = ft_strdup(line);
                map_cpy(line, player, &j, map->map_height);
                i++;  
            }
            count++;
       }
    }
    map->map[i] =  NULL;
    player->map_cpy[j] =  NULL;
    displayArray(player->map_cpy);
}