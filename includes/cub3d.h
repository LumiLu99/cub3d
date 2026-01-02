/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:56:07 by yelu              #+#    #+#             */
/*   Updated: 2026/01/02 13:39:06 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include <stdio.h>
# include <fcntl.h>

// Colours
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define WHITE_PIXEL 0xFFFFFF
# define BLUE_PIXEL 0x0000FF
# define GRAY_PIXEL 0x808080

// Window
# define WIDTH 1920
# define HEIGHT 1080

// Tile size
# define TILE_SIZE 15

// Maths
# define PI 3.14159265359

# define FOV_DEGREE 60

// Side
# define TEX_SIZE 4
# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

// Error message
# define INVALID_XPM_FILE_EXT "Invalid texture file extension \".xpm\""
# define INVALID_CUB_FILE_EXT "Invalid cub file extension \".cub\""

typedef enum state
{
	ELEMENTS,
	MAP,
	INVALID
}	t_state;

typedef struct s_map
{
	char	**map_arr;
	int		map_rows;
	int		map_column;
	int		floor;
	int		ceiling;
}	t_map;

typedef struct s_minimap
{
	int	mp_x;
	int	mp_y;
}	t_minimap;

typedef struct s_player
{
	char	direction;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_time
{
	long long	time;
	long long	old_time;
	double		delta_time;
	int			fps;
	int			fps_count;
	long long	start_time;
}	t_time;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	camera_x;
	double	delta_x;
	double	delta_y;
	int		map_x;
	int		map_y;
	double	side_n_x;
	double	side_n_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_dist;
	int		side;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
}	t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		endian;
	int		bits_per_pixel;
	int		line_len;
	int		img_height;
	int		img_width;
	char	*tex_path;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_img		img_mlx;
	t_img		tex[TEX_SIZE];
	t_map		map;
	t_minimap	mini;
	t_time		time;
	t_ray		ray;
}	t_data;

int			ft_close(t_data *data);
int			update(void *param);

void		move_player(t_data *data);

// key
int			on_keypress(int keysym, t_data *data);
int			on_keyrelease(int keysym, t_data *data);

// raycasting
void		draw_dda(t_data *data);
void		side_dist(t_data *data);
void		ray_tex_init(t_data *data);
void		ray_tex_draw(t_data *data, int x);
void		ray_tex_sides(t_data *data, int side);
void		tex_init(t_data *data);

// init
void		init_mlx(t_data *data);
void		init_player(t_player *player);

// utils
void		print_error_exit(char *str);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
long long	get_time_in_ms(void);
void		print_fps(t_data *data);

//parse.c
int			parse_file(const char *filename, t_data *data);

// parse_map.c
int			parse_map(const char *filename, t_data *data);
bool		player_direction(char c);

//parse_map2.c
bool		read_map(t_map *map, char *line);
bool		validate_map(t_map *map, t_player *player);
bool		validate_player(char **map, t_player *player);

//parse_texture.c
int			parse_texture(char *line, t_data *data);

//parse_color.c
int			parse_color(char *identifier, char *color);

// parsing_utils.c
int			identify_state(char c);
bool		check_open_file(const char *file, const char *ext, int *fd, char *msg);
bool		check_all_element_exists(t_data *data);
bool		check_file_ext(const char *filename, const char *ext);

// parsing_free.c
void		free_2d_array(char **array);
bool		error_message(char *message);
void		free_texture_path(t_data *data);
void		cleanup_data(t_data *data);
void		cleanup_texture(char **texture, char *texture_path);

#endif
