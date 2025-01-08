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
            else if (!ft_strncmp(line[0], "cy", ft_strlen(line[0])) && val->cy == false)
                val->cy = true;
            else if (!ft_strncmp(line[0], "sp", ft_strlen(line[0])) && val->sp == false)
                val->sp = true;
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
    int f;

    f = 0;
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
        else if (*str == '-')
		{
			if (f > 0)
				return (3);
			f++;
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
		printf("Error\nAmbient Light RGB Only Takes 3 Numbers\n");
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
		printf("Error\nAmbient Light RGB Should be a Number\n");
		freearray(rgb);
		return (1);
	}
	cor->am.rgb[0] = string_to_float(rgb[0]);
	cor->am.rgb[1] = string_to_float(rgb[1]);
	cor->am.rgb[2] = string_to_float(rgb[2]);
	if ((cor->am.rgb[0] > 255 || cor->am.rgb[0] < 0) || (cor->am.rgb[1] > 255 || cor->am.rgb[1] < 0) || (cor->am.rgb[2] > 255 || cor->am.rgb[2] < 0))
	{
		printf("Error\nAmbient Light RGB Range Is Between 0-255\n");
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

int check_cor_c(char **line , t_cor *cor)
{
    char **xyz;
    char **vector;

	if (twodsize(line) != 4)
	{
		printf("Error\nCamera only Takes 3 arguments\n");
		return (1);
	}
	xyz = ft_split(line[1], ',');
	vector = ft_split(line[2], ',');
	if (twodsize(xyz) != 3)
	{
		printf("Error\nCamera Coordinates Of The Viewpoint Only Takes 3 Numbers\n");
		freearray(xyz);
		freearray(vector);
		return (1);
	}
    if (twodsize(vector) != 3)
	{
		printf("Error\nCamera 3D Normalized Orientation Vector Only Takes 3 Numbers\n");
		freearray(xyz);
		freearray(vector);
		return (1);
	}
	if (is_all_digits(line[3]) == 0 || is_all_digits(line[3]) == 3)
	{
		printf("Error\nCamera FOV Should be a Number\n");
		freearray(xyz);
		freearray(vector);
		return (1);
	}
	if (is_all_digits(xyz[0]) == 0 || is_all_digits(xyz[1]) == 0 || is_all_digits(xyz[2]) == 0 || is_all_digits(xyz[0]) == 3 || is_all_digits(xyz[1]) == 3 || is_all_digits(xyz[2]) == 3)
	{
		printf("Error\nCamera Coordinates Of The Viewpoint Should be a Number\n");
		freearray(xyz);
		freearray(vector);
		return (1);
	}
    if (is_all_digits(vector[0]) == 0 || is_all_digits(vector[1]) == 0 || is_all_digits(vector[2]) == 0 || is_all_digits(vector[0]) == 3 || is_all_digits(vector[1]) == 3 || is_all_digits(vector[2]) == 3)
	{
		printf("Error\nCamera 3D Normalized Orientation Vector Should be a Number\n");
		freearray(xyz);
		freearray(vector);
		return (1);
	}
	cor->cm.cor[0] = string_to_float(xyz[0]);
	cor->cm.cor[1] = string_to_float(xyz[1]);
	cor->cm.cor[2] = string_to_float(xyz[2]);
	cor->cm.vector[0] = string_to_float(vector[0]);
	cor->cm.vector[1] = string_to_float(vector[1]);
	cor->cm.vector[2] = string_to_float(vector[2]);
    cor->cm.fov = string_to_float(line[3]);

    if ((cor->cm.vector[0] > 1 || cor->cm.vector[0] < -1) || (cor->cm.vector[1] > 1 || cor->cm.vector[1] < -1) || (cor->cm.vector[2] > 1 || cor->cm.vector[2] < -1))
	{
		printf("Error\nCamera 3D Normalized Orientation Vector Range Is Between -1 -> 1\n");
		freearray(xyz);
		freearray(vector);
		return (1);
	}
	if (cor->cm.fov > 180 || cor->cm.fov < 0)
	{
		printf("Error\nCamera Horizontal field of view Range Is Between 0 -> 180\n");
		freearray(xyz);
		freearray(vector);
		return (1);
	}
	freearray(xyz);
    freearray(vector);
	return (0);
}

int check_cor_l(char **line, t_cor *cor)
{
    char **xyz;

	if (twodsize(line) != 3)
	{
		printf("Error\nLight only Takes 2 arguments\n");
		return (1);
	}
	xyz = ft_split(line[1], ',');
	if (twodsize(xyz) != 3)
	{
		printf("Error\nLight Point Coordinates Only Takes 3 Numbers\n");
		freearray(xyz);
		return (1);
	}
	if (is_all_digits(line[2]) == 0 || is_all_digits(line[2]) == 3)
	{
		printf("Error\nLight Brightness Raito Should be a Number\n");
		freearray(xyz);
		return (1);
	}
	if (is_all_digits(xyz[0]) == 0 || is_all_digits(xyz[1]) == 0 || is_all_digits(xyz[2]) == 0 || is_all_digits(xyz[0]) == 3 || is_all_digits(xyz[1]) == 3 || is_all_digits(xyz[2]) == 3)
	{
		printf("Error\nLight Point Coordinates Should be a Number\n");
		freearray(xyz);
		return (1);
	}
	cor->light.cor[0] = string_to_float(xyz[0]);
	cor->light.cor[1] = string_to_float(xyz[1]);
	cor->light.cor[2] = string_to_float(xyz[2]);
    cor->light.brightness = string_to_float(line[2]);
    if (cor->light.brightness > 1 || cor->light.brightness < 0)
	{
		printf("Error\nLight Brightness Range Is Between 0 -> 1\n");
		freearray(xyz);
		return (1);
	}
	freearray(xyz);
	return (0);
}

int check_cor_cy(char **line, t_cor *cor)
{
    char **xyz;
    char **vector;
    char **rgb;

	if (twodsize(line) != 6)
	{
		printf("Error\nCylinder only Takes 5 arguments\n");
		return (1);
	}
	xyz = ft_split(line[1], ',');
    rgb = ft_split(line[5], ',');
	vector = ft_split(line[2], ',');
    if (twodsize(rgb) != 3)
	{
		printf("Error\nCylinder RGB Only Takes 3 Numbers\n");
		freearray(rgb);
        freearray(xyz);
		freearray(vector);
		return (1);
	}
    if (is_all_digits(rgb[0]) == 0 || is_all_digits(rgb[1]) == 0 || is_all_digits(rgb[2]) == 0 || is_all_digits(rgb[0]) == 3 || is_all_digits(rgb[1]) == 3 || is_all_digits(rgb[2]) == 3)
	{
		printf("Error\nCylinder RGB Should be a Number\n");
		freearray(rgb);
        freearray(xyz);
		freearray(vector);
		return (1);
	}
	if (twodsize(xyz) != 3)
	{
		printf("Error\nCoordinates Of The Center Of The Cylinder Only Takes 3 Numbers\n");
		freearray(xyz);
		freearray(vector);
        freearray(rgb);
		return (1);
	}
    if (twodsize(vector) != 3)
	{
		printf("Error\n3D Normalized Vector Of Axis Of Cylinder Only Takes 3 Numbers\n");
		freearray(xyz);
		freearray(vector);
        freearray(rgb);
		return (1);
	}
	if (is_all_digits(line[3]) == 0 || is_all_digits(line[3]) == 3)
	{
		printf("Error\nCylinder Diameter Should be a Number\n");
		freearray(xyz);
		freearray(vector);
        freearray(rgb);
		return (1);
	}
    if (is_all_digits(line[4]) == 0 || is_all_digits(line[4]) == 3)
	{
		printf("Error\nCylinder Height Should be a Number\n");
		freearray(xyz);
        freearray(rgb);
		freearray(vector);
		return (1);
	}
	if (is_all_digits(xyz[0]) == 0 || is_all_digits(xyz[1]) == 0 || is_all_digits(xyz[2]) == 0 || is_all_digits(xyz[0]) == 3 || is_all_digits(xyz[1]) == 3 || is_all_digits(xyz[2]) == 3)
	{
		printf("Error\nCoordinates Of The Center Of The Cylinder Should be a Number\n");
		freearray(xyz);
		freearray(vector);
        freearray(rgb);
		return (1);
	}
    if (is_all_digits(vector[0]) == 0 || is_all_digits(vector[1]) == 0 || is_all_digits(vector[2]) == 0 || is_all_digits(vector[0]) == 3 || is_all_digits(vector[1]) == 3 || is_all_digits(vector[2]) == 3)
	{
		printf("Error\3D Normalized Vector Of Axis Of Cylinder Should be a Number\n");
		freearray(xyz);
		freearray(vector);
        freearray(rgb);
		return (1);
	}
	cor->cy.cor[0] = string_to_float(xyz[0]); 
	cor->cy.cor[1] = string_to_float(xyz[1]); 
	cor->cy.cor[2] = string_to_float(xyz[2]); 
    cor->cy.vector[0] = string_to_float(vector[0]);
    cor->cy.vector[1] = string_to_float(vector[1]);
    cor->cy.vector[2] = string_to_float(vector[2]);
    cor->cy.cy_diameter = string_to_float(line[3]);
    cor->cy.cy_height = string_to_float(line[4]);
    cor->cy.rgb[0] = string_to_float(rgb[0]);
    cor->cy.rgb[1] = string_to_float(rgb[1]);
    cor->cy.rgb[2] = string_to_float(rgb[2]);
		if (cor->cy.cy_diameter < 0)
	{
		printf("Error\nCylinder Diameter Should be a Positive Number\n");
		freearray(xyz);
        freearray(rgb);
		return (1);
	}
	if (cor->cy.cy_height < 0)
	{
		printf("Error\nCylinder height Should be a Positive Number\n");
		freearray(xyz);
        freearray(rgb);
		return (1);
	}
    if ((cor->cy.rgb[0] > 255 || cor->cy.rgb[0] < 0) || (cor->cy.rgb[1] > 255 || cor->cy.rgb[1] < 0) || (cor->cy.rgb[2] > 255 || cor->cy.rgb[2] < 0))
	{
		printf("Error\nCylinder RGB Range Is Between 0-255\n");
		freearray(rgb);
        freearray(xyz);
		freearray(vector);
		return (1);
	}
    if ((cor->cy.vector[0] > 1 || cor->cy.vector[0] < -1) || (cor->cy.vector[1] > 1 || cor->cy.vector[1] < -1) || (cor->cy.vector[2] > 1 || cor->cy.vector[2] < -1))
	{
		printf("Error\nCylinder 3D Normalized Vector Of Axis Range Is Between -1 -> 1\n");
		freearray(xyz);
		freearray(vector);
		freearray(rgb);
		return (1);
	}
	freearray(xyz);
    freearray(rgb);
    freearray(vector);
	return (0);
}

int	check_cor_pl(char **line, t_cor *cor)
{
	char **xyz;
    char **vector;
    char **rgb;

	if (twodsize(line) != 4)
	{
		printf("Error\nPlane only Takes 4 arguments\n");
		return (1);
	}
	xyz = ft_split(line[1], ',');
    rgb = ft_split(line[3], ',');
	vector = ft_split(line[2], ',');
	 if (twodsize(rgb) != 3)
	{
		printf("Error\nPlane RGB Only Takes 3 Numbers\n");
		freearray(rgb);
        freearray(xyz);
		freearray(vector);
		return (1);
	}
    if (is_all_digits(rgb[0]) == 0 || is_all_digits(rgb[1]) == 0 || is_all_digits(rgb[2]) == 0 || is_all_digits(rgb[0]) == 3 || is_all_digits(rgb[1]) == 3 || is_all_digits(rgb[2]) == 3)
	{
		printf("Error\nPlane RGB Should be a Number\n");
		freearray(rgb);
        freearray(xyz);
		freearray(vector);
		return (1);
	}
	if (twodsize(xyz) != 3)
	{
		printf("Error\nCoordinates Of The Center Of The Plane Only Takes 3 Numbers\n");
		freearray(xyz);
		freearray(vector);
        freearray(rgb);
		return (1);
	}
    if (twodsize(vector) != 3)
	{
		printf("Error\n3D Normalized Vector Of Axis Of Plane Only Takes 3 Numbers\n");
		freearray(xyz);
		freearray(vector);
        freearray(rgb);
		return (1);
	}
	if (is_all_digits(xyz[0]) == 0 || is_all_digits(xyz[1]) == 0 || is_all_digits(xyz[2]) == 0 || is_all_digits(xyz[0]) == 3 || is_all_digits(xyz[1]) == 3 || is_all_digits(xyz[2]) == 3)
	{
		printf("Error\nCoordinates Of The Center Of The Plane Should be a Number\n");
		freearray(xyz);
		freearray(vector);
        freearray(rgb);
		return (1);
	}
    if (is_all_digits(vector[0]) == 0 || is_all_digits(vector[1]) == 0 || is_all_digits(vector[2]) == 0 || is_all_digits(vector[0]) == 3 || is_all_digits(vector[1]) == 3 || is_all_digits(vector[2]) == 3)
	{
		printf("Error\3D Normalized Vector Of Axis Of Plane Should be a Number\n");
		freearray(xyz);
		freearray(vector);
        freearray(rgb);
		return (1);
	}
	cor->pl.cor[0] = string_to_float(xyz[0]); 
	cor->pl.cor[1] = string_to_float(xyz[1]); 
	cor->pl.cor[2] = string_to_float(xyz[2]); 
    cor->pl.vector[0] = string_to_float(vector[0]);
    cor->pl.vector[1] = string_to_float(vector[1]);
    cor->pl.vector[2] = string_to_float(vector[2]);
	cor->pl.rgb[0] = string_to_float(rgb[0]);
    cor->pl.rgb[1] = string_to_float(rgb[1]);
    cor->pl.rgb[2] = string_to_float(rgb[2]);
	 if ((cor->pl.rgb[0] > 255 || cor->pl.rgb[0] < 0) || (cor->pl.rgb[1] > 255 || cor->pl.rgb[1] < 0) || (cor->pl.rgb[2] > 255 || cor->pl.rgb[2] < 0))
	{
		printf("Error\nPlane RGB Range Is Between 0-255\n");
		freearray(rgb);
        freearray(xyz);
		freearray(vector);
		return (1);
	}
    if ((cor->pl.vector[0] > 1 || cor->pl.vector[0] < -1) || (cor->pl.vector[1] > 1 || cor->pl.vector[1] < -1) || (cor->pl.vector[2] > 1 || cor->pl.vector[2] < -1))
	{
		printf("Error\nPlane 3D Normalized Vector Of Axis Range Is Between -1 -> 1\n");
		freearray(xyz);
		freearray(vector);
		freearray(rgb);
		return (1);
	}
	freearray(xyz);
    freearray(rgb);
    freearray(vector);
	return (0);
}

int	check_cor_sp(char **line, t_cor *cor)
{
	char **xyz;
    char **rgb;

	if (twodsize(line) != 4)
	{
		printf("Error\nSphere only Takes 4 arguments\n");
		return (1);
	}
	xyz = ft_split(line[1], ',');
    rgb = ft_split(line[3], ',');
	 if (twodsize(rgb) != 3)
	{
		printf("Error\nSphere RGB Only Takes 3 Numbers\n");
		freearray(rgb);
        freearray(xyz);
		return (1);
	}
    if (is_all_digits(rgb[0]) == 0 || is_all_digits(rgb[1]) == 0 || is_all_digits(rgb[2]) == 0 || is_all_digits(rgb[0]) == 3 || is_all_digits(rgb[1]) == 3 || is_all_digits(rgb[2]) == 3)
	{
		printf("Error\nSphere RGB Should be a Number\n");
		freearray(rgb);
        freearray(xyz);
		return (1);
	}
	if (twodsize(xyz) != 3)
	{
		printf("Error\nCoordinates Of The Center Of The Sphere Only Takes 3 Numbers\n");
		freearray(xyz);
        freearray(rgb);
		return (1);
	}
	if (is_all_digits(xyz[0]) == 0 || is_all_digits(xyz[1]) == 0 || is_all_digits(xyz[2]) == 0 || is_all_digits(xyz[0]) == 3 || is_all_digits(xyz[1]) == 3 || is_all_digits(xyz[2]) == 3)
	{
		printf("Error\nCoordinates Of The Center Of The Sphere Should be a Number\n");
		freearray(xyz);
        freearray(rgb);
		return (1);
	}
	if (is_all_digits(line[2]) == 0 || is_all_digits(line[2]) == 3)
	{
		printf("Error\nSphere Diameter Should be a Number\n");
		freearray(xyz);
        freearray(rgb);
		return (1);
	}
	cor->sp.cor[0] = string_to_float(xyz[0]); 
	cor->sp.cor[1] = string_to_float(xyz[1]); 
	cor->sp.cor[2] = string_to_float(xyz[2]);
	cor->sp.diameter = string_to_float(line[2]);
	cor->sp.rgb[0] = string_to_float(rgb[0]);
    cor->sp.rgb[1] = string_to_float(rgb[1]);
    cor->sp.rgb[2] = string_to_float(rgb[2]);
	if (cor->sp.diameter < 0)
	{
		printf("Error\nSphere Diameter Should be a Positive Number\n");
		freearray(xyz);
        freearray(rgb);
		return (1);
	}
	if (cor->sp.rgb[0] < 0 || cor->sp.rgb[1] < 0  || cor->sp.rgb[2] < 0)
	{
		printf("Error\nSphere RGB Should be a Positive Number\n");
		freearray(xyz);
        freearray(rgb);
		return (1);
	}
	freearray(xyz);
	freearray(rgb);
	return (0);
}

int	check_cor(char **line, t_cor *cor)
{
	if (line[0][0] == 'A')
		check_cor_a(line, cor);
    else if (line[0][0] == 'C')
    {
        check_cor_c(line, cor);
    }
    else if (line[0][0] == 'L')
    {
        check_cor_l(line, cor);
    }
    else if (line[0][0] == 'c')
    {
        check_cor_cy(line, cor);
    }
	else if (line[0][0] == 'p')
    {
        check_cor_pl(line, cor);
    }
	else if (line[0][0] == 's')
    {
        check_cor_sp(line, cor);
    }
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