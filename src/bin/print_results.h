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

#ifndef __PRINT_RESULTS_H_
#define __PRINT_RESULTS_H_

void print_configuration(tmdb_configuration_t *cfg);

void print_collection_images(tmdb_collection_images_t *collection_images);
void print_collection_info(tmdb_collection_t *collection_info);

void print_company_info(tmdb_company_t *companies);
void print_company_movies(tmdb_movie_t *movies);

void print_genre_list(tmdb_genre_t *genres);
void print_genre_movies(tmdb_movie_t *movies);

void print_movie_info(tmdb_movie_t *movie_alt);
void print_movie_casts(tmdb_movie_casts_t *movie_casts);
void print_movie_images(tmdb_movie_images_t *movie_images);
void print_movie_basic_info(tmdb_movie_t *info);
void print_movie_keywords(tmdb_movie_keywords_t *movie_keywords);
void print_movie_now_playing(tmdb_movie_t *movies);
void print_movie_popular(tmdb_movie_t *movies);
void print_movie_releases(tmdb_movie_releases_t *movie_releases);
void print_movie_similar(tmdb_movie_t *movies);
void print_movie_top_rated(tmdb_movie_t *movies);
void print_movie_trailers(tmdb_movie_trailers_t *movie_trailers);
void print_movie_translations(tmdb_movie_translations_t *movie_translations);
void print_movie_upcoming(tmdb_movie_t *movies);

void print_person_credits(tmdb_person_credits_t *person_credits);
void print_person_images(tmdb_image_t *person_images);
void print_person_info(tmdb_person_t *person);
void print_person_latest(tmdb_person_t *person);

void print_search_companies(tmdb_company_t *companies);
void print_search_movies(tmdb_movie_t *movies);
void print_search_persons(tmdb_person_t *persons);

#endif
