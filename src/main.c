/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 03:05:38 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/18 04:33:13 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#define APIKEY "Mettre api key"
#define BUFFER_SIZE 10000

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) 
{
    size_t total_size = size * nmemb;
    strncat((char*)userp, (const char*)contents, total_size);
    return total_size;
}
void print_next_passage(const char* json)
{
    cJSON *root = NULL;
    cJSON *siri = NULL;
    cJSON *service = NULL;
    cJSON *stopMonitoring = NULL;
    cJSON *firstDelivery = NULL;
    cJSON *visits = NULL;
    cJSON *firstVisit = NULL;
    cJSON *journey = NULL;
    cJSON *call = NULL;
    cJSON *expected = NULL;

    root = cJSON_Parse(json);
    if (!root) {
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
        printf("Aucun passage imminent trouvé.\n");
        goto end;
    }

    firstVisit = cJSON_GetArrayItem(visits, 0);
    journey = cJSON_GetObjectItem(firstVisit, "MonitoredVehicleJourney");
    if (!journey) goto end;
    call = cJSON_GetObjectItem(journey, "MonitoredCall");
    if (!call) goto end;
    expected = cJSON_GetObjectItem(call, "ExpectedArrivalTime");
    if (!expected) goto end;

    printf("Prochain passage : %s\n", expected->valuestring);

end:
    cJSON_Delete(root);
}

void print_last_passage(const char* json) {
    cJSON *root = NULL, *siri = NULL, *service = NULL, *stopMonitoring = NULL;
    cJSON *firstDelivery = NULL, *visits = NULL, *visit = NULL;
    cJSON *journey = NULL, *call = NULL, *expected = NULL;
    int i, n;
    const char* last_time = NULL;

    root = cJSON_Parse(json);
    if (!root) {
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
    for (i = 0; i < n; ++i) {
        visit = cJSON_GetArrayItem(visits, i);
        journey = cJSON_GetObjectItem(visit, "MonitoredVehicleJourney");
        if (!journey) continue;
        call = cJSON_GetObjectItem(journey, "MonitoredCall");
        if (!call) continue;
        expected = cJSON_GetObjectItem(call, "ExpectedArrivalTime");
        if (!expected) continue;
        last_time = expected->valuestring; // On prend la dernière valeur rencontrée
    }

    if (last_time)
        printf("Dernier passage annoncé à Porte de Clichy (ligne 14) : %s\n", last_time);
    else
        printf("Aucun passage trouvé.\n");

end:
    cJSON_Delete(root);
}

int main(void) 
{
    CURL *curl;
    CURLcode res;
    char buffer[BUFFER_SIZE] = {0}; // Buffer pour stocker la réponse

    struct curl_slist *headers = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://prim.iledefrance-mobilites.fr/marketplace/stop-monitoring?MonitoringRef=STIF:StopPoint:Q:479062:");
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "apikey: " APIKEY);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
	{
            print_next_passage(buffer);
	    print_last_passage(buffer);
	}

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}

