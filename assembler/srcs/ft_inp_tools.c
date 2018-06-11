/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inp_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 14:29:35 by akaseris          #+#    #+#             */
/*   Updated: 2018/06/11 22:13:36 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char	*ft_addheader(char **tmp, int name, t_frame *frame)
{
	t_header *head;

	head = frame->header;
	if (name)
	{
		if (ft_strlen(*tmp) > PROG_NAME_LENGTH || head->prog_name != NULL)
		{
			ft_strdel(tmp);
			return (ft_strdup("Name is duplicated or too big"));
		}
		head->prog_name = *tmp;
	}
	else
	{
		if (ft_strlen(*tmp) > COMMENT_LENGTH || head->comment != NULL)
		{
			ft_strdel(tmp);
			return (ft_strdup("Comment is duplicated or too big"));
		}
		head->comment = *tmp;
	}
	return (NULL);
}

char	*ft_header(char *s, int name, t_frame *frame)
{
	int		i;
	char	*tmp;

	i = (name) ? ft_strlen(NAME_CMD_STRING) : ft_strlen(COMMENT_CMD_STRING);
	while (ft_isspace(s[i]))
		i++;
	if (s[i++] != '"')
		return (ft_strdup("Name and comment must be inside quotes"));
	s = s + i;
	if (!(tmp = ft_strchr(s, '"')))
		return (ft_strdup("Quotes must close in the same line"));
	tmp++;
	while (ft_isspace(*tmp))
		tmp++;
	if (*tmp != '\0' && *tmp != COMMENT_CHAR)
		return (ft_strdup("Invalid characters at the end of the line"));
	tmp = ft_strsub(s, 0, ft_strlen(s) - ft_strlen(ft_strchr(s, '"')));
	return (ft_addheader(&tmp, name, frame));
}

char	*ft_line(char *s, t_frame *frame)
{
	t_line	*line;
	char	*tmp;
	char	*ret;

	ret = NULL;
	line = NULL;
	if ((tmp = ft_strchr(s, COMMENT_CHAR)))
		tmp[0] = '\0';
	if (!(s = ft_strtrim(s)) || *s == '\0')
		return (NULL);
	if (s[ft_strlen(s) - 1] == SEPARATOR_CHAR)
		ret = ft_strdup("Separator char at the end of the line");
	tmp = s;
	ret = (!ret) ? ft_initline(&line) : ret;
	ret = (!ret) ? ft_get_label(&s, &line->label) : ret;
	ret = (!ret) ? ft_get_opname(&s, &line->opname) : ret;
	ret = (!ret) ? ft_get_arguments(s, line) : ret;
	ft_strdel(&tmp);
	if (!ret)
		ft_push_line(line, frame);
	else
		ft_free_lines(&line);
	return (ret);
}
