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
#include <getopt.h>

#include "colors.h"
#include "tmdb.h"
#include "env.h"
#include "print_results.h"

static struct option long_options[] = {
	/* Commands. */
	{"configuration",      no_argument,       NULL, 'a'},

	{"movie-info",	       required_argument, NULL, 'b'},
	{"movie-alt",          required_argument, NULL, 'c'},
	{"movie-casts",        required_argument, NULL, 'd'},
	{"movie-images",       required_argument, NULL, 'e'},
	{"movie-keywords",     required_argument, NULL, 'f'},
	{"movie-releases",     required_argument, NULL, 'g'},
	{"movie-trailers",     required_argument, NULL, 'h'},
	{"movie-translations", required_argument, NULL, 'i'},
	{"movie-similar",      required_argument, NULL, 'j'},
	{"movie-upcoming",     no_argument,       NULL, 'k'},
	{"movie-now-playing",  no_argument,       NULL, 'l'},
	{"movie-popular",      no_argument,       NULL, 'm'},
	{"movie-top-rated",    no_argument,       NULL, 'n'},

	{"collection-info",    required_argument, NULL, 'o'},
	{"collection-images",  required_argument, NULL, 'p'},

	{"person-info",        required_argument, NULL, 'q'},
	{"person-credits",     required_argument, NULL, 'r'},
	{"person-images",      required_argument, NULL, 's'},
	{"person-latest",      no_argument,       NULL, 't'},

	{"company-movies",     required_argument, NULL, 'u'},
	{"company-info",       required_argument, NULL, 'v'},

	{"genre-list",         optional_argument, NULL, 'w'},
	{"genre-movies",       required_argument, NULL, 'x'},

	{"search-person",      required_argument, NULL, 'P'},
	{"search-movie",       required_argument, NULL, 'M'},
	{"search-company",     required_argument, NULL, 'C'},

	{"language",           required_argument, NULL, 'L'},
	{"country",            required_argument, NULL, 'T'},
	{"adult",              no_argument,       NULL, 'A'},
	{"year",               required_argument, NULL, 'Y'},

	{0, 0, 0, 0},
};

static const char * const args[] = {
	/* Commands. */
	""              ,

	"movie_id"      ,
	"movie_id"      ,
	"movie_id"      ,
	"movie_id"      ,
	"movie_id"      ,
	"movie_id"      ,
	"movie_id"      ,
	"movie_id"      ,
	"movie_id"      ,
	""              ,
	""              ,
	""              ,
	""              ,

	"collection_id" ,
	"collection_id" ,

	"person_id"     ,
	"person_id"     ,
	"person_id"     ,
	""              ,

	"company_id"    ,
	"company_id"    ,

	""              ,
	"genre_id"      ,

	"person_name"   ,
	"movie_name"    ,
	"company_name"  ,

	"lang"		,
	"country"	,
	""		,
	"YYYY"		,

	NULL,
};

#define DESCRIPTION_LINE_OFFSET	74
#define ARGS_LINE_OFFSET	48

static const char * const desc[] = {
	/* Commands. */
	"Get the system wide configuration information for images.",

	"Get the basic movie information for a specific movie id.",
	"Get the alternative titles for a specific movie id.",
	"Get the cast information for a specific movie id.",
	"Get the images (posters and backdrops) for a specific movie id.",
	"Get the plot keywords for a specific movie id.",
	"Get the release date by country for a specific movie id.",
	"Get the trailers for a specific movie id.",
	"Get the translations for a specific movie id.",
	"Get the similar movies for a specific movie id.",
	"Get the list of upcoming movies.",
	"Get the list of movies playing in theatres.",
	"Get the list of popular movies on The Movie Database.",
	"Get the list of top rated movies.",

	"Get the basic collection information for a specific collection id." ,
	"Get all of the images for a particular collection by collection id." ,

	"Get the general person information for a specific id.",
	"Get the credits for a specific person id.",
	"Get the images for a specific person id.",
	"Get the latest person id.",

	"Get the list of movies associated with a particular company.",
	"Get the basic company information for a specific company id.",

	"Get the list of genres.",
	"Get the list of movies for a particular genre by id.",

	"Search for people by name.",
	"Search for movies by title.",
	"Search for companies by name.",

	"ISO 639 1 language ID.",
	"ISO 3166 1 country ID.",
	"Include adult content.",
	"Filter results by year.",

	NULL,
};

const char *short_options =
	"ab:c:d:e:f:g:h:i:j:klmno:p:q:r:s:tu:v:w::x:P:M:C:L:T:AY:";

