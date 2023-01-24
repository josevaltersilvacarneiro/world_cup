#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.h"

#ifndef config_h
#include "config.h"
#endif /* config_h */

char groups[] = {
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
};

extern void regist_teams(TEAM *teams);

void
regist(TEAM *teams, GAME *games)
{
	char options[2];
	char option;

	printf("1 → Register teams\n");
	options[0] = 't';

	printf("2 → Register games\n");
	options[1] = 'g';

	option = get_option(options, 2);

	switch (option) {
		case 't':
			regist_teams(teams);
			break;
		case 'g':
			break;
	}
}

void
print_teams(TEAM *teams, GAME *games)
{
	for (register int i = 0; i < AMOUNT_OF_GROUPS; i++) {
		printf("%c\n", groups[i]);

		for (TEAM *team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next)
			if (team_ptr->group == groups[i])
				printf("%s\n", team_ptr->name);
	}
}

int
main(int argc, char *argv[])
{
	bool quit;
	TEAM *teams;
	GAME *games;

	teams = (TEAM *) malloc(sizeof(TEAM));
	teams->next = NULL;

	games = (GAME *) malloc(sizeof(GAME));
	games->next = NULL;

	quit = false;
	do {
		char options[AMOUNT_OF_OPTIONS];
		char option;

		printf("1 → Register\n");
		options[0] = 'r';
		
		printf("6 → Show the teams\n");
		options[5] = 'p';

		printf("7 → Exit without saving changes\n");
		options[6] = 'w';

		printf("8 → Exit and save changes\n");
		options[7] = 'c';

		option = get_option(options, AMOUNT_OF_OPTIONS);

		switch (option) {
			case 'r':
				printf("Registering...\n");
				regist(teams, games);
				break;
			case 'e':
				printf("Editing...\n");
				break;
			case 'd':
				break;
			case 's':
				break;
			case 'n':
				break;
			case 'p':
				print_teams(teams, games);
				break;
			case 'w':
				break;
			case 'c':
				quit = true;
				break;
		}
	} while (!quit);

	/*
	for (GAME *p = games->next; p != NULL; p = p->next) {
		free(p->team_one);
		free(p->team_two);
	}*/

	/*for (TEAM *team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next)
		free(team_ptr->name);*/
	
	free(games);
	free(teams);

	return 0;
}
