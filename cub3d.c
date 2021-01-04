/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:22 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:53:20 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./srcs/code/cub3dlib.h"

void	my_mlx_pixel_put(t_cub3d *cub3d, int x, int y, int color)
{
	char *dst;

	dst = (char *)cub3d->data.addr + (y * cub3d->data.line_lenght + x
		* (cub3d->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		ft_exit(t_cub3d *cub3d)
{
	write(1, "\n\x1b[36m-------> Game over <-------\n", 33);
	mlx_destroy_window(cub3d->data.mlx, cub3d->data.win);
	exit(0);
	return (0);
}

void	ft_init_structs(t_cub3d *cub3d)
{
	cub3d->player.dirx = -1;
	cub3d->player.diry = 0;
	cub3d->player.planex = 0;
	cub3d->player.planey = 0.66;
	cub3d->player.movespeed = 0.21;
	cub3d->player.rotspeed = 0.042;
	cub3d->map.ruta_norte = NULL;
	cub3d->map.ruta_sur = NULL;
	cub3d->map.ruta_este = NULL;
	cub3d->map.ruta_oeste = NULL;
	cub3d->map.ruta_sprite = NULL;
	cub3d->map.tmp1 = NULL;
	cub3d->map.tmp2 = NULL;
	cub3d->map.xpvu = 0;
	cub3d->sprite.num = 0;
	cub3d->player.nswe = '\0';
	cub3d->map.color_f = -1;
	cub3d->map.color_c = -1;
}

int		main(int argc, char **argv)
{
	t_cub3d cub3d;

	cub3d.data.arg = argc;
	ft_init_structs(&cub3d);
	ft_parseo(&cub3d, argv);
	cub3d.data.mlx = mlx_init();
	cub3d.data.win =
		mlx_new_window(cub3d.data.mlx, cub3d.map.w, cub3d.map.h, "Cub3D");
	cub3d.data.img = mlx_new_image(cub3d.data.mlx, cub3d.map.w, cub3d.map.h);
	cub3d.data.addr =
		mlx_get_data_addr(cub3d.data.img, &cub3d.data.bits_per_pixel,
		&cub3d.data.line_lenght, &cub3d.data.endian);
	ft_fill_texture(&cub3d);
	ft_control_error(argc, argv);
	mlx_hook(cub3d.data.win, 2, (1L << 0), ft_keypress, &cub3d);
	mlx_hook(cub3d.data.win, 3, (1L << 0), ft_keyrelease, &cub3d);
	mlx_hook(cub3d.data.win, 17, (17L << 0), ft_exit, &cub3d);
	mlx_loop_hook(cub3d.data.mlx, ft_raycasting, &cub3d);
	mlx_loop(cub3d.data.mlx);
}
