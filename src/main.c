/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:17:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/21 01:41:42 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ratp.h"

int main(int argc, char **argv) 
{
	char *arret = NULL;
	char *ligne = NULL;
	char *code_to_search = NULL;
	char *transport_type = NULL;

	if (argc != 4) 
		return (printf("Usage : %s <numero_ligne> <station> <type de transport> \nExemple : %s 14 Madeleine METRO\n", argv[0], argv[0]), 1);
	if (parse_csv(arret, ligne, code_to_search, transport_type, argv))
	{
		char content[BUFFER_SIZE] = {0};
		CURLcode res;
		res = do_request(code_to_search,content);
		if (res != CURLE_OK)
    			fprintf(stderr, "Probleme lors de la requete: %s\n", curl_easy_strerror(res));
		else
		{
    			print_next_passage(content);
    			print_last_passage(content);
		}
	}
    return 0;
}

