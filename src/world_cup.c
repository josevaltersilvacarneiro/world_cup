#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

extern void start_string();
extern void destroy_string();

extern CUP *get_data(void);
extern void push_data(CUP *cup);

extern char get_option(const char options[], unsigned int amount_of_options);
extern bool are_all_teams_registered(TEAM *teams);
extern bool are_all_games_registered(TEAM *teams, GAME *games, char groups[]);

extern TEAM *regist_teams(TEAM *teams);
extern GAME *regist_games(const TEAM *teams, GAME *games);

extern void sort_classification(TEAM *first_team);

void
print_hyphens(void)
{
	for (register int i = 0; i < AMOUNT_OF_SPACES; i++)
		printf("-");
	printf("\n");
}

void
print_spaces(size_t amount)
{
	for (register int i = amount; i != 0; i--)
		printf(" ");
}

void
regist(CUP *cup)
{
	char options[2];
	char option;

	if (!are_all_teams_registered(cup->teams)) {
		printf("1 → Register teams\n");
		options[0] = 't';
	}

	if (!are_all_games_registered(cup->teams, cup->games, groups)) {
		printf("2 → Register games\n");
		options[1] = 'g';
	}

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
	sort_classification(cup->teams);

	for (register int i = 0; i < AMOUNT_OF_GROUPS; i++) {
		print_hyphens();
		printf("%15c\n", groups[i]);
		print_hyphens();

		printf("NAME%20sGDGSGC\n", "PT");

		for (TEAM *team_ptr = cup->teams->next; team_ptr != NULL; team_ptr = team_ptr->next)
			if (team_ptr->group == groups[i]) {
				printf("%s", team_ptr->name);

				print_spaces(22 - strlen(team_ptr->name));
				
				printf("%2u%2u%2u%2u\n",
				      team_ptr->pt,
				      team_ptr->gd,
				      team_ptr->gs,
				      team_ptr->gc);
			}
	}
	print_hyphens();
}

int
main(int argc, char *argv[])
{
	bool quit;
	CUP *cup;

	start_string();

	cup = get_data();

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
				regist(cup);
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
				print_teams(cup);
				break;
			case 'w':
				break;
			case 'c':
				quit = true;
				break;
		}
	} while (!quit);

	push_data(cup);

	destroy_string();

	return 0;
}
