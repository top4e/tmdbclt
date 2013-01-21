/* TMDB - TheMovieDB web api library
* Copyright (C) 2012 Atanas Tulbenski <top4e@top4e.com>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library;
* if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <curl/curl.h>

#include "tmdb.h"

void net_data_chunk_init(net_data_t *data)
{
	data->body.memory = malloc(1);
	data->body.size = 0;
	data->header.memory = malloc(1);
	data->header.size = 0;
}

void net_data_chunk_free(net_data_t *data)
{
	if (data->body.memory)
		free(data->body.memory);
	
	if (data->header.memory)
		free(data->header.memory);
	
	data->body.memory = NULL;
	data->body.size = 0;
	data->header.memory = NULL;
	data->header.size = 0;
}

static size_t WriteMemoryCallback(void *contents,
				  size_t size,
				  size_t nmemb,
				  void *userp)
{
	size_t realsize = size * nmemb;
	MemoryStruct_t *mem = (MemoryStruct_t *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		exit(EXIT_FAILURE);
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

int net_get(const char *url_name,
	    const char *header_str,
	    net_data_t *data)
{
	CURL *curl_handle;

	if (url_name == NULL)
		return -1;

	if (data == NULL)
		return -1;

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */
	curl_handle = curl_easy_init();

	if (header_str != NULL)
		curl_easy_setopt(curl_handle, CURLOPT_HEADER, (long)header_str);

	curl_easy_setopt(curl_handle, CURLOPT_URL,
			 url_name);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION,
			 WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION,
			 WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA,
			 (void *)&data->body);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER,
			 (void *)&data->header);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_perform(curl_handle);
	curl_easy_cleanup(curl_handle);

	curl_global_cleanup();

	return 0;
}


static int do_mkdir(const char *path, mode_t mode)
{
	struct stat	st;
	int		status = 0;

	if (stat(path, &st) != 0) {
		if (mkdir(path, mode) != 0 && errno != EEXIST)
			status = -1;
	}
	else if (!S_ISDIR(st.st_mode)) {
		errno = ENOTDIR;
		status = -1;
	}

	return status;
}

static int mkpath(const char *path, mode_t mode)
{
	char           *pp;
	char           *sp;
	int             status;
	char           *copypath = strdup(path);

	status = 0;
	pp = copypath;
	while (status == 0 && (sp = strchr(pp, '/')) != 0) {
		if (sp != pp) {
			*sp = '\0';
			status = do_mkdir(copypath, mode);
			*sp = '/';
		}
		pp = sp + 1;
	}

	if (status == 0)
		status = do_mkdir(path, mode);

	free(copypath);
	return status;
}

static int save_image(char *filename, void *data, size_t size)
{
	FILE *imagefile;
	size_t written;

	imagefile = fopen(filename, "w");
	written = fwrite(data, 1, size, imagefile);
	fclose(imagefile);

	if (written != size)
		return -1;

	return 0;
}

int tmdb_save_image_generic(tmdb_configuration_t	*cfg,
			    const char			*filename,
			    const char			*filepath)
{
	int		result;
	char		fname_str[1024];
	char		url_str[1024];
	net_data_t	data;

	if (!cfg)
		return -1;
	if (!filename)
		return -1;
	if (!filepath)
		return -1;

	net_data_chunk_init(&data);

	sprintf(url_str, "%s%s%s", cfg->base_url, "original", filename);

	result = net_get(url_str, NULL, &data);

	if (!result) {
		sprintf(fname_str, "%s%s", filepath, filename);
		mkpath(filepath, 0777);
		save_image(fname_str, data.body.memory, data.body.size);
	}
	net_data_chunk_free(&data);

	return 0;
}

int tmdb_save_image(tmdb_configuration_t	*cfg,
		    tmdb_image_t		*image,
		    const char			*filepath)
{
	tmdb_image_t	*image_p;

	image_p = image;
	while (image_p) {
		tmdb_save_image_generic(cfg, image_p->file_path, filepath);
		image_p = image_p->next;
	}
	return 0;
}


