#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef config_h
#include "config.h"
#endif /* config_h */

#define FILENAME "data.json"
#define MAXIMUM_AMOUNT_OF_CHARACTERS_PER_LINE 120

extern String str(const String string);

extern TEAM *convert_to_team_ptr(TEAM **first_team, const String team_name);

extern TEAM *add_team(
			TEAM **first_team,
			const char group,
			const String name,
			const unsigned int pt,
			const unsigned int gs,
			const unsigned int gc,
			const unsigned int gd
		     );

extern GAME *add_game(
			TEAM **first_team,
			GAME **first_game,
			TEAM *team_one,
			TEAM *team_two,
			const unsigned short team_one_goals,
			const unsigned short team_two_goals,
			const unsigned int date,
			const String place
		     );


void free_teams(TEAM **first_team);
void free_games(GAME **first_game);

bool
does_file_exist(const String filename)
{
	return access(filename, F_OK) == 0;
}

CUP
*get_data(void)
{
	FILE *fp;
	CUP  *cup;

	fp = does_file_exist(FILENAME) ? fopen(FILENAME, "r") : NULL;

	cup = calloc(1, sizeof(CUP));

	cup->first_team = NULL;
	cup->first_game = NULL;

	if (fp != NULL) {
		/* The file was opened for reading successfully */

		char buf_line[MAXIMUM_AMOUNT_OF_CHARACTERS_PER_LINE]; /* buffer */
		String eptr; /* or char *eptr */

		/* TEAM */

		char   group;
		String name;

		size_t pt;
		size_t gs;
		size_t gc;
		int    gd;

		/* GAME */

		TEAM *team_one;
		TEAM *team_two;

		unsigned short team_one_goals;
		unsigned short team_two_goals;
		unsigned int   date;
		String place;

		/* TEAM */

		fscanf(fp, "%[^\n]\n", buf_line);

		for (fscanf(fp, "%[^\n]", buf_line); strcmp(buf_line, "# games"); ) {
			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			group = *str(buf_line);
			
			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			name = str(buf_line);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			pt = strtoul(buf_line, &eptr, 10);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			gs = strtoul(buf_line, &eptr, 10);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			gc = strtoul(buf_line, &eptr, 10);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			gd = strtoul(buf_line, &eptr, 10);

			fscanf(fp, "%s\n", buf_line);
			fscanf(fp, "%[^\n]\n", buf_line);

			/* Adding */

			add_team(&cup->first_team, group, name, pt, gs, gc, gd);
		}
		
		/* GAME */

		for (; !feof(fp); ) {
			fscanf(fp, "%[^\n]", buf_line);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			team_one = convert_to_team_ptr(&cup->first_team, buf_line);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			team_two = convert_to_team_ptr(&cup->first_team, buf_line);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			team_one_goals = strtoul(buf_line, &eptr, 10);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			team_two_goals = strtoul(buf_line, &eptr, 10);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			date = strtoul(buf_line, &eptr, 10);

			fscanf(fp, "%[^:] : %s", buf_line, buf_line);
			place = str(buf_line);

			fscanf(fp, "\n%[^\n]", buf_line);

			/* Adding */

			add_game(
				&cup->first_team,
				&cup->first_game,
				team_one,
				team_two,
				team_one_goals,
				team_two_goals,
				date,
				place
				);
		}

		if(fclose(fp))
			puts("There is an error and the data was lost");
	}

	return cup;
}

void
push_data(CUP *cup)
{
	FILE *fp;

	fp = fopen(FILENAME, "w");

	if (fp == NULL)
		printf("There is an error: could not open %s file in write mode\n", FILENAME);
	else {
		fprintf(fp, "# teams\n");
		for (TEAM *team_ptr = cup->first_team; team_ptr != NULL; team_ptr = team_ptr->next) {
			fprintf(fp, "{\n");
			
			fprintf(fp, "\tgroup : %c\n", team_ptr->group);
			fprintf(fp, "\tname : %s\n", team_ptr->name);

			fprintf(fp, "\tpt : %u\n", team_ptr->pt);
			fprintf(fp, "\tgs : %u\n", team_ptr->gs);
			fprintf(fp, "\tgc : %u\n", team_ptr->gc);

			fprintf(fp, "\tgd : %d\n", team_ptr->gd);
			
			fprintf(fp, "}\n");
		}

		fprintf(fp, "# games\n");
		for (GAME *game_ptr = cup->first_game; game_ptr != NULL; game_ptr = game_ptr->next) {
			fprintf(fp, "{\n");
			
			fprintf(fp, "\tteam_one : %s\n", game_ptr->team_one->name);
			fprintf(fp, "\tteam_two : %s\n", game_ptr->team_two->name);

			fprintf(fp, "\tteam_one_goals : %d\n", game_ptr->team_one_goals);
			fprintf(fp, "\tteam_two_goals : %d\n", game_ptr->team_two_goals);

			fprintf(fp, "\tdate : %d\n", game_ptr->date);

			fprintf(fp, "}\n");
		}
	}

	if (fclose(fp))
		puts("There is an error and the data were lost");

	free_games(&cup->first_game);
	free_teams(&cup->first_team);
	free(cup);
}

void
free_teams(TEAM **first_team)
{
	TEAM *next;

	for (; *first_team != NULL; ) {
		next = (*first_team)->next;
		free(*first_team);
		*first_team = next;
	}
}

void
free_games(GAME **first_game)
{
	GAME *next;

	for (; *first_game != NULL; ) {
		next = (*first_game)->next;
		free(*first_game);
		*first_game = next;
	}
}
