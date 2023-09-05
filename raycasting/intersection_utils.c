/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:49:52 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/05 11:14:58 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int is_up(float angle)
{
    if(angle >= M_PI)
        return 1;
    return -1;
}
int is_right(float angle)
{
    if(angle > 3 * M_PI / 2 || angle  < M_PI / 2)
        return 1;
    return -1;
}


t_ray* ray_data (t_map map,float angle, int flag, t_coord inter_type)
{
    t_ray *ray =NULL; 
    
    ray = malloc(sizeof(t_ray));
    ray->x = inter_type.x;
    ray->y = inter_type.y;
    ray->distance = floor(inter_type.distance) * cos(angle - map.player_pos.rotation_angle);
    ray->angle = angle;
    ray->projection_wall = floor((FRAME_HEIGHT * ((map.max_width*FRAME_WIDTH /2) / tan(FOV / 2)))/ray->distance);
    //printf("%f\n",  ray->projection_wall);
    if(flag == 1)
        ray->hit_wall_h = 1;
    else
        ray->hit_wall_v = 1;
    return ray;
}


void free_rays(t_list **list)
{
    t_list *tmp_list =NULL;
    t_ray *tmp_ray;
    t_list *next;
    tmp_list = *list;
    
    while(tmp_list)
    {
        tmp_ray=(t_ray*)((tmp_list)->content);
        if(tmp_ray)
        {
            free(tmp_ray);
            tmp_ray =NULL;
        }
        next = (tmp_list)->next;
        if(tmp_list)
        {
            free(tmp_list);
            tmp_list =NULL;
        }
        tmp_list = next;
    }
}
