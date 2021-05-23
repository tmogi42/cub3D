/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmogi <tmogi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:24:05 by tmogi             #+#    #+#             */
/*   Updated: 2021/05/23 16:25:46 by tmogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

int	error(int fd, int result, t_info *info)
{
	printf("Error\n");
	if (result == -1)
		printf("[ Something wrong inqut args ]\n");
	else if (result == -2)
		printf("[ Failed to INITIALIZE paramaters ]\n");
	else if (result == -3)
		printf("[ Failed to READ cub_file ]\n");
	else if (result == -4)
		printf("[ Failed to LOAD texture ]\n");
	else if (result == -5)
		printf("[ Failed to OPEN game window ]\n");
	else if (result == -6)
		printf("[ Failed to CREATE bitmap_image ]\n");
	if (result <= -3)
		clear_all_params(info);
	close(fd);
	return (-1);
}

int	check_file_name(char *val)
{
	int	i;

	i = 0;
	if (my_strcmp(val, ".cub") == 0 || my_strstr(val, "/.cub") == 1)
		return (-1);
	while (val[i] != '\0')
	{
		if (val[i] == '.')
		{
			if (my_strcmp(&(val[i]), ".cub") == 0)
				return (0);
		}
		i++;
	}
	return (-1);
}

int	judge_input_args(int argc, char **argv)
{
	int	fd;

	fd = -1;
	if (argc == 2)
	{
		if (check_file_name(argv[1]) == 0)
			fd = open(argv[1], O_RDONLY);
	}
	else if (argc == 3)
	{
		if (check_file_name(argv[1]) == 0 && my_strcmp(argv[2], "--save") == 0)
			fd = open(argv[1], O_RDONLY);
	}
	return (fd);
}

int	check_color_val(t_map *map)
{
	if (map->c != 2)
		return (-1);
	if (map->rgb[0] == -1)
		return (-1);
	if (map->rgb[1] == -1)
		return (-1);
	if (map->rgb[2] == -1)
		return (-1);
	map->rgb[0] = -1;
	map->rgb[1] = -1;
	map->rgb[2] = -1;
	return (0);
}

int	check_start_zero(char *line)
{
	int	i;
	int	num_f;
	int	zero_f;

	i = 0;
	num_f = 0;
	zero_f = 0;
	while (line[i] != '\0')
	{
		if (line[i] < '0' || '9' < line[i])
		{
			num_f = 0;
			zero_f = 0;
		}
		else if (zero_f == 1 && num_f == 0)
			return (1);
		else if (line[i] == '0')
			zero_f = 1;
		else
			num_f = 1;
		i++;
	}
	return (0);
}
