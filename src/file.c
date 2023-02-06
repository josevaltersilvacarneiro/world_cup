#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef config_h
#include "config.h"
#endif /* config_h */

#define FILENAME "data.json"

bool
does_file_exist(const String filename)
{
	return access(filename, F_OK) == 0;
}

CUP
*get_data(void)
{
	CUP *cup = calloc(1, sizeof(CUP));

	cup->teams = calloc(1, sizeof(TEAM));
	cup->games = calloc(1, sizeof(GAME));

	cup->teams->next = NULL;
	cup->games->next = NULL;
	
	if (!does_file_exist(FILENAME)) {
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
		for (TEAM *team_ptr = cup->teams->next; team_ptr != NULL; team_ptr = team_ptr->next) {
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
		for (GAME *game_ptr = cup->games->next; game_ptr != NULL; game_ptr = game_ptr->next) {
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
		printf("There is an error and the data were lost\n");

	free(cup->games);
	free(cup->teams);
	free(cup);
}
