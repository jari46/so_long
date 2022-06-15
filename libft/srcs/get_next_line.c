/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:29:33 by yehan             #+#    #+#             */
/*   Updated: 2022/06/15 15:25:08 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*s_save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	s_save = read_iter(s_save, fd);
	if (s_save == NULL || *s_save == '\0')
	{
		free(s_save);
		s_save = NULL;
		return (NULL);
	}
	line = get_line(s_save);
	if (line == NULL)
	{
		free(s_save);
		s_save = NULL;
		return (NULL);
	}
	if (set_remains(&s_save, ft_strlen(line)) == false)
		return (NULL);
	return (line);
}

char	*read_iter(char *s_save, int fd)
{
	char			*buf;
	static ssize_t	nread;
	char			*temp;
	char			*new;

	buf = ft_calloc(1, BUFFER_SIZE + 1);
	new = s_save;
	while (new == NULL || !ft_strchr(new, '\n'))
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread == -1)
			ft_perror_exit("Error\n");
		if (nread == 0)
			break ;
		buf[nread] = '\0';
		temp = new;
		new = ft_strjoin(new, buf);
		free(temp);
	}
	free(buf);
	buf = NULL;
	if (nread < 0)
		return (NULL);
	return (new);
}

char	*get_line(char const *s_save)
{
	size_t		len;
	char		*line;

	if (ft_strchr(s_save, '\n'))
	{
		len = ft_strchr(s_save, '\n') - s_save + 1;
	}
	else
	{
		len = ft_strchr(s_save, '\0') - s_save;
	}
	line = ft_calloc(1, len + 1);
	ft_strlcpy(line, s_save, len + 1);
	return (line);
}

bool	set_remains(char **s_save, size_t offset)
{
	char	*temp;

	temp = *s_save;
	*s_save = malloc(ft_strlen(temp + offset) + 1);
	if (*s_save == NULL)
	{
		free(temp);
		temp = NULL;
		return (false);
	}
	ft_strlcpy(*s_save, temp + offset, ft_strlen(temp + offset) + 1);
	free(temp);
	temp = NULL;
	return (true);
}
