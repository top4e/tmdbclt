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

#include "tmdb.h"
#include "utils.h"
#include "env.h"
#include "print_results.h"

#define API_KEY	"?api_key=1b0086a1c63c77c4b16f9349831f3153"

static tmdb_ctx_t tmdb_ctx;

static void configuration(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;

	cfg = tmdb_configuration();
	print_configuration(cfg);
	tmdb_clean_configuration(cfg);
}

static void search_person(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_person_t		*person;
	tmdb_person_t		*person_p;

	person = tmdb_search_person(opts->name, opts->adult);
	print_search_persons(person);

	cfg = tmdb_configuration();
	person_p = person;

	while (person_p) {
		tmdb_save_image_generic(cfg, person_p->profile_path,
					"./images/profiles");
		person_p = person_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_person_type(person);
}

static void search_movie(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_search_movie(opts->name,
				  opts->language,
				  opts->adult,
				  opts->year);

	print_search_movies(movie);
	cfg = tmdb_configuration();

	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path,
					"./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path,
					"./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

static void search_company(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_company_t		*company;
	tmdb_company_t		*company_p;

	company = tmdb_search_company(opts->name);
	print_search_companies(company);
	cfg = tmdb_configuration();
	company_p = company;
	while (company_p) {
		tmdb_save_image_generic(cfg, company_p->logo_path,
					"./images/logos");
		company_p = company_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_company_type(company);
}

static void movie_info(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_movie_info(opts->id, opts->language);
	print_movie_basic_info(movie);
	cfg = tmdb_configuration();
	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path, "./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path, "./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

static void movie_alt_titles(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_movie_alt_titles(opts->id, opts->country);
	print_movie_info(movie);
	cfg = tmdb_configuration();
	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path,
					"./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path,
					"./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

static void movie_casts(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_casts_t	*movie_casts;
	tmdb_cast_t		*cast;
	tmdb_crew_t		*crew;

	movie_casts = tmdb_movie_casts(opts->id);
	print_movie_casts(movie_casts);
	cfg = tmdb_configuration();

	cast = movie_casts->cast;
	while (cast) {
		tmdb_save_image_generic(cfg, cast->profile_path,
					"./images/profiles");
		cast = cast->next;
	}
	crew = movie_casts->crew;
	while (cast) {
		tmdb_save_image_generic(cfg, crew->profile_path,
					"./images/profiles");
		crew = crew->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_casts_type(movie_casts);
}

static void movie_images(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_images_t	*movie_images;

	movie_images = tmdb_movie_images(opts->id);
	print_movie_images(movie_images);
	cfg = tmdb_configuration();
	tmdb_save_image(cfg, movie_images->backdrops,
			"./images/backdrops");
	tmdb_save_image(cfg, movie_images->posters,
			"./images/posters");
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_images_type(movie_images);
}

static void movie_keywords(tmdb_options_t *opts)
{
	tmdb_movie_keywords_t	*movie_keywords;

	movie_keywords = tmdb_movie_keywords(opts->id);
	print_movie_keywords(movie_keywords);
	tmdb_clean_movie_keywords_type(movie_keywords);
}

static void movie_releases(tmdb_options_t *opts)
{
	tmdb_movie_releases_t	*movie_releases;

	movie_releases = tmdb_movie_releases(opts->id);
	print_movie_releases(movie_releases);
	tmdb_clean_movie_releases_type(movie_releases);
}

static void movie_trailers(tmdb_options_t *opts)
{
	tmdb_movie_trailers_t	*movie_trailers;

	movie_trailers = tmdb_movie_trailers(opts->id);
	print_movie_trailers(movie_trailers);
	tmdb_clean_movie_trailers_type(movie_trailers);
}

static void movie_translations(tmdb_options_t *opts)
{
	tmdb_movie_translations_t	*movie_translations;

	movie_translations = tmdb_movie_translations(opts->id);
	print_movie_translations(movie_translations);
	tmdb_clean_movie_translations_type(movie_translations);
}

static void movie_similar(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_movie_similar(opts->id, opts->language);
	print_movie_similar(movie);
	cfg = tmdb_configuration();

	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path,
					"./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path,
					"./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

static void movie_upcoming(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_movie_upcoming(opts->language);
	print_movie_upcoming(movie);
	cfg = tmdb_configuration();
	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path,
					"./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path,
					"./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

static void movie_now_playing(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_movie_now_playing(opts->language);
	print_movie_now_playing(movie);
	cfg = tmdb_configuration();
	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path,
					"./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path,
					"./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

static void movie_popular(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_movie_popular(opts->language);
	print_movie_popular(movie);
	cfg = tmdb_configuration();
	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path,
					"./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path,
					"./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

static void movie_top_rated(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_movie_top_rated(opts->language);
	print_movie_top_rated(movie);
	cfg = tmdb_configuration();
	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path,
					"./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path,
					"./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

static void collection_info(tmdb_options_t *opts)
{
	tmdb_collection_t	*collection;

	collection = tmdb_collection_info(opts->id, opts->language);
	print_collection_info(collection);
	tmdb_clean_collection_type(collection);
}

static void collection_images(tmdb_options_t *opts)
{
	tmdb_configuration_t		*cfg;
	tmdb_collection_images_t	*collection_images;

	collection_images = tmdb_collection_images(opts->id,
						   opts->language);
	print_collection_images(collection_images);
	cfg = tmdb_configuration();
	tmdb_save_image(cfg, collection_images->backdrops,
			"./images/backdrops");
	tmdb_save_image(cfg, collection_images->posters,
			"./images/posters");
	tmdb_clean_configuration(cfg);
	tmdb_clean_collection_images_type(collection_images);
}

static void person_info(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_person_t		*person;
	tmdb_person_t		*person_p;

	person = tmdb_person_info(opts->id);
	print_person_info(person);
	cfg = tmdb_configuration();
	person_p = person;
	while (person_p) {
		tmdb_save_image_generic(cfg, person_p->profile_path,
					"./images/profiles");
		person_p = person_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_person_type(person);
}

static void person_credits(tmdb_options_t *opts)
{
	tmdb_person_credits_t	*person_credits;

	person_credits = tmdb_person_credits(opts->id);
	print_person_credits(person_credits);
	tmdb_clean_person_credits_type(person_credits);
}

static void person_images(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_image_t		*image;

	image = tmdb_person_images(opts->id);
	print_person_images(image);
	cfg = tmdb_configuration();
	tmdb_save_image(cfg, image, "./images/profiles");
	tmdb_clean_configuration(cfg);
	tmdb_clean_image_type(image);
}

static void person_latest(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_person_t		*person;
	tmdb_person_t		*person_p;

	person = tmdb_person_latest();
	print_person_latest(person);
	cfg = tmdb_configuration();
	person_p = person;
	while (person_p) {
		tmdb_save_image_generic(cfg, person_p->profile_path,
					"./images/profiles");
		person_p = person_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_person_type(person);
}

static void company_movies(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_company_movies(opts->id, opts->language, NULL);
	print_company_movies(movie);
	cfg = tmdb_configuration();
	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path,
					"./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path,
					"./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

static void company_info(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_company_t		*company;
	tmdb_company_t		*company_p;

	company = tmdb_company_info(opts->id);
	print_company_info(company);
	cfg = tmdb_configuration();
	company_p = company;
	while (company_p) {
		tmdb_save_image_generic(cfg, company_p->logo_path,
					"./images/logos");
		company_p = company_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_company_type(company);
}

static void genre_list(tmdb_options_t *opts)
{
	tmdb_genre_t		*genre_list;

	genre_list = tmdb_genre_list(opts->language);
	print_genre_list(genre_list);
	tmdb_clean_genre_type(genre_list);
}

static void genre_movies(tmdb_options_t *opts)
{
	tmdb_configuration_t	*cfg;
	tmdb_movie_t		*movie;
	tmdb_movie_t		*movie_p;

	movie = tmdb_genre_movies(opts->id, opts->language, NULL);
	print_genre_movies(movie);
	cfg = tmdb_configuration();
	movie_p = movie;
	while (movie_p) {
		tmdb_save_image_generic(cfg, movie_p->backdrop_path,
					"./images/backdrops");
		tmdb_save_image_generic(cfg, movie_p->poster_path,
					"./images/posters");
		movie_p = movie_p->next;
	}
	tmdb_clean_configuration(cfg);
	tmdb_clean_movie_type(movie);
}

int main(int argc, char *argv[])
{
	tmdb_options_t			opts;

	tmdb_ctx.net_get = net_get;
	tmdb_ctx.net_init_data = net_data_chunk_init;
	tmdb_ctx.net_free_data = net_data_chunk_free;
	tmdb_ctx.api_key = API_KEY;

	if (tmdb_init(&tmdb_ctx))
		return -1;

	memset(&opts, 0, sizeof(tmdb_options_t));
	if (tmdb_getopt(argc, argv, &opts))
		return 0;

	switch (opts.method) {
	case SEARCH_PERSON:
		search_person(&opts);
		break;
	case SEARCH_MOVIE:
		search_movie(&opts);
		break;
	case SEARCH_COMPANY:
		search_company(&opts);
		break;
	case CONFIGURATION:
		configuration(&opts);
		break;
	case MOVIE:
		movie_info(&opts);
		break;
	case MOVIE_ALT_TITLES:
		movie_alt_titles(&opts);
		break;
	case MOVIE_CASTS:
		movie_casts(&opts);
		break;
	case MOVIE_IMAGES:
		movie_images(&opts);
		break;
	case MOVIE_KEYWORDS:
		movie_keywords(&opts);
		break;
	case MOVIE_RELEASES:
		movie_releases(&opts);
		break;
	case MOVIE_TRAILERS:
		movie_trailers(&opts);
		break;
	case MOVIE_TRANSLATIONS:
		movie_translations(&opts);
		break;
	case MOVIE_SIMILAR:
		movie_similar(&opts);
		break;
	case MOVIE_UPCOMING:
		movie_upcoming(&opts);
		break;
	case MOVIE_NOW_PLAYING:
		movie_now_playing(&opts);
		break;
	case MOVIE_POPULAR:
		movie_popular(&opts);
		break;
	case MOVIE_TOP_RATED:
		movie_top_rated(&opts);
		break;
	case COLLECTION:
		collection_info(&opts);
		break;
	case COLLECTION_IMAGES:
		collection_images(&opts);
		break;
	case PERSON:
		person_info(&opts);
		break;
	case PERSON_CREDITS:
		person_credits(&opts);
		break;
	case PERSON_IMAGES:
		person_images(&opts);
		break;
	case PERSON_LATEST:
		person_latest(&opts);
		break;
	case COMPANY_MOVIES:
		company_movies(&opts);
		break;
	case COMPANY:
		company_info(&opts);
		break;
	case GENRE_LIST:
		genre_list(&opts);
		break;
	case GENRE_MOVIES:
		genre_movies(&opts);
		break;
	default:
		break;
	}

	tmdb_free_opts(&opts);
	return 0;
}
