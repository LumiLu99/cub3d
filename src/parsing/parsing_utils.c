# include "../../includes/cub3d.h"

int identify_parse_state(char c);
bool check_and_open_file(const char *file, const char *ext, int *fd, char *msg);
bool check_all_element_exists(t_data *data);
bool check_file_ext(const char *filename, const char *ext);

int identify_parse_state(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E' || c == 'F' || c == 'C')
		return ELEMENTS;
	else if (c == ' ' || c == '1' || c == '0')
		return MAP;
	return INVALID;
}

bool check_and_open_file(const char *file, const char *ext, int *fd, char *msg)
{
	if (!check_file_ext(file, ext))
		return (error_message(msg));
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (error_message("Invalid fd or path: Failed to open file"));
	return true;
}

bool check_all_element_exists(t_data *data)
{
	int i = 0;
	while (i < 4)
	{
		if (data->tex[i].tex_path == NULL)
			return(error_message("Texture elements given incomplete"));
		i++;
	}
	if (data->map.floor == -1 || data->map.ceiling == -1)
		return(error_message("Floor and ceiling elements given incomplete"));
	return true;
}

bool check_file_ext(const char *filename, const char *ext)
{
	size_t filename_len = ft_strlen(filename);
	size_t ext_len = ft_strlen(ext);

	if (filename[0] == '\0')
		return false;
	if (filename_len <= ext_len)
		return false;
	while (filename[filename_len - 1] && ext_len > 0)
	{
		// printf("filename[%c], ext[%c]\n", filename[filename_len - 1], ext[ext_len - 1]);
		if (filename[filename_len - 1] != ext[ext_len - 1])
			return false;
		// printf("filename_len: %zu, ext: %zu\n", filename_len, ext_len);
		filename_len--;
		ext_len--;
	}
	return true;
}
