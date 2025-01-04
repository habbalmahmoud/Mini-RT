#include "../includes/miniRT.h"

int check_dup(char **line, t_val *val)
{
    if ((!ft_strncmp(line[0], "A", ft_strlen(line[0])) || !ft_strncmp(line[0], "C", ft_strlen(line[0]))
        || !ft_strncmp(line[0], "L", ft_strlen(line[0])) || !ft_strncmp(line[0], "cy", ft_strlen(line[0]))
        || !ft_strncmp(line[0], "pl", ft_strlen(line[0])) || !ft_strncmp(line[0], "sp", ft_strlen(line[0]))
        || !ft_strncmp(line[0], "\0", ft_strlen(line[0]))))
    {
        if (line[0])
        {
            if (!ft_strncmp(line[0], "A", ft_strlen(line[0])) && val->a == true)
                return (1);
            else if (!ft_strncmp(line[0], "A", ft_strlen(line[0])) && val->a == false)
                val->a = true;
            else if (!ft_strncmp(line[0], "C", ft_strlen(line[0])) && val->c == true)
                return (1);
            else if (!ft_strncmp(line[0], "C", ft_strlen(line[0])) && val->c == false)
                val->c = true;
            else if (!ft_strncmp(line[0], "L", ft_strlen(line[0])) && val->l == true)
                return (1);
            else if (!ft_strncmp(line[0], "L", ft_strlen(line[0])) && val->l == false)
                val->l = true;
            else if (!ft_strncmp(line[0], "cy", ft_strlen(line[0])) && val->cy == true)
                return (1); 
            else if (!ft_strncmp(line[0], "cy", ft_strlen(line[0])) && val->cy == false)
                val->cy = true;
            else if (!ft_strncmp(line[0], "sp", ft_strlen(line[0])) && val->sp == true)
                return (1);
            else if (!ft_strncmp(line[0], "sp", ft_strlen(line[0])) && val->sp == false)
                val->sp = true;
            else if (!ft_strncmp(line[0], "pl", ft_strlen(line[0])) && val->pl == true)
                return (1);
            else if (!ft_strncmp(line[0], "pl", ft_strlen(line[0])) && val->pl == false)
                val->pl = true;
        }
    }
    else
        return (2);
    return (0);
}

float string_to_float(const char *str) {
    if (!str)
        return 0.0f;

    float result = 0.0f;
    float fraction = 0.0f;
    int sign = 1;
    int divisor = 1;
    int decimal_found = 0;

    while (ft_isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str) {
        if (ft_isdigit(*str)) {
            if (decimal_found) {
                fraction = fraction * 10 + (*str - '0');
                divisor *= 10;
            } else {
                result = result * 10 + (*str - '0');
            }
        } else if (*str == '.') {
            if (decimal_found) {
                break;
            }
            decimal_found = 1;
        } else {
            break;
        }
        str++;
    }

    result += fraction / divisor;
    return result * sign;
}

int is_all_digits(const char *str)
{
	int i;

	i = 0;
    if (!str || *str == '\0')
        return 0;

    while (*str)
	{
		if (*str == '.')
		{
			if (i > 0)
				return (3);
			i++;
		}
        else if (!ft_isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

int check_cor_a(char **line, t_cor *cor)
{
	char **rgb;

	if (twodsize(line) != 3)
	{
		printf("Error\nAmbient Light only Takes 2 arguments\n");
		return (1);
	}
	rgb = ft_split(line[2], ',');
	if (twodsize(rgb) != 3)
	{
		printf("Error\nRGB Only Takes 3 Numbers\n");
		freearray(rgb);
		return (1);
	}
	if (is_all_digits(line[1]) == 0 || is_all_digits(line[1]) == 3)
	{
		printf("Error\nAmbient Light Should be a Number\n");
		freearray(rgb);
		return (1);
	}
	if (is_all_digits(rgb[0]) == 0 || is_all_digits(rgb[1]) == 0 || is_all_digits(rgb[2]) == 0 || is_all_digits(rgb[0]) == 3 || is_all_digits(rgb[1]) == 3 || is_all_digits(rgb[2]) == 3)
	{
		printf("Error\nRGB Should be a Number\n");
		freearray(rgb);
		return (1);
	}
	cor->am.rgb[0] = string_to_float(rgb[0]);
	cor->am.rgb[1] = string_to_float(rgb[1]);
	cor->am.rgb[2] = string_to_float(rgb[2]);
	if ((cor->am.rgb[0] > 255 || cor->am.rgb[0] < 0) || (cor->am.rgb[1] > 255 || cor->am.rgb[1] < 0) || (cor->am.rgb[2] > 255 || cor->am.rgb[2] < 0))
	{
		printf("Error\n RGB Range Is Between 0-255\n");
		freearray(rgb);
		return (1);
	}
	cor->am.am = string_to_float(line[1]);
	if (cor->am.am > 1 || cor->am.am < 0)
	{
		printf("Error\n Ambient Light Range Is Between 0-1\n");
		freearray(rgb);
		return (1);
	}
	freearray(rgb);
	return (0);
}

int	check_cor(char **line, t_cor *cor)
{
	if (line[0][0] == 'A')
		check_cor_a(line, cor);
	return (0);
}
t_val   *init_val(t_val *data)
{
    data->a = false;
    data->c = false;
    data->l = false;
    data->cy = false;
    data->sp = false;
    data->pl = false;
    return (data);
}

int validate(char **map ,t_cor *cor)
{
    int i;
    char **line;
    // int j;
    t_val *val;

    val = malloc(sizeof(t_val));
    val = init_val(val);
    i = 0;
    while(map[i])
    {
        if (map[i][ft_strlen(map[i]) - 1] == '\n')
            map[i][ft_strlen(map[i]) - 1] = 0;
        line = ft_split(map[i], ' ');
        if (check_dup(line, val) == 1)
        {
            freearray(line);
            free (val);
            printf("Error\nDuplicate Was Found !\n");
            return (1);
        }
        else if (check_dup(line, val) == 2)
        {
            freearray(line);
            free (val);
            printf("Error\nUnkown Element!\n");
            return (1);
        }
        freearray(line);
        i++;
    }
    if (val->cy == false || val->sp == false || val->a == false || val->l == false || val->c == false || val->pl == false)
    {
        printf("Error\nMissing Elemnt/s !\n");
        free (val);
        return (1);
    }
    free (val);
    i  = 0;
    while(map[i])
    {
        if (map[i][ft_strlen(map[i]) - 1] == '\n')
            map[i][ft_strlen(map[i]) - 1] = 0;
        line = ft_split(map[i], ' ');
        check_cor(line, cor);
        freearray(line);
        i++;
    }
    return (0);
}

// t_map **map_lines;
//     t_map *temp;

//     map_lines = malloc(sizeof(t_map*));
//     *map_lines = malloc(sizeof(t_map));
//     temp = *map_lines;
//     i = 0;
    
//     while(map[i])
//     {
//         temp->line = map[i];
//         i++;
//         if (map[i])
//         {
//         temp->next = malloc(sizeof(t_map));

//         temp = temp->next;
//         }
//     }


//     while (*map_lines)
//     {
//         printf("%s\n", (*map_lines)->line);
//         *map_lines = (*map_lines)->next;
//     }