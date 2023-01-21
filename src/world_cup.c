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

		options[5] = 'p';
		options[6] = 'w';
		options[7] = 'c';

		printf("1 → Register\n");
		options[0] = 'r';

		option = get_option(options, AMOUNT_OF_OPTIONS);

		switch (option) {
			case 'r':
				printf("Registering...\n");
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
		free(cup[group]);
	}
	
	free(games);

	return 0;
}
