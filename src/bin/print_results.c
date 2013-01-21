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

#include "colors.h"

#define TST_PRM(__p) { if (__p == NULL) return; }

void print_configuration(tmdb_configuration_t *cfg)
{
	int i;

	TST_PRM(cfg);
	PRINTCT1("\n Configuration\n");

	PRINTCT2("base_url         ", cfg->base_url);
	PRINTCT2("secure_base_url  ", cfg->secure_base_url);

	for (i = 0; i < cfg->poster_sizes_cnt; i++)
		PRINTCT2("Posters          ", cfg->poster_sizes[i]);

	for (i = 0; i < cfg->backdrop_sizes_cnt; i++)
		PRINTCT2("Backdrops        ", cfg->backdrop_sizes[i]);

	for (i = 0; i < cfg->profile_sizes_cnt; i++)
		PRINTCT2("Profiles         ", cfg->profile_sizes[i]);

	for (i = 0; i < cfg->logo_sizes_cnt; i++)
		PRINTCT2("Logos            ", cfg->logo_sizes[i]);
}

void print_collection_images(tmdb_collection_images_t *collection_images)
{
	tmdb_image_t	   *backdrops;
	tmdb_image_t	   *posters;

	TST_PRM(collection_images);
	PRINTCT1("\n Collection Images [");
	PRINTCT1(collection_images->id);
	PRINTCT1("]\n\n");
	PRINTCT1("------------------------------------\n");

	backdrops = collection_images->backdrops;
	if (backdrops)
		PRINTCT1("-----------BACKDROPS----------------\n");
	while (backdrops) {
		PRINTCT2("aspect_ratio ", backdrops->aspect_ratio);
		PRINTCT2("file_path    ", backdrops->file_path);
		PRINTCT2("height       ", backdrops->height);
		PRINTCT2("width        ", backdrops->width);
		PRINTCT2("iso_639_1    ", backdrops->iso_639_1);
		PRINTCT2("vote_average ", backdrops->vote_average);
		PRINTCT2("vote_count   ", backdrops->vote_count);
		PRINTCT1("------------------------------------\n");
		backdrops = backdrops->next;
	}

	posters = collection_images->posters;
	if (posters)
		PRINTCT1("------------POSTERS----------------\n");
	while (posters) {
		PRINTCT2("aspect_ratio ", posters->aspect_ratio);
		PRINTCT2("file_path    ", posters->file_path);
		PRINTCT2("height       ", posters->height);
		PRINTCT2("width        ", posters->width);
		PRINTCT2("iso_639_1    ", posters->iso_639_1);
		PRINTCT2("vote_average ", posters->vote_average);
		PRINTCT2("vote_count   ", posters->vote_count);
		PRINTCT1("------------------------------------\n");
		posters = posters->next;
	}
}

void print_collection_info(tmdb_collection_t *collection_info)
{
	tmdb_movie_t	   *parts;

	TST_PRM(collection_info);
	parts = collection_info->parts;

	PRINTCT1("\n Collection Info [");
	PRINTCT1(collection_info->id);
	PRINTCT1("]\n\n");
	PRINTCT1("------------------------------------\n");
	PRINTCT2("backdrop_path ", collection_info->backdrop_path);
	PRINTCT2("name          ", collection_info->name);
	PRINTCT2("poster_path   ", collection_info->poster_path);

	if (parts)
		PRINTCT1("-------------PARTS------------------\n");
	while (parts) {
		PRINTCT2("backdrop_path ", parts->backdrop_path);
		PRINTID2("id            ", parts->id);
		PRINTCT2("poster_path   ", parts->poster_path);
		PRINTCT2("release_date  ", parts->release_date);
		PRINTCT2("title         ", parts->title);
		PRINTCT1("------------------------------------\n");
		parts = parts->next;
	}
}

