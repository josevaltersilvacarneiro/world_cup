#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

extern char get_option(const char options[], unsigned int amount_of_options);
extern TEAM *regist_teams(TEAM *teams);
extern GAME *regist_games(TEAM *teams, GAME *games);

void
print_spaces(void)
{
	for (register int i = 0; i < AMOUNT_OF_SPACES; i++)
		printf("-");
	printf("\n");
}

void
regist(CUP *cup)
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
			cup->teams = regist_teams(cup->teams);
			break;
		case 'g':
			cup->games = regist_games(cup->teams, cup->games);
			break;
	}
}

void
print_teams(CUP *cup)
{
	for (register int i = 0; i < AMOUNT_OF_GROUPS; i++) {
		print_spaces();
		printf("%c\n", groups[i]);
		print_spaces();

		for (TEAM *team_ptr = cup->teams->next; team_ptr != NULL; team_ptr = team_ptr->next)
			if (team_ptr->group == groups[i])
				printf("%s\t%u\t%u\t%u\n", team_ptr->name, team_ptr->pt, team_ptr->gs, team_ptr->gc);
	}
	print_spaces();
}

int
main(int argc, char *argv[])
{
	bool quit;
	CUP cup;

	cup.teams = calloc(1, sizeof(TEAM));
	cup.teams->next = NULL;

	cup.games = calloc(1, sizeof(GAME));
	cup.games->next = NULL;

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
				regist(&cup);
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
				print_teams(&cup);
				break;
			case 'w':
				break;
			case 'c':
				quit = true;
				break;
		}
	} while (!quit);

	/*for (TEAM *team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next)
		free(team_ptr->name);*/
	
	free(cup.games);
	free(cup.teams);

	return 0;
}
