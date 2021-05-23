/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:23:51 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 16:23:51 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_read_data(t_info *info)
{
	int		i;
	char	p_dir;

	i = 0;
	while (i < 2)
		if (info->map.res[i++] == 0)
			return (-1);
	i = 0;
	while (i < 5)
		if (info->map.t_path[i++] == NULL)
			return (-1);
	if (info->map.f_color == -1 || info->map.c_color == -1)
		return (-1);
	if (info->map.height == 0 || info->map.map == NULL)
		return (-1);
	p_dir = set_player_pos(info);
	if (p_dir == 0)
		return (-1);
	set_player_dir(p_dir, info);
	if (is_map_closed(info, &(info->map)) == -1)
		return (-1);
	if (get_sprite_num(info, &(info->sp)) == -1)
		return (-1);
	return (0);
}

int	get_sprite_num(t_info *info, t_sprite *sp)
{
	sp->num = count_sprite(info);
	if (sp->num == 0)
		return (0);
	sp->x = malloc(sizeof(double) * sp->num);
	sp->y = malloc(sizeof(double) * sp->num);
	sp->order = malloc(sizeof(int) * sp->num);
	sp->dist = malloc(sizeof(double) * sp->num);
	if (!(sp->x) || !(sp->y) || !(sp->order) || !(sp->dist))
		return (-1);
	return (0);
}

int	is_map_closed(t_info *info, t_map *map)
{
	int	i;
	int	player_x;
	int	player_y;

	player_x = (int)info->posx;
	player_y = (int)info->posy;
	map->tmpmap = malloc(sizeof(char *) * (map->height + 2));
	if (map->tmpmap == NULL)
		return (-1);
	i = 0;
	while (i < (map->height + 2))
	{
		map->tmpmap[i] = malloc(sizeof(char) * (map->max_width + 3));
		if (map->tmpmap[i] == NULL)
			return (free_char_arr(&(map->tmpmap), 0, i));
		i++;
	}
	convert_map(map);
	if (floodfill(map->tmpmap, player_x + 1, player_y + 1, 1) == 0)
		return (free_char_arr(&(map->tmpmap), 0, i));
	free_char_arr(&(map->tmpmap), 0, map->height + 2);
	return (0);
}

void	convert_map(t_map *map)
{
	int	i;
	int	j;
	int	height;
	int	width;

	i = 0;
	height = map->height;
	width = map->max_width;
	while (i <= height + 1)
	{
		j = 0;
		while (j <= width + 1)
		{
			if (i == 0 || j == 0 || i == height + 1 || j == width + 1)
				map->tmpmap[i][j] = 'Z';
			else if (j > my_strlen(map->map[i - 1]))
				map->tmpmap[i][j] = ' ';
			else
				map->tmpmap[i][j] = map->map[i - 1][j - 1];
			j++;
		}
		map->tmpmap[i][j] = '\0';
		i++;
	}
}

int	floodfill(char **map, int x, int y, int flag)
{
	if (flag != 0)
	{
		if (my_chrstr(map[y][x], "EWSN") == 0)
			map[y][x] = '5';
		if (map[y][x + 1] == 'Z' || map[y][x - 1] == 'Z')
			flag = 0;
		if (map[y + 1][x] == 'Z' || map[y - 1][x] == 'Z')
			flag = 0;
		if (my_chrstr(map[y][x + 1], " 02") == 1)
			flag = floodfill(map, x + 1, y, flag);
		if (my_chrstr(map[y][x - 1], " 02") == 1)
			flag = floodfill(map, x - 1, y, flag);
		if (my_chrstr(map[y + 1][x], " 02") == 1)
			flag = floodfill(map, x, y + 1, flag);
		if (my_chrstr(map[y - 1][x], " 02") == 1)
			flag = floodfill(map, x, y - 1, flag);
	}
	return (flag);
}
