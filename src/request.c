/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:53:05 by ascordil          #+#    #+#             */
/*   Updated: 2025/05/23 00:44:33 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ratp.h"


static size_t	write_callback(void *contents, size_t size, size_t nmemb, void *userp) 
{
    size_t total_size = size * nmemb;

    strncat((char*)userp, (const char*)contents, total_size);
    return total_size;
}



CURLcode	do_request(char *stop_point, char *content)
{

        CURL *curl;
        CURLcode res;
        struct curl_slist *headers = NULL;
        char url[512];

        snprintf(url, sizeof(url), "https://prim.iledefrance-mobilites.fr/marketplace/stop-monitoring?MonitoringRef=STIF:StopPoint:Q:%s:",stop_point);
        curl = curl_easy_init();
        if (curl)
	{
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "apikey: " APIKEY);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, content);
		res = curl_easy_perform(curl);
	}
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
	return (res);

}
