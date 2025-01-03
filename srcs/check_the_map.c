#include "../includes/miniRT.h"
#include <fcntl.h>

void fill_map(int fd, char **map)
{
    char *line;
    int i;

    i = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        map[i] = line;
        i++;
        line = get_next_line(fd);
    }
    map[i] = NULL;
    if (map[0] == NULL)
    {
        free(map);
        exit(printf("Error\n"));
    }
    free(line);
}

int count_lines(int fd)
{
    char *line;
    int i;

    i = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        i++;
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    return (i);
}

char **checking_the_map(char *str)
{
    int str_len;
    char *substr;
    int fd;
    int fd_cpy;
    char **map;

    str_len = ft_strlen(str);
    substr = ft_substr(str, str_len - 3, 3);
    if (ft_strncmp(substr, ".rt", 3) != 0)
    {
        free(substr);
        exit(printf("Error\nWrong Extension\n"));
    }
    free(substr);
    fd = open(str, O_RDONLY);
    fd_cpy = open(str, O_RDONLY);
    if (fd < 0 || fd_cpy < 0)
        exit(printf("Error reading the file!\n"));
    map = malloc((count_lines(fd_cpy) + 1) * sizeof(char *));
    if (!map)
        return (NULL);
    fill_map(fd, map);
    return (map);
}