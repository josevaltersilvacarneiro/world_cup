#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.h"

#define AMOUNT_OF_OPTIONS 8
#define AMOUNT_OF_GROUPS  32

struct team {
	char *name;
	struct team *next;
};

typedef struct team TEAM;

struct group {
	char name;
	TEAM *teams;
};

typedef struct group GROUP;

struct game {
	TEAM *team_one;
	TEAM *team_two;
	struct game *next;
};

typedef struct game GAME;

void
regist(GROUP *cup[], GAME *games)
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
			break;
		case 'g':
			break;
	}
}

void
print_teams(GROUP *cup[], GAME *games)
{
	for (register int i = 0; i < AMOUNT_OF_GROUPS; i++) {
		printf("%c\n", cup[i]->name);
		for (TEAM *p = cup[i]->teams->next; p->next != NULL; p = p->next)
			printf("%s\n", p->name);
	}
}

int
main(int argc, char *argv[])
{
	bool  quit;
	GROUP *cup[AMOUNT_OF_GROUPS];
	GAME  *games;

	for (register int group = 0; group < AMOUNT_OF_GROUPS; group++) {
		cup[group]		= (GROUP *) malloc(sizeof(GROUP));
		cup[group]->teams	= (TEAM  *) malloc(sizeof(TEAM));
		cup[group]->teams->next = NULL;
	}

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
				regist(cup, games);
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
				break;
			case 'w':
				break;
			case 'c':
				quit = true;
				break;
		}
	} while (!quit);

	for (GAME *p = games->next; p != NULL; p = p->next) {
		free(p->team_one);
		free(p->team_two);
	}
	
	for (register int group = 0; group < AMOUNT_OF_GROUPS; group++) {
		for (TEAM *p = cup[group]->teams->next; p != NULL; p = p->next)
			free(p->name);
		free(cup[group]->teams);
		free(cup[group]);
	}
	
	free(games);

	return 0;
}
