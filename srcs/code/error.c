/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:57:11 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:41 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void	error_cub3d(char *s)
{
	ft_putstr_fd("\x1b[31mError\n", 1);
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
	exit(0);
}

void	ft_fill_texture(t_cub3d *cub3d)
{
	if (!(cub3d->textura_norte.tex_norte =
		mlx_xpm_file_to_image(cub3d->data.mlx,
		cub3d->map.ruta_norte, &cub3d->player.tex_w, &cub3d->player.tex_h)))
		error_cub3d("\t------> \x1b[36mThe NO texture does not exist!");
	else if (!(cub3d->textura_sur.tex_sur =
		mlx_xpm_file_to_image(cub3d->data.mlx,
		cub3d->map.ruta_sur, &cub3d->player.tex_w, &cub3d->player.tex_h)))
		error_cub3d("\t------> \x1b[36mThe SO texture does not exist!");
	else if (!(cub3d->textura_oeste.tex_oeste =
		mlx_xpm_file_to_image(cub3d->data.mlx, cub3d->map.ruta_este,
		&cub3d->player.tex_w, &cub3d->player.tex_h)))
		error_cub3d("\t------> \x1b[36mThe WE texture does not exist!");
	else if (!(cub3d->textura_este.tex_este =
		mlx_xpm_file_to_image(cub3d->data.mlx,
		cub3d->map.ruta_oeste, &cub3d->player.tex_w, &cub3d->player.tex_h)))
		error_cub3d("\t------> \x1b[36mThe EA texture does not exist!");
	if (!(cub3d->sprite.tex_add = mlx_xpm_file_to_image(cub3d->
		data.mlx, cub3d->map.ruta_sprite,
		&cub3d->sprite.tex_w, &cub3d->sprite.tex_h)))
		error_cub3d("\t------> \x1b[36mThe SPRITE texture does not exist!");
}

int		ft_control_error(int argc, char **argv)
{
	char	*tmp;
	int		i;

	i = 0;
	if (argc < 2 || argc > 3)
		error_cub3d("\t------> \x1b[36mInvalid argument numbers");
	else if (argc == 2 || argc == 3)
	{
		if ((tmp = ft_strchr(argv[1], '.')) == NULL)
			error_cub3d("\t------> \x1b[36mInvalid map: \".cub\".");
		if ((ft_strncmp(tmp, ".cub\0", 5)) != 0)
			error_cub3d("\t------> \x1b[36mInvalid map: \".cub\".");
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 7) != 0)
				error_cub3d("\t------> \x1b[36mInvalid argument: --save");
		}
	}
	return (0);
}

int		ft_parseo(t_cub3d *cub3d, char **argv)
{
	char	*line;
	int		fd;
	int		x;

	x = 0;
	line = NULL;
	cub3d->map.i = 0;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error_cub3d("\t------> \x1b[36mInvalid map!");
	while ((cub3d->map.i = get_next_line(fd, &line)) > 0)
	{
		ft_check_lines(cub3d, line);
		free(line);
		line = NULL;
		x++;
	}
	ft_check_lines(cub3d, line);
	close(fd);
	free(line);
	line = NULL;
	(cub3d->map.xpvu < 3 || cub3d->map.color_f == -1 || cub3d->
		map.color_c == -1) ? error_cub3d("\t------> \x1b[36mInvalid map!") : 0;
	ft_reservar_map(cub3d);
	ft_fill_map(cub3d, argv);
	return (0);
}
