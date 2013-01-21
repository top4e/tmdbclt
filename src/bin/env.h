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

#ifndef __ENV_H_
#define __ENV_H_

typedef enum tmdb_method_type_e {
	CONFIGURATION,

	AUTH_TOKEN_NEW,
	AUTH_SESSION_NEW,

	ACOUNT,
	ACOUNT_FAV_MOVIES,
	ACOUNT_FAV,
	ACOUNT_RATED,
	ACOUNT_WATCHLIST,

	MOVIE,
	MOVIE_ALT_TITLES,
	MOVIE_CASTS,
	MOVIE_IMAGES,
	MOVIE_KEYWORDS,
	MOVIE_RELEASES,
	MOVIE_TRAILERS,
	MOVIE_TRANSLATIONS,
	MOVIE_SIMILAR,
	MOVIE_CHANGES,
	MOVIE_LATEST,
	MOVIE_UPCOMING,
	MOVIE_NOW_PLAYING,
	MOVIE_POPULAR,
	MOVIE_TOP_RATED,
	MOVIE_RATING,

	COLLECTION,
	COLLECTION_IMAGES,

	PERSON,
	PERSON_CREDITS,
	PERSON_IMAGES,
	PERSON_CHANGES,
	PERSON_LATEST,

	COMPANY,
	COMPANY_MOVIES,

	GENRE_LIST,
	GENRE_MOVIES,

	SEARCH_MOVIE,
	SEARCH_PERSON,
	SEARCH_COMPANY,
} tmdb_method_type_t;

typedef struct tmdb_options_s {
	tmdb_method_type_t	method;
	char			*id;
	char			*name;
	char			*language;
	char			*country;
	int			adult;
	char			*year;
} tmdb_options_t;

int tmdb_getopt(int argc, char **argv, tmdb_options_t *opts);
void tmdb_free_opts(tmdb_options_t *opts);

#endif
