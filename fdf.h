/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/10 17:21:22 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 22:03:35 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"

typedef struct	s_color
{
	float	    r;
	float	    g;
	float		b;
}				t_color;

typedef struct	s_dot
{
	float		x;
	float		y;
	int			color;
}				t_dot;

typedef struct	s_image
{
	void		*image_ptr;
	int			bpp;
	int			s_l;
	int			endian;
	int			*image;
}				t_image;

typedef struct	s_par
{
	t_dot		d1;
	t_dot		d2;
	t_dot		d3;
	t_dot		d4;
}				t_par;

typedef struct	s_vector
{
	float	    x;
	float	    y;
}				t_vector;

/*typedef struct	s_inputs
{
	int			fd;
	char		*line;
	char		**tabline;
	int			*tmpcolors;
	int			**colors;
	int			*tmptab;
	int			**tab;
	int			*lenx;
	int			leny;
}				t_inputs;*/

typedef struct	s_inputs
{
	int			fd;
	char		*line;
	int			**tab;
	int			*lenx;
	int			leny;
}				t_inputs;

typedef struct	s_map
{
	t_image		*image;
	t_dot		origin;
	t_dot		centre;
	t_vector	i;
	t_vector	j;
	t_vector	k;
	t_dot		***tabdot;
	int			minz;
	int			maxz;
	float		zoom;
}			    t_map;

typedef struct	s_window
{
    void		*mlx;
    void		*win;
	int			width;
	int			height;
	char		*name;
	int			colorparam;
	int			maxcolor;
	int			mincolor;
	t_map		*map;
	t_inputs	*inputs;
}				t_window;

int				params(t_window *win, int ac, char **av);
int				ft_init_tabs(t_window *win, t_inputs *inputs, t_map *map);
int				parse(t_window *win, t_inputs *inputs, char *file);
void			ft_refresh(t_window *win, t_image *image);
int				set_dots(t_window *win, t_inputs *inputs, t_map *map);
void			reset_dots(t_window *win, t_inputs *inputs, t_map *map);
void			print_dots(t_window *win, t_inputs *inputs, t_map *map);
t_par			set_par(t_dot *d1, t_dot *d2, t_dot *d3, t_dot *d4);
void			ft_put_line(t_window *window, t_dot *d1, t_dot *d2);
void			ft_put_par(t_window *win, t_par par, int color);
void			ft_print_bordure(t_window *win);
int				key_hook(int keycode, t_window *win);
int     		mouse_hook(int button, int x, int y, t_window *win);
void			ft_parallele(t_window *win, int keycode);
int				ft_clear_memory(t_window *win, t_inputs *inputs);
int				set_dots(t_window *win, t_inputs *inputs, t_map *map);
int				maping(t_window *win, int mincolor, int maxcolor, double prop);
int				set_color(t_window *win, int z);

#endif