void print_company_info(tmdb_company_t *companies)
{
	tmdb_company_t *info;

	TST_PRM(companies);
	info = companies;
	PRINTCT1("\n Company Info\n");
	while (info) {
		PRINTID2("id             ", info->id);
		PRINTCT2("name           ", info->name);
		PRINTCT2("logo_path      ", info->logo_path);
		PRINTCT2("description    ", info->description);
		PRINTCT2("headquarters   ", info->headquarters);
		PRINTCT2("homepage       ", info->homepage);

		info = info->parent_company;
		if (info)
			PRINTCT1("\n Parent Company Info\n");
	}
}

void print_company_movies(tmdb_movie_t *movies)
{
	tmdb_movie_t *info;

	TST_PRM(movies);
	info = movies;
	PRINTCT1("\n Company Movies\n");
	while (info) {
		PRINTCT2("backdrop_path  ", info->backdrop_path);
		PRINTID2("id             ", info->id);
		PRINTCT2("original_title ", info->original_title);
		PRINTCT2("release_date   ", info->release_date);
		PRINTCT2("poster_path    ", info->poster_path);
		PRINTCT2("title          ", info->title);
		PRINTCT2("vote_average   ", info->vote_average);
		PRINTCT2("vote_count     ", info->vote_count);
		PRINTCT1("------------------------------------------\n");
		info = info->next;
	}
}

void print_genre_list(tmdb_genre_t *genres)
{
	tmdb_genre_t *info;

	TST_PRM(genres);
	info = genres;
	PRINTCT1("\n Genre List\n");
	while (info) {
		PRINTID2("id        ", info->id);
		PRINTCT2("name      ", info->name);
		PRINTCT1("------------------------------------------\n");
		info = info->next;
	}
}

void print_genre_movies(tmdb_movie_t *movies)
{
	tmdb_movie_t *info;

	TST_PRM(movies);
	info = movies;
	PRINTCT1("\n Genre Movies\n");
	while (info) {
		PRINTCT2("backdrop_path  ", info->backdrop_path);
		PRINTID2("id             ", info->id);
		PRINTCT2("original_title ", info->original_title);
		PRINTCT2("release_date   ", info->release_date);
		PRINTCT2("poster_path    ", info->poster_path);
		PRINTCT2("title          ", info->title);
		PRINTCT2("vote_average   ", info->vote_average);
		PRINTCT2("vote_count     ", info->vote_count);
		PRINTCT1("------------------------------------------\n");
		info = info->next;
	}
}

void print_movie_info(tmdb_movie_t *movie_alt)
{
	tmdb_movie_t *info;

	TST_PRM(movie_alt);
	info = movie_alt;
	PRINTCT1("\n Movie Alternative Titles\n\n");
	PRINTCT1("------------------------------------\n");
	while (info) {
		if (info->production_countries)
			PRINTCT2("iso_3166_1 ",
				 info->production_countries->iso_3166_1);
		PRINTCT2("title      ", info->title);
		PRINTCT1("------------------------------------\n");
		info = info->next;
	}
}

void print_movie_casts(tmdb_movie_casts_t *movie_casts)
{
	tmdb_cast_t	   *cast;
	tmdb_crew_t	   *crew;

	TST_PRM(movie_casts);
	cast = movie_casts->cast;
	crew = movie_casts->crew;
	PRINTCT1("\n Movie Casts [");
	PRINTCT1(movie_casts->id);
	PRINTCT1("]\n\n");
	PRINTCT1("------------------------------------\n");

	PRINTCT1("\n Movie Casts : Casts\n");
	PRINTCT1("------------------------------------\n");
	while (cast) {
		PRINTID2("id           ", cast->id);
		PRINTCT2("name         ", cast->name);
		PRINTCT2("character    ", cast->character);
		PRINTCT2("order        ", cast->order);
		PRINTCT2("cast_id      ", cast->cast_id);
		PRINTCT2("profile_path ", cast->profile_path);
		PRINTCT1("------------------------------------\n");
		cast = cast->next;
	}

	PRINTCT1("\n Movie Casts : Crew\n");
	PRINTCT1("------------------------------------\n");
	while (crew) {
		PRINTID2("id           ", crew->id);
		PRINTCT2("name         ", crew->name);
		PRINTCT2("department   ", crew->department);
		PRINTCT2("job          ", crew->job);
		PRINTCT2("profile_path ", crew->profile_path);
		PRINTCT1("------------------------------------\n");
		crew = crew->next;
	}
}

