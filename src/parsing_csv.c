/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_csv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:54:11 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/23 00:40:28 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ratp.h"

int	parse_csv(char *arret, char *ligne, char **code_to_search, char *transport_type, char **argv)
{
	char line[BUFFER_SIZE];
	int	i;
	int	nb_column = 15;
	FILE *fp = fopen("assets/gares.csv", "r");
	if (!fp) 
		return (perror("fopen"), 1);
	//skip header
	fgets(line, sizeof(line), fp); // skip header
	while (fgets(line, sizeof(line), fp)) 
	{
		char temp[BUFFER_SIZE];
		strncpy(temp, line, BUFFER_SIZE);
		temp[BUFFER_SIZE-1] = '\0';
		i = 0;
		// printf("---------------------");
		while (i < nb_column)
		{
			if (i == 0)
			{
				strtok(temp, ";");
				i++;
				continue;
			}
			else if (i == 3)
			{
        			arret  = strtok(NULL, ";");
				// printf("arret %s\n",arret);
			}
			else if (i == 6)
			{
        			*code_to_search  = strtok(NULL, ";");
				// printf("code %s\n",*code_to_search);

			}
			else if (i == 11)
			{

        			ligne = strtok(NULL, ";");
				// printf("ligne %s\n",ligne);
			}
			else if (i == 12)
			{
        			transport_type = strtok(NULL, ";");
				// printf("type de transport %s\n",transport_type);

			}
			else
				printf("%s\n", strtok(NULL,";"));
			i++;
		}
			// printf("---------------------");

		to_uppercase(arret);
		to_uppercase(argv[2]);
	if (strcmp(ligne, argv[1])==0 && strcmp(transport_type, argv[3])==0 && strcmp(arret, argv[2]) == 0)
	{
		printf("Pour la ligne de %s %s a l'arret %s :\n",transport_type, ligne, arret);
    		return (fclose(fp), 1);
	}
    }
    return (0);
}