static void print_usage(const char *prog_name)
{
	int i;
	int len1;
	char line_buffer[4096];

	printf("%sUsage: %s%s %sOPTION%s %sARGS%s\n",
	       COLOR_EMR, COLOR_RED, prog_name,
	       COLOR_EMB, COLOR_NONE, COLOR_EMG, COLOR_NONE);

	i = 0;

	while (long_options[i].name) {
		sprintf(line_buffer, " %s-%c%s, %s--%s%s",
			COLOR_EMB, (char)long_options[i].val,
			COLOR_NONE, COLOR_EMB,
			long_options[i].name, COLOR_NONE);
		len1 = strlen(line_buffer);
		printf("%s", line_buffer);

		sprintf(line_buffer, "%s%s%s", COLOR_EMG, args[i], COLOR_NONE);
		while (len1 < ARGS_LINE_OFFSET) {
			printf(" ");
			len1++;
		}
		printf("%s", line_buffer);
		len1 += strlen(line_buffer);
		while (len1 < DESCRIPTION_LINE_OFFSET) {
			printf(" ");
			len1++;
		}
		printf(" - %s%s%s\n", COLOR_EMY, desc[i], COLOR_NONE);
		i++;
	}
}

int tmdb_getopt(int argc, char **argv, tmdb_options_t *opts)
{
	int c;
	int result = 0;

	if (argc < 2) {
		print_usage(argv[0]);
		result = -1;
	}

	while (!result)	{
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, short_options,
				 long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c) {
		case 'P':
			opts->name = strdup(optarg);
			opts->method = SEARCH_PERSON;
			break;
		case 'M':
			opts->name = strdup(optarg);
			opts->method = SEARCH_MOVIE;
			break;
		case 'C':
			opts->name = strdup(optarg);
			opts->method = SEARCH_COMPANY;
			break;
		case 'a':
			opts->method = CONFIGURATION;
			break;
		case 'b':
			opts->id = strdup(optarg);
			opts->method = MOVIE;
			break;
		case 'c':
			opts->id = strdup(optarg);
			opts->method = MOVIE_ALT_TITLES;
			break;
		case 'd':
			opts->id = strdup(optarg);
			opts->method = MOVIE_CASTS;
			break;
		case 'e':
			opts->id = strdup(optarg);
			opts->method = MOVIE_IMAGES;
			break;
		case 'f':
			opts->id = strdup(optarg);
			opts->method = MOVIE_KEYWORDS;
			break;
		case 'g':
			opts->id = strdup(optarg);
			opts->method = MOVIE_RELEASES;
			break;
		case 'h':
			opts->id = strdup(optarg);
			opts->method = MOVIE_TRAILERS;
			break;
		case 'i':
			opts->id = strdup(optarg);
			opts->method = MOVIE_TRANSLATIONS;
			break;
		case 'j':
			opts->id = strdup(optarg);
			opts->method = MOVIE_SIMILAR;
			break;
		case 'k':
			opts->method = MOVIE_UPCOMING;
			break;
		case 'l':
			opts->method = MOVIE_NOW_PLAYING;
			break;
		case 'm':
			opts->method = MOVIE_POPULAR;
			break;
		case 'n':
			opts->method = MOVIE_TOP_RATED;
			break;
		case 'o':
			opts->id = strdup(optarg);
			opts->method = COLLECTION;
			break;
		case 'p':
			opts->id = strdup(optarg);
			opts->method = COLLECTION_IMAGES;
			break;
		case 'q':
			opts->id = strdup(optarg);
			opts->method = PERSON;
			break;
		case 'r':
			opts->id = strdup(optarg);
			opts->method = PERSON_CREDITS;
			break;
		case 's':
			opts->id = strdup(optarg);
			opts->method = PERSON_IMAGES;
			break;
		case 't':
			opts->method = PERSON_LATEST;
			break;
		case 'u':
			opts->id = strdup(optarg);
			opts->method = COMPANY_MOVIES;
			break;
		case 'v':
			opts->id = strdup(optarg);
			opts->method = COMPANY;
			break;
		case 'w':
			opts->method = GENRE_LIST;
			break;
		case 'x':
			opts->id = strdup(optarg);
			opts->method = GENRE_MOVIES;
			break;
		case 'L':
			opts->language = strdup(optarg);
			break;
		case 'T':
			opts->country = strdup(optarg);
			break;
		case 'A':
			opts->adult = 1;
			break;
		case 'Y':
			opts->year = strdup(optarg);
			break;
		default:
			print_usage(argv[0]);
			result = -1;
			break;
		}
	}

	return result;
}

void tmdb_free_opts(tmdb_options_t *opts)
{
	if (!opts)
		return;

	if (opts->id) {
		free(opts->id);
		opts->id = NULL;
	}

	if (opts->name) {
		free(opts->name);
		opts->name = NULL;
	}

	if (opts->language) {
		free(opts->language);
		opts->language = NULL;
	}

	if (opts->country) {
		free(opts->country);
		opts->country = NULL;
	}

	if (opts->year) {
		free(opts->year);
		opts->year = NULL;
	}
}
