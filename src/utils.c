/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:47:19 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/23 00:37:58 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ratp.h"

void to_uppercase(char *str) 
{
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

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

	memset(&tm, 0, sizeof(tm));
	if (strptime(iso, "%Y-%m-%dT%H:%M:%S", &tm) == 0)
	{
		printf("%s\n", iso);
		return ;
	}
	strftime(out, sizeof(out), "%d/%m/%Y %H:%M", &tm);
	printf("%s\n", out);
}