void print_movie_images(tmdb_movie_images_t *movie_images)
{
	tmdb_image_t	   *backdrops;
	tmdb_image_t	   *posters;

	TST_PRM(movie_images);
	backdrops = movie_images->backdrops;
	posters = movie_images->posters;

	PRINTCT1("\n Movie Images [");
	PRINTCT1(movie_images->id);
	PRINTCT1("]\n\n");
	PRINTCT1("------------------------------------\n");

	PRINTCT1("\n Movie Images : Backdrops\n\n");
	PRINTCT1("------------------------------------\n");
	while (backdrops) {
		PRINTCT2("file_path    ", backdrops->file_path);
		PRINTCT2("width        ", backdrops->width);
		PRINTCT2("height       ", backdrops->height);
		PRINTCT2("iso_639_1    ", backdrops->iso_639_1);
		PRINTCT2("aspect_ratio ", backdrops->aspect_ratio);
		PRINTCT2("vote_average ", backdrops->vote_average);
		PRINTCT2("vote_count   ", backdrops->vote_count);
		PRINTCT1("------------------------------------\n");
		backdrops = backdrops->next;
	}

	PRINTCT1("\n Movie Images : Posters\n\n");
	PRINTCT1("------------------------------------\n");
	while (posters) {
		PRINTCT2("file_path    ", posters->file_path);
		PRINTCT2("width        ", posters->width);
		PRINTCT2("height       ", posters->height);
		PRINTCT2("iso_639_1    ", posters->iso_639_1);
		PRINTCT2("aspect_ratio ", posters->aspect_ratio);
		PRINTCT2("vote_average ", posters->vote_average);
		PRINTCT2("vote_count   ", posters->vote_count);
		PRINTCT1("------------------------------------\n");
		posters = posters->next;
	}
}

void print_movie_basic_info(tmdb_movie_t *info)
{
	tmdb_company_t	*company;
	tmdb_country_t	*country;
	tmdb_genre_t	*genre;
	tmdb_language_t	*language;

	TST_PRM(info);
	PRINTCT1("\n Movie Info\n");
	PRINTCT2("adult                   ", info->adult);
	PRINTCT2("backdrop_path           ", info->backdrop_path);
	PRINTCT2("belongs_to_collection   ", info->belongs_to_collection);
	PRINTCT2("budget                  ", info->budget);
	genre = info->genres;
	while (genre) {
		PRINTCT3("--> genre               ",
			 genre->id,
			 genre->name);
		genre = genre->next;
	}
	PRINTCT2("home_page               ", info->home_page);
	PRINTID2("id                      ", info->id);
	PRINTCT2("imdb_id                 ", info->imdb_id);
	PRINTCT2("original_title          ", info->original_title);
	PRINTCT2("overview                ", info->overview);
	PRINTCT2("popularity              ", info->popularity);
	PRINTCT2("poster_path             ", info->poster_path);
	company = info->production_companies;
	while (company) {
		PRINTCT3("--> production_companies",
			 company->id,
			 company->name);
		company = company->next;
	}
	country = info->production_countries;
	while (country) {
		PRINTCT3("--> production_countries",
			 country->iso_3166_1,
			 country->name);
		country = country->next;
	}
	PRINTCT2("release_date            ", info->release_date);
	PRINTCT2("revenue                 ", info->revenue);
	PRINTCT2("runtime                 ", info->runtime);
	language = info->spoken_languages;
	while (language) {
		PRINTCT3("--> spoken_languages    ",
			 language->iso_639_1,
			 language->name);
			 language = language->next;
	}
	PRINTCT2("status                  ", info->status);
	PRINTCT2("tagline                 ", info->tagline);
	PRINTCT2("title                   ", info->title);
	PRINTCT2("vote_average            ", info->vote_average);
	PRINTCT2("vote_count              ", info->vote_count);
}

