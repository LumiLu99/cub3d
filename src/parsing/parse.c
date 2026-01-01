# include "../../includes/cub3d.h"

static int handle_empty_line_and_error(char **line, int *error, t_parse_state *state);
static int handle_element_state(char **line, t_parse_state *state, t_data *data, t_parse_state type);
static void process_line(char **line, int *error, t_parse_state *state, t_data *data);
int parse_file(const char *filename, t_data *data);

static int  handle_empty_line_and_error(char **line, int *error, t_parse_state *state)
{
	if (((*line)[0] == '\n' && *state == ELEMENTS) || *error == -1)
		return 0;
	return 1;
}

static int  handle_element_state(char **line, t_parse_state *state, t_data *data, t_parse_state type)
{
	if (type == MAP)
	{
		if(!check_all_element_exists(data))
			return 0;
		*state = MAP;
	}
	else if (!parse_texture(*line, data))
		return 0;
	return 1;
}

static void    process_line(char **line, int *error, t_parse_state *state, t_data *data)
{
	t_parse_state   type;
	
	type = identify_parse_state((*line)[0]);
	if (type == INVALID)
	{
		ft_putstr_fd("Error\nInvalid element in file\n", 2);
		*error = -1;
		return ;
	}
	if (*state == ELEMENTS)
	{
		if(!handle_element_state(line, state, data, type))
		{
			*error = -1;
			return ;
		}
	}
	if (*state == MAP && !read_map(&data->map, *line))
	{
		*error = -1;
		return ;
	}
}

/**
 * this function verifies the sequence of the elements in the map file
 * divided into 2 section: ELEMENTS and MAP (in order)
 * must start with section ELEMENTS (can be seperated by new line)
 * skip when see new line or error
 * let it read until the end of the file
 * store error flag when there is error, after finish read only exit
 * identify the type of each line
 * when reach map, check each element has their own value
 * when found element in map, return error
 * at the end validate the last part is map
 */
int parse_file(const char *filename, t_data *data)
{
	t_parse_state	state;
	int				error;
	int				fd;
	char			*line;

	state = ELEMENTS;
	error = 0;
	if (!check_and_open_file(filename, ".cub", &fd, INVALID_CUB_FILE_EXT))
		return 0;
	line = get_next_line(fd);
	while (line)
	{
		if (handle_empty_line_and_error(&line, &error, &state))
			process_line(&line, &error, &state, data);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (error == -1)
		return 0;
	if (state == ELEMENTS)
		return (error_message("No textures or map found"));
	return 1;
}
