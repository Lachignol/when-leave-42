/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:49:41 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/23 00:04:53 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ratp.h"

void print_next_passage(const char *json)
{
    cJSON *root = NULL, *siri = NULL, *service = NULL, *stopMonitoring = NULL;
    int deliveryCount = 0;

    root = cJSON_Parse(json);
    if (!root) {
        printf("Erreur de parsing JSON\n");
        return;
    }

    siri = cJSON_GetObjectItem(root, "Siri");
    service = siri ? cJSON_GetObjectItem(siri, "ServiceDelivery") : NULL;
    stopMonitoring = service ? cJSON_GetObjectItem(service, "StopMonitoringDelivery") : NULL;

    if (!stopMonitoring || !cJSON_IsArray(stopMonitoring) || (deliveryCount = cJSON_GetArraySize(stopMonitoring)) == 0) {
        printf("Aucun passage imminent trouvé.\n");
        cJSON_Delete(root);
        return;
    }

    printf("Tous les prochains passages :\n");

    for (int d = 0; d < deliveryCount; ++d) {
        cJSON *delivery = cJSON_GetArrayItem(stopMonitoring, d);
        if (!delivery) continue;

        cJSON *visits = cJSON_GetObjectItem(delivery, "MonitoredStopVisit");
        if (!visits || !cJSON_IsArray(visits)) continue;

        int visitCount = cJSON_GetArraySize(visits);
        for (int i = 0; i < visitCount; ++i) {
            cJSON *visit = cJSON_GetArrayItem(visits, i);
            if (!visit) continue;

            cJSON *journey = cJSON_GetObjectItem(visit, "MonitoredVehicleJourney");
            cJSON *call = journey ? cJSON_GetObjectItem(journey, "MonitoredCall") : NULL;
            cJSON *expected = call ? cJSON_GetObjectItem(call, "ExpectedArrivalTime") : NULL;
            cJSON *dest = journey ? cJSON_GetObjectItem(journey, "DestinationName") : NULL;

            const char *direction = (dest && dest->valuestring) ? dest->valuestring : "Inconnu";
            if (expected && expected->valuestring) {
                printf("  Direction : %-25s - Passage à ", direction);
                print_formatted_datetime(expected->valuestring);
            }
        }
    }

    cJSON_Delete(root);
}
// void	print_next_passage(const char *json)
// {
//     cJSON *root = NULL;
//     cJSON *siri = NULL;
//     cJSON *service = NULL;
//     cJSON *stopMonitoring = NULL;
//     cJSON *firstDelivery = NULL;
//     cJSON *visits = NULL;
//     cJSON *firstVisit = NULL;
//     cJSON *journey = NULL;
//     cJSON *call = NULL;
//     cJSON *expected = NULL;
//
//     root = cJSON_Parse(json);
//     if (!root)
//     {
// 	    printf("Erreur de parsing JSON\n");
// 	    return;
//     }
//     siri = cJSON_GetObjectItem(root, "Siri");
//     if (!siri) goto end;
//     service = cJSON_GetObjectItem(siri, "ServiceDelivery");
//     if (!service) goto end;
//     stopMonitoring = cJSON_GetObjectItem(service, "StopMonitoringDelivery");
//     if (!stopMonitoring || !cJSON_IsArray(stopMonitoring)) goto end;
//     firstDelivery = cJSON_GetArrayItem(stopMonitoring, 0);
//     if (!firstDelivery) goto end;
//     visits = cJSON_GetObjectItem(firstDelivery, "MonitoredStopVisit");
//     if (!visits || !cJSON_IsArray(visits) || cJSON_GetArraySize(visits) == 0) {
//         printf("Aucun passage imminent trouvé.\n");
//         goto end;
//     }
//     printf("array%s",visits->valuestring);
//     firstVisit = cJSON_GetArrayItem(visits, 0);
//     journey = cJSON_GetObjectItem(firstVisit, "MonitoredVehicleJourney");
//     if (!journey) goto end;
//     call = cJSON_GetObjectItem(journey, "MonitoredCall");
//     if (!call) goto end;
//     expected = cJSON_GetObjectItem(call, "ExpectedArrivalTime");
//     if (!expected) goto end;
//     printf("Prochain passage : ");
//     print_formatted_datetime(expected->valuestring);
//
// end:
//     cJSON_Delete(root);
// }

void print_last_passage(const char* json)
{
    cJSON *root = NULL, *siri = NULL, *service = NULL, *stopMonitoring = NULL;
    cJSON *firstDelivery = NULL, *visits = NULL, *visit = NULL;
    cJSON *journey = NULL, *call = NULL, *expected = NULL;
    int i, n;
    const char* last_time = NULL;

    root = cJSON_Parse(json);
    if (!root)
    {
        printf("Erreur de parsing JSON\n");
        return;
    }
    siri = cJSON_GetObjectItem(root, "Siri");
    if (!siri) goto end;
    service = cJSON_GetObjectItem(siri, "ServiceDelivery");
    if (!service) goto end;
    stopMonitoring = cJSON_GetObjectItem(service, "StopMonitoringDelivery");
    if (!stopMonitoring || !cJSON_IsArray(stopMonitoring)) goto end;
    firstDelivery = cJSON_GetArrayItem(stopMonitoring, 0);
    if (!firstDelivery) goto end;
    visits = cJSON_GetObjectItem(firstDelivery, "MonitoredStopVisit");
    if (!visits || !cJSON_IsArray(visits) || cJSON_GetArraySize(visits) == 0) {
        printf("Aucun dernier passage trouvé.\n");
        goto end;
    }
    n = cJSON_GetArraySize(visits);
    for (i = 0; i < n; ++i) 
    {
        visit = cJSON_GetArrayItem(visits, i);
        journey = cJSON_GetObjectItem(visit, "MonitoredVehicleJourney");
        if (!journey) continue;
        call = cJSON_GetObjectItem(journey, "MonitoredCall");
        if (!call) continue;
        expected = cJSON_GetObjectItem(call, "ExpectedArrivalTime");
        if (!expected) continue;
        last_time = expected->valuestring;
    }
    if (last_time)
    {
        printf("Dernier passage annoncé : ");
        print_formatted_datetime(last_time);
    }
    else
        printf("Aucun passage trouvé.\n");

end:
    cJSON_Delete(root);
}
