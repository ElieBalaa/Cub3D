/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:09:36 by oiskanda          #+#    #+#             */
/*   Updated: 2025/08/01 02:25:08 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

/* Game constants */
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define TEXTURE_SIZE 64
# define FOV 60
# define MOVE_SPEED 1.0
# define ROT_SPEED 0.05
# define MAP_SCALE 40

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* Key codes */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_SHIFT 65505

/* Colors */
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000

typedef struct s_line
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_line;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_square;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		move_speed;
	double		rot_speed;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	shift;
}	t_keys;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceiling_color;
}	t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	step;
	t_vector	map;
	double		perp_wall_dist;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}	t_ray;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_map		map;
	t_texture	textures[4];
	t_ray		ray;
	t_keys		keys;
}	t_game;

/* Function prototypes */
int		contains_cub(char *filename);
int		is_valid_char(char c);
int		exit_error(char *msg);

/* Game initialization */
int		init_game(t_game *game);
int		init_mlx(t_game *game);
int		init_player(t_game *game);
int		init_map(t_game *game);
void	cleanup_game(t_game *game);

/* Map parsing */
int		parse_map_file(char *filename, t_game *game);
int		read_map_lines(int fd, t_game *game);
void	free_map(t_game *game);

/* Game loop */
int		game_loop(t_game *game);
int		close_game(t_game *game);
int		handle_key_press(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);

/* Movement */
void	process_movement(t_game *game);
void	process_rotation(t_game *game);
void	calculate_movement(t_game *game, double *move_x, double *move_y);
void	apply_forward_backward(t_game *game, double *move_x,
			double *move_y, double speed);
void	apply_left_right(t_game *game, double *move_x,
			double *move_y, double speed);

/* Collision */
int		check_collision(t_game *game, double x, double y);
int		check_single_point(t_game *game, int map_x, int map_y);
int		touch(float ray_x, float ray_y, t_game *game);
void	draw_map_cell(t_game *game, int x, int y);

/* Rendering */
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_square(t_game *game, t_square sq);
void	clear_screen(t_game *game, int color);
void	draw_map(t_game *game);
void	draw_direction_line(t_game *game, int x, int y);
void	draw_ray_line(t_game *game, t_line line);

/* Raycasting */
void	cast_fov_rays(t_game *game);
void	draw_line(t_game *game, float start_x);
int		ray_hit_wall(t_game *game, double ray_x, double ray_y);
void	cast_ray(t_game *game, double ray_dir_x, double ray_dir_y);

#endif
