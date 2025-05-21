/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:47:19 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/21 01:42:58 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ratp.h"

char	*trim(char *str)
{
	char	*end;

	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
		str++;
	if (*str == 0)
		return (str);
	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
		end--;
	*(end + 1) = 0;
	return (str);
}

void	print_formatted_datetime(const char *iso)
{
	struct tm	tm;
	char		out[64];

	memset(&tm, 0, sizeof(struct tm));
	if (strptime(iso, "%Y-%m-%dT%H:%M:%S", &tm) == NULL)
	{
		printf("%s\n", iso);
		return ;
	}
	strftime(out, sizeof(out), "%d/%m/%Y %H:%M", &tm);
	printf("%s\n", out);
}
