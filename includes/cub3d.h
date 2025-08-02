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
# include "../minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

/* Game constants */
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define FULLSCREEN_WIDTH 1700
# define FULLSCREEN_HEIGHT 970
# define TEXTURE_SIZE 64
# define FOV 60
# define MOVE_SPEED 1.0
# define ROT_SPEED 0.05
# define MAP_SCALE 40
# define MINIMAP_SIZE 150
# define MINIMAP_SCALE 8
# define MINIMAP_MARGIN 20
# define MINIMAP_RADIUS 70
# define MINIMAP_VIEW_DISTANCE 10

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
# define KEY_F 102

/* Colors */
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000

/* Minimap Colors */
# define MINIMAP_BG 0x1A1A1A
# define MINIMAP_WALL 0x404040
# define MINIMAP_FLOOR 0x2A2A2A
# define MINIMAP_PLAYER 0x00AAFF
# define MINIMAP_PLAYER_DOT 0xFFFFFF
# define MINIMAP_DIRECTION 0x00FFAA
# define MINIMAP_BORDER 0x555555
# define MINIMAP_BORDER_OUTER 0x000000

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
	int		current_width;
	int		current_height;
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
	int			tex_x;
}	t_ray;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_map		map;
	t_texture	textures[4];
	t_texture	floor_texture;
	t_ray		ray;
	t_keys		keys;
	int			fullscreen;
}	t_game;

/* Function prototypes */
int			contains_cub(char *filename);
int			is_valid_char(char c);
int			exit_error(char *msg);
double		calculate_distance(double x1, double y1, double x2, double y2);
int			is_in_minimap_circle(int x, int y, int radius);

/* Game initialization */
int			init_game(t_game *game);
int			init_mlx(t_game *game);
int			init_player(t_game *game);
int			init_map(t_game *game);
int			load_texture(t_game *game, t_texture *texture, char *path);
int			load_textures(t_game *game);
void		cleanup_game(t_game *game);

/* Map parsing */
int			parse_map_file(char *filename, t_game *game);
int			read_map_lines(int fd, t_game *game);
void		free_map(t_game *game);
char		*trim_spaces(char *str);
int			parse_color(char *color_str);
char		*trim_newline(char *str);
void		process_map_line(char *line, t_game *game, int *i,
				int *map_started);
void		free_textures(t_game *game);
int			count_map_lines(char *filename);
void		handle_texture_path(char *line, char *prefix, char **texture_ptr);
void		handle_color(char *line, char *prefix, int *color_ptr);

/* Game loop */
int			game_loop(t_game *game);
int			close_game(t_game *game);
int			handle_key_press(int keycode, t_game *game);
int			handle_key_release(int keycode, t_game *game);
void		toggle_fullscreen(t_game *game);
void		destroy_window_and_image(t_game *game);
void		create_new_window_and_image(t_game *game,
				int new_width, int new_height);
void		register_event_handlers(t_game *game);

/* Minimap */
void		draw_minimap(t_game *game);
void		draw_minimap_background_and_border(t_game *game);
void		draw_minimap_world_cells(t_game *game);
void		draw_minimap_cell_at_pos(t_game *game, int world_x, int world_y);
void		draw_minimap_player_professional(t_game *game);
void		draw_minimap_border_pixel(t_game *game, int x, int y, int center_x);

/* Movement */
void		process_movement(t_game *game);
void		process_rotation(t_game *game);
void		calculate_movement(t_game *game, double *move_x, double *move_y);
void		apply_forward_backward(t_game *game, double *move_x,
				double *move_y, double speed);
void		apply_left_right(t_game *game, double *move_x,
				double *move_y, double speed);

/* Collision */
int			check_collision(t_game *game, double x, double y);
int			check_single_point(t_game *game, int map_x, int map_y);
int			touch(float ray_x, float ray_y, t_game *game);
void		draw_map_cell(t_game *game, int x, int y);

/* Rendering */
void		put_pixel(t_game *game, int x, int y, int color);
void		draw_square(t_game *game, t_square sq);
void		clear_screen(t_game *game, int color);
void		draw_map(t_game *game);
void		draw_ray_line(t_game *game, t_line line);
void		draw_direction_line(t_game *game, int player_x, int player_y);

/* Raycasting */
void		render_3d_view(t_game *game);
void		cast_rays_for_3d(t_game *game, double base_angle, double fov_rad);
double		cast_single_ray(t_game *game, double angle);
int			calculate_wall_color(double distance);
void		draw_wall_slice(t_game *game, t_ray *ray,
				int x, t_texture *texture);
void		draw_floor_pixel(t_game *game, int x, int y);
void		draw_wall_slice_ceiling(t_game *game, int x, int y);
void		draw_wall_slice_wall(t_game *game, t_ray *ray, int x, int y);
int			get_texture_color(t_texture *texture, int x, int y);
void		init_ray(t_game *game, t_ray *ray, int x);
void		calculate_step_and_side_dist(t_game *game, t_ray *ray);
void		perform_dda(t_game *game, t_ray *ray);
void		calculate_wall_distance(t_game *game, t_ray *ray);
void		calculate_perp_wall_dist(t_game *game, t_ray *ray);
void		calculate_line_height_and_draw_range(t_game *game, t_ray *ray);
t_texture	*get_wall_texture(t_game *game, t_ray *ray);
void		calculate_floor_coords(t_game *game, int x, int y, double *floor_x);
void		calculate_wall_texture_coords(t_game *game, t_ray *ray,
				t_texture *texture);

#endif
