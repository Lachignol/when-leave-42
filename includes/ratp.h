/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:54:22 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/23 00:52:20 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RATP_H
#define _RATP_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <time.h>
#include <strings.h>

#define APIKEY "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define BUFFER_SIZE 20000


CURLcode	do_request(char *stop_point, char *content);
int		parse_csv(char *arret, char *ligne, char **code_to_search, char *transport_type, char **argv);
void		print_formatted_datetime(const char *iso);
void 		print_next_passage(const char* json);
void 		print_last_passage(const char* json);
char		*trim(char *str);
void 		to_uppercase(char *str);

#endif
