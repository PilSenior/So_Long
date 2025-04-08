/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: htekdemi <htekdemi@student.42kocaeli.co	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/23 23:18:41 by htekdemi		  #+#	#+#			 */
/*   Updated: 2025/03/23 23:18:41 by htekdemi		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/so_long.h"
#define BUFFER_SIZE 42

char	*line_after_new_line(char *s, char c)
{
	char	*str;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (safe_free(s));
	str = (char *)malloc((ft_strlen(s) - i) + 1);
	if (!str)
		return (safe_free(s));
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

char	*line_before_new_line(char *s, char c)
{
	char	*str;
	int		i;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*read_and_join(int fd, char *s, char *str)
{
	char	*temp;
	int		i;

	i = 1;
	while (!ft_strchr(s, '\n') && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
			return (safe_free(str));
		str[i] = '\0';
		temp = ft_strjoin(s, str);
		free(s);
		if (!temp)
			return (safe_free(str));
		s = temp;
	}
	return (s);
}

char	*find_next_line(int fd, char *s)
{
	char	*str;

	if (!s)
	{
		s = (char *)malloc(1);
		if (!s)
			return (NULL);
		s[0] = '\0';
	}
	str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (safe_free(s));
	s = read_and_join(fd, s, str);
	free(str);
	return (s);
}

int	get_next_line(int fd, char **line, char **saved_line)
{
	char	*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line || !saved_line)
		return (-1);
	*saved_line = find_next_line(fd, *saved_line);
	if (!(*saved_line))
		return (-1);
	*line = line_before_new_line(*saved_line, '\n');
	if (!(*line))
	{
		*saved_line = safe_free(*saved_line);
		return (0);
	}
	temp = line_after_new_line(*saved_line, '\n');
	*saved_line = temp;
	if (*saved_line && (*saved_line)[0] == '\0')
		*saved_line = safe_free(*saved_line);
	return (1);
}
