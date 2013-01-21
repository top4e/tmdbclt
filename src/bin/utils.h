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
* if not, see <http://www.gnu.org/licenses/>
*/
#ifndef __FILEHELPER_H_
#define __FILEHELPER_H_

int tmdb_save_image(tmdb_configuration_t	*cfg,
		    tmdb_image_t		*image,
		    const char			*filepath);

int tmdb_save_image_generic(tmdb_configuration_t	*cfg,
			    const char			*filename,
			    const char			*filepath);

int net_get(const char *url_name,
	    const char *header_str,
	    net_data_t *data);

void net_data_chunk_init(net_data_t *data);
void net_data_chunk_free(net_data_t *data);
#endif
