/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:38:02 by qhatahet          #+#    #+#             */
/*   Updated: 2024/11/02 16:32:36 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_buff(char *buff, int fd)
{
	char	*str;
	int		byte_read;

	str = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		return (NULL);
	byte_read = 1;
	while (!ft_strchr(str, '\n') && byte_read != 0)
	{
		byte_read = read(fd, str, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(str);
			free(buff);
			return (NULL);
		}
		str[byte_read] = '\0';
		buff = ft_strjoin(buff, str);
	}
	free(str);
	return (buff);
}

static char	*get_line(char *buff)
{
	int		i;
	char	*str;

	i = 0;
	if (!buff || buff[i] == '\0')
		return (NULL);
	while (buff[i] != '\n' && buff[i])
		i++;
	if (buff[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		str[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

static char	*update_buff(char *buff)
{
	char	*str;
	int		j;
	int		i;

	i = 0;
	while (buff[i] != '\n' && buff[i])
		i++;
	if (buff[i] == '\0')
	{
		free(buff);
		return (NULL);
	}
	i++;
	str = malloc(ft_strlen(buff) - i + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (buff[j + i] != '\0')
	{
		str[j] = buff[i + j];
		j++;
	}
	str[j] = '\0';
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = read_buff(buff, fd);
	if (!buff)
		return (NULL);
	line = get_line(buff);
	buff = update_buff(buff);
	if (!line)
	{
		free(line);
		free(buff);
		return (NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("a.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free (line);
// 	}
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// free(line);
// 	close(fd);
// 	return (0);
// }