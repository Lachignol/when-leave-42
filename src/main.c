/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:17:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/23 00:51:58 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ratp.h"

void parse_and_print_schedule(const char *json_data) {
    cJSON *root = cJSON_Parse(json_data);
    if (!root) {
        printf("Erreur parsing JSON\n");
        return;
    }

    cJSON *siri = cJSON_GetObjectItem(root, "Siri");
    if (!siri) {
        cJSON_Delete(root);
        return;
    }

    cJSON *serviceDelivery = cJSON_GetObjectItem(siri, "ServiceDelivery");
    if (!serviceDelivery) {
        cJSON_Delete(root);
        return;
    }

    cJSON *stopMonitoringDeliveryArr = cJSON_GetObjectItem(serviceDelivery, "StopMonitoringDelivery");
    if (!stopMonitoringDeliveryArr || !cJSON_IsArray(stopMonitoringDeliveryArr)) {
        cJSON_Delete(root);
        return;
    }

    cJSON *stopMonitoringDelivery = cJSON_GetArrayItem(stopMonitoringDeliveryArr, 0);
    if (!stopMonitoringDelivery) {
        cJSON_Delete(root);
        return;
    }

    cJSON *monitoredStopVisit = cJSON_GetObjectItem(stopMonitoringDelivery, "MonitoredStopVisit");
    if (!monitoredStopVisit || !cJSON_IsArray(monitoredStopVisit)) {
        cJSON_Delete(root);
        return;
    }

    int count = cJSON_GetArraySize(monitoredStopVisit);
    for (int i = 0; i < count; i++) {
        cJSON *visit = cJSON_GetArrayItem(monitoredStopVisit, i);
        if (!visit) continue;

        cJSON *journey = cJSON_GetObjectItem(visit, "MonitoredVehicleJourney");
        if (!journey) continue;

        // DirectionName[0].value
        const char *direction = "Inconnu";
        cJSON *directionNameArr = cJSON_GetObjectItem(journey, "DirectionName");
        if (directionNameArr && cJSON_IsArray(directionNameArr)) {
            cJSON *firstDirection = cJSON_GetArrayItem(directionNameArr, 0);
            if (firstDirection) {
                cJSON *val = cJSON_GetObjectItem(firstDirection, "value");
                if (val && cJSON_IsString(val)) {
                    direction = val->valuestring;
                }
            }
        }

        // MonitoredCall.ExpectedArrivalTime
        const char *expectedTime = "Inconnu";
        cJSON *monitoredCall = cJSON_GetObjectItem(journey, "MonitoredCall");
        if (monitoredCall) {
            cJSON *expectedArrivalTime = cJSON_GetObjectItem(monitoredCall, "ExpectedArrivalTime");
            if (expectedArrivalTime && cJSON_IsString(expectedArrivalTime)) {
                expectedTime = expectedArrivalTime->valuestring;
            }
        }

        printf("Direction : %-20s - ", direction);
	print_formatted_datetime(expectedTime);
    }

    cJSON_Delete(root);
}


int main(int argc, char **argv) 
{
	char *arret = NULL;
	char *ligne = NULL;
	char *code_to_search = NULL;
	char *transport_type = NULL;

	if (argc != 4) 
		return (printf("Usage : %s <numero_ligne> <station> <type de transport> \nExemple : %s 14 Madeleine METRO\n", argv[0], argv[0]), 1);
	if (parse_csv(arret, ligne, &code_to_search, transport_type, argv))
	{
		char content[BUFFER_SIZE] = {0};
		CURLcode res;
		res = do_request(code_to_search,content);
		if (res != CURLE_OK)
    			fprintf(stderr, "Probleme lors de la requete: %s\n", curl_easy_strerror(res));
		else
		{
			parse_and_print_schedule(content);
    			print_next_passage(content);
    			print_last_passage(content);
		}
	}
    return 0;
}

