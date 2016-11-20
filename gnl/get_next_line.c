/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 18:19:57 by amanchon          #+#    #+#             */
/*   Updated: 2016/11/02 07:45:36 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_line_len(char *str)
{
	int					i;

	i = 0;
	while (*str != '\n' && *str != 13 && *str++ != '\0')
		i++;
	return (i);
}

static void		read_next_line(int fd, t_storage *s)
{
	char				*tmp;

	if (!(s->memory[fd]))
		s->memory[fd] = ft_strnew(1);
	while ((!(ft_strchr(s->memory[fd], '\n'))
		&& !(ft_strchr(s->memory[fd], 13)))
		&& (s->nb_bytes = read(fd, s->buffer, BUFF_SIZE)) > 0)
	{
		s->buffer[s->nb_bytes] = '\0';
		tmp = s->memory[fd];
		s->memory[fd] = ft_strjoin(s->memory[fd], s->buffer);
		ft_strdel(&tmp);
	}
	ft_strdel(&s->buffer);
}

static int		manage_memory(int fd, t_storage *s)
{
	char				*tmp;
	int					linelen;

	if ((linelen = get_line_len(s->memory[fd])) > 0
		|| linelen < (int)ft_strlen(s->memory[fd]))
	{
		tmp = s->memory[fd];
		s->memory[fd] = ft_strdup(s->memory[fd] + linelen + 1);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_storage	storage;

	if (fd < 0 || fd > MAXFILE || line == NULL)
		return (-1);
	if (!(storage.buffer = (char*)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	read_next_line(fd, &storage);
	if (storage.nb_bytes == -1)
		return (-1);
	*line = ft_strsub(storage.memory[fd], 0, get_line_len(storage.memory[fd]));
	return (manage_memory(fd, &storage));
}/*

int					main(int argc, char **argv)
{
	int				fd;
	int				i;
	char			**line;

	i = 1;
	if (argc != 2)
		return (0);
	line = (char **)malloc(sizeof(char*));
	fd = open(argv[1], O_RDONLY);
	while (i > 0)
	{
		i = get_next_line(fd, line);
		if (i != -1)
			ft_putstr(*line);
		if (i == -1)
			write(1, "\nerror\n", 7);
		else if (i == 0)
			write(1, "\nEOF\n", 5);
		else
			write(1,"\nLigneLue\n", 10);
	}
	close(fd);
	return (0);
}*/