void print_movie_keywords(tmdb_movie_keywords_t *movie_keywords)
{
	tmdb_keywords_t	   *keyword;

	TST_PRM(movie_keywords);
	keyword = movie_keywords->keywords;

	PRINTCT1("\n Movie Keywords [");
	PRINTCT1(movie_keywords->id);
	PRINTCT1("]\n\n");
	PRINTCT1("------------------------------------\n");

	while (keyword) {
		PRINTID2("id   ", keyword->id);
		PRINTCT2("name ", keyword->name);
		PRINTCT1("------------------------------------\n");
		keyword = keyword->next;
	}
}

void print_movie_now_playing(tmdb_movie_t *movies)
{
	tmdb_movie_t *info;

	TST_PRM(movies);
	info = movies;

	PRINTCT1("\n Movie Now Playing\n\n");
	PRINTCT1("------------------------------------\n");

	while (info) {
		PRINTCT2("backdrop_path  ", info->backdrop_path);
		PRINTID2("id             ", info->id);
		PRINTCT2("original_title ", info->original_title);
		PRINTCT2("release_date   ", info->release_date);
		PRINTCT2("poster_path    ", info->poster_path);
		PRINTCT2("title          ", info->title);
		PRINTCT2("vote_average   ", info->vote_average);
		PRINTCT2("vote_count     ", info->vote_count);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}

void print_movie_popular(tmdb_movie_t *movies)
{
	tmdb_movie_t *info;

	TST_PRM(movies);
	info = movies;

	PRINTCT1("\n Movie Popular\n\n");
	PRINTCT1("------------------------------------\n");

	while (info) {
		PRINTCT2("backdrop_path  ", info->backdrop_path);
		PRINTID2("id             ", info->id);
		PRINTCT2("original_title ", info->original_title);
		PRINTCT2("release_date   ", info->release_date);
		PRINTCT2("poster_path    ", info->poster_path);
		PRINTCT2("title          ", info->title);
		PRINTCT2("vote_average   ", info->vote_average);
		PRINTCT2("vote_count     ", info->vote_count);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}

void print_movie_releases(tmdb_movie_releases_t *movie_releases)
{
	tmdb_release_t	   *release;

	TST_PRM(movie_releases);
	release = movie_releases->releases;

	PRINTCT1("\n Movie Releases [");
	PRINTCT1(movie_releases->id);
	PRINTCT1("]\n\n");
	PRINTCT1("------------------------------------\n");

	while (release) {
		PRINTCT2("iso_3166_1    ", release->iso_3166_1);
		PRINTCT2("certification ", release->certification);
		PRINTCT2("release_date  ", release->release_date);
		PRINTCT1("------------------------------------\n");
		release = release->next;
	}
}

void print_movie_similar(tmdb_movie_t *movies)
{
	tmdb_movie_t *info;

	TST_PRM(movies);
	info = movies;

	PRINTCT1("\n Movie Similar\n\n");
	PRINTCT1("------------------------------------\n");

	while (info) {
		PRINTCT2("backdrop_path  ", info->backdrop_path);
		PRINTID2("id             ", info->id);
		PRINTCT2("original_title ", info->original_title);
		PRINTCT2("release_date   ", info->release_date);
		PRINTCT2("poster_path    ", info->poster_path);
		PRINTCT2("title          ", info->title);
		PRINTCT2("vote_average   ", info->vote_average);
		PRINTCT2("vote_count     ", info->vote_count);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}

void print_movie_top_rated(tmdb_movie_t *movies)
{
	tmdb_movie_t *info;

	TST_PRM(movies);
	info = movies;

	PRINTCT1("\n Movie Top Rated\n\n");
	PRINTCT1("------------------------------------\n");

	while (info) {
		PRINTCT2("backdrop_path  ", info->backdrop_path);
		PRINTID2("id             ", info->id);
		PRINTCT2("original_title ", info->original_title);
		PRINTCT2("release_date   ", info->release_date);
		PRINTCT2("poster_path    ", info->poster_path);
		PRINTCT2("title          ", info->title);
		PRINTCT2("vote_average   ", info->vote_average);
		PRINTCT2("vote_count     ", info->vote_count);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}

void print_movie_trailers(tmdb_movie_trailers_t *movie_trailers)
{
	tmdb_trailer_t	   *trailer;

	TST_PRM(movie_trailers);
	PRINTCT1("\n Movie Trailers [");
	PRINTCT1(movie_trailers->id);
	PRINTCT1("]\n\n");
	PRINTCT1("------------------------------------\n");

	PRINTCT1("\n Movie Trailers Quicktime\n\n");
	PRINTCT1("------------------------------------\n");
	trailer = movie_trailers->quicktime;
	while (trailer) {
		char buf[1024];
		PRINTCT2("name   ", trailer->name);
		PRINTCT2("size   ", trailer->size);
		sprintf(buf, "%s [%s%s]", trailer->source,
			"http://TODO/", trailer->source);
		PRINTCT2("source ", buf);
		PRINTCT1("------------------------------------\n");
		trailer = trailer->next;
	}

	PRINTCT1("\n Movie Trailers Youtube\n\n");
	PRINTCT1("------------------------------------\n");
	trailer = movie_trailers->youtube;
	while (trailer) {
		char buf[1024];
		PRINTCT2("name   ", trailer->name);
		PRINTCT2("size   ", trailer->size);
		sprintf(buf, "%s [%s%s]", trailer->source,
			"http://www.youtube.com/watch?v=", trailer->source);
		PRINTCT2("source ", buf);
		PRINTCT1("------------------------------------\n");
		trailer = trailer->next;
	}
}

void print_movie_translations(tmdb_movie_translations_t *movie_translations)
{
	tmdb_translation_t *translation;

	TST_PRM(movie_translations);
	PRINTCT1("\n Movie Translations [");
	PRINTCT1(movie_translations->id);
	PRINTCT1("]\n\n");
	PRINTCT1("------------------------------------\n");

	translation = movie_translations->translations;
	while (translation) {
		PRINTCT2("iso_639_1    ", translation->iso_639_1);
		PRINTCT2("name         ", translation->name);
		PRINTCT2("english_name ", translation->english_name);
		PRINTCT1("------------------------------------\n");
		translation = translation->next;
	}
}

void print_movie_upcoming(tmdb_movie_t *movies)
{
	tmdb_movie_t *info;

	TST_PRM(movies);
	info = movies;

	PRINTCT1("\n Movie Upcoming\n\n");
	PRINTCT1("------------------------------------\n");

	while (info) {
		PRINTCT2("backdrop_path  ", info->backdrop_path);
		PRINTID2("id             ", info->id);
		PRINTCT2("original_title ", info->original_title);
		PRINTCT2("release_date   ", info->release_date);
		PRINTCT2("poster_path    ", info->poster_path);
		PRINTCT2("title          ", info->title);
		PRINTCT2("vote_average   ", info->vote_average);
		PRINTCT2("vote_count     ", info->vote_count);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}

void print_person_credits(tmdb_person_credits_t *person_credits)
{
	tmdb_person_credits_t *info;

	TST_PRM(person_credits);
	info = person_credits;
	PRINTCT1("\n Person Credits\n\n");
	PRINTCT1("------------------------------------\n");
	while (info) {
		PRINTID2("id             ", info->movie->id);
		PRINTCT2("title          ", info->movie->title);
		PRINTCT2("character      ", info->character);
		PRINTCT2("original_title ", info->movie->original_title);
		PRINTCT2("poster_path    ", info->movie->poster_path);
		PRINTCT2("release_date   ", info->movie->release_date);
		PRINTCT2("adult          ", info->movie->adult);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}

void print_person_images(tmdb_image_t *person_images)
{
	tmdb_image_t *info;

	TST_PRM(person_images);
	info = person_images;
	PRINTCT1("\n Person Images\n\n");
	PRINTCT1("------------------------------------\n");
	while (info) {
		PRINTCT2("file_path    ", info->file_path);
		PRINTCT2("width        ", info->width);
		PRINTCT2("height       ", info->height);
		PRINTCT2("iso_639_1    ", info->iso_639_1);
		PRINTCT2("aspect_ratio ", info->aspect_ratio);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}

void print_person_info(tmdb_person_t *person)
{
	tmdb_person_t *info;
	int	aka;

	TST_PRM(person);
	info = person;

	PRINTCT1("\n Person Info\n\n");
	PRINTCT1("------------------------------------\n");
	if (info) {
		PRINTCT2("adult          ", info->adult);
		for (aka = 0; aka < info->aka_cnt; aka++)
			PRINTCT2("also_known_as  ", info->also_known_as[aka]);

		PRINTCT2("biography      ", info->biography);
		PRINTCT2("birthday       ", info->birthday);
		PRINTCT2("deathday       ", info->deathday);
		PRINTCT2("homepage       ", info->homepage);
		PRINTID2("id             ", info->id);
		PRINTCT2("name           ", info->name);
		PRINTCT2("place_of_birth ", info->place_of_birth);
		PRINTCT2("profile_path   ", info->profile_path);
		PRINTCT1("------------------------------------\n");
	}
}

void print_person_latest(tmdb_person_t *person)
{
	tmdb_person_t *info;
	int	aka;

	TST_PRM(person);
	info = person;
	PRINTCT1("\n Person Latest\n\n");
	PRINTCT1("------------------------------------\n");
	if (info) {
		PRINTCT2("adult          ", info->adult);
		for (aka = 0; aka < info->aka_cnt; aka++)
			PRINTCT2("also_known_as  ", info->also_known_as[aka]);

		PRINTCT2("biography      ", info->biography);
		PRINTCT2("birthday       ", info->birthday);
		PRINTCT2("deathday       ", info->deathday);
		PRINTCT2("homepage       ", info->homepage);
		PRINTID2("id             ", info->id);
		PRINTCT2("name           ", info->name);
		PRINTCT2("place_of_birth ", info->place_of_birth);
		PRINTCT2("profile_path   ", info->profile_path);
		PRINTCT1("------------------------------------\n");
	}
}

void print_search_companies(tmdb_company_t *companies)
{
	tmdb_company_t *info;

	TST_PRM(companies);
	info = companies;
	PRINTCT1("\n Company Search Results\n\n");
	PRINTCT1("------------------------------------\n");
	while (info) {
		PRINTID2("id        ", info->id);
		PRINTCT2("name      ", info->name);
		PRINTCT2("logo_path ", info->logo_path);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}

void print_search_movies(tmdb_movie_t *movies)
{
	tmdb_movie_t *info;

	TST_PRM(movies);
	info = movies;
	PRINTCT1("\n Movie Search Results\n\n");
	PRINTCT1("------------------------------------\n");
	while (info) {
		PRINTCT2("adult          ", info->adult);
		PRINTCT2("backdrop_path  ", info->backdrop_path);
		PRINTID2("id             ", info->id);
		PRINTCT2("original_title ", info->original_title);
		PRINTCT2("release_date   ", info->release_date);
		PRINTCT2("poster_path    ", info->poster_path);
		PRINTCT2("popularity     ", info->popularity);
		PRINTCT2("title          ", info->title);
		PRINTCT2("vote_average   ", info->vote_average);
		PRINTCT2("vote_count     ", info->vote_count);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}

void print_search_persons(tmdb_person_t *persons)
{
	tmdb_person_t *info;

	TST_PRM(persons);
	info = persons;
	PRINTCT1("\n Person Search Results\n\n");
	PRINTCT1("------------------------------------\n");
	while (info) {
		PRINTCT2("adult        ", info->adult);
		PRINTID2("id           ", info->id);
		PRINTCT2("name         ", info->name);
		PRINTCT2("profile_path ", info->profile_path);
		PRINTCT1("------------------------------------\n");

		info = info->next;
	}
}



