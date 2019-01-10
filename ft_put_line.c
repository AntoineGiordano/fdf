/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_set_line.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/12 14:59:37 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/12 14:59:38 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

float	ft_abs(float x)
{
	if (x >= 0)
		return (x);
	else
		return (-x);
}

void	set_pixel(t_image *image, int x, int y, t_color *color)
{
	printf("Debut set pixel\n");
	image->image[4 * (x + y * image->s_l) + 0] = (int)(color->r);
	image->image[4 * (x + y * image->s_l) + 1] = (int)(color->g);
	image->image[4 * (x + y * image->s_l) + 2] = (int)(color->b);
}

void	ft_put_line(t_window *win, t_dot *d1, t_dot *d2)
{
	t_vector	pas;
	int			nbpixels;
	int			i;
	t_color		dcolor;
	t_color		color;

	//printf("Debut put line\n");
	pas.x = d2->x - d1->x;
	pas.y = d2->y - d1->y;
	if (ft_abs(pas.x) > ft_abs(pas.y))
	{
		nbpixels = ft_abs(pas.x);
		pas.y /= ft_abs(pas.x);
		pas.x /= ft_abs(pas.x);
	}
	else
	{
		nbpixels = ft_abs(pas.y);
		pas.x /= ft_abs(pas.y);
		pas.y /= ft_abs(pas.y);
	}
	printf("RGB 1 : %f, %f, %f\n", d1->color.r, d1->color.g, d1->color.b);
	printf("RGB 2 : %f, %f, %f\n", d2->color.r, d2->color.g, d2->color.b);
	dcolor.r = (d2->color.r - d1->color.r) / nbpixels;
	dcolor.g = (d2->color.g - d1->color.g) / nbpixels;
	dcolor.b = (d2->color.b - d1->color.b) / nbpixels;
	printf("Quantum RGB : %f, %f, %f\t Avec n pixels : %i\n", dcolor.r, dcolor.g, dcolor.b, nbpixels);
	i = -1;
	while (++i < nbpixels)
	{
		color.r = d1->color.r + i * dcolor.r;
		color.g = d1->color.g + i * dcolor.g;
		color.b = d1->color.b + i * dcolor.b;

		set_pixel(win->map->image, d1->x + pas.x * i, d1->y + pas.y * i, &color);
	}
}

void	set_pas(t_dot d2, t_dot d3, t_vector *pas, int *nbpixels)
{
	pas->x = d3.x - d2.x;
	pas->y = d3.y - d2.y;
	if (ft_abs(pas->x) > ft_abs(pas->y))
	{
		*nbpixels = ft_abs(pas->x);
		pas->y /= ft_abs(pas->x);
		pas->x /= ft_abs(pas->x);
	}
	else
	{
		*nbpixels = ft_abs(pas->y);
		pas->x /= ft_abs(pas->y);
		pas->y /= ft_abs(pas->y);
	}
}

void	ft_put_par(t_window *win, t_par par, int color)
{
	t_dot		tmp;
	t_vector	pas;
	t_vector	line;
	int			nbpixels;
	int			i;

	line.x = par.d1.x - par.d2.x;
	line.y = par.d1.y - par.d2.y;
	set_pas(par.d2, par.d3, &pas, &nbpixels);
	i = -1;
	while (i++ < nbpixels)
	{
		tmp.x = par.d2.x + line.x;
		tmp.y = par.d2.y + line.y;
		//ft_put_line(win, &(par.d2), &tmp, color);
		par.d2.x += pas.x;
		par.d2.y += pas.y;
	}
}
