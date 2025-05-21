/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_csv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:54:11 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/21 22:42:04 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ratp.h"

int	parse_csv(char *arret, char *ligne, char **code_to_search, char *transport_type, char **argv)
{
	char line[BUFFER_SIZE];
	FILE *fp = fopen("assets/gares.csv", "r");
	if (!fp) 
		return (perror("fopen"), 1);
	fgets(line, sizeof(line), fp); // skip header
	while (fgets(line, sizeof(line), fp)) 
	{
		char temp[BUFFER_SIZE];
		strncpy(temp, line, BUFFER_SIZE);
		temp[BUFFER_SIZE-1] = '\0';
		char *v1  = strtok(temp, ";");
        	char *v2  = strtok(NULL, ";");
        	char *v3  = strtok(NULL, ";");
        	arret  = strtok(NULL, ";");
        	char *v5  = strtok(NULL, ";");
        	char *v6  = strtok(NULL, ";");
        	*code_to_search  = strtok(NULL, ";");
        	char *v8  = strtok(NULL, ";");
        	char *v9  = strtok(NULL, ";");
        	char *v10 = strtok(NULL, ";");
        	char *v11 = strtok(NULL, ";");
        	ligne = strtok(NULL, ";");
        	transport_type = strtok(NULL, ";");
        	char *v14 = strtok(NULL, ";");
        	char *v15 = strtok(NULL, ";");

        printf(
            "v1: %s\n"
            "v2: %s\n"
            "v3: %s\n"
            "arret: %s\n"
            "v5: %s\n"
            "v6: %s\n"
            "v7: %s\n"
            "v8: %s\n"
            "v9: %s\n"
            "v10: %s\n"
            "v11: %s\n"
            "ligne: %s\n"
            "transport_type: %s\n"
            "v14: %s\n"
            "v15: %s\n"
            "-----------------------------\n",
            v1  ? v1  : "",
            v2  ? v2  : "",
            v3  ? v3  : "",
            arret  ? arret  : "",
            v5  ? v5  : "",
            v6  ? v6  : "",
            *code_to_search  ? *code_to_search  : "",
            v8  ? v8  : "",
            v9  ? v9  : "",
            v10 ? v10 : "",
            v11 ? v11 : "",
            ligne ? ligne : "",
            transport_type ? transport_type : "",
            v14 ? v14 : "",
            v15 ? v15 : ""
        );
	if (strcmp(ligne, argv[1])==0 && strcmp(transport_type, argv[3])==0 && strcmp(arret, argv[2]) == 0)
	{
		printf("Pour la ligne de %s %s a l'arret %s :\n",transport_type, ligne, arret);
    		return (fclose(fp), 1);
	}
    }
    return (0);
}
