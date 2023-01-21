#include <stdio.h>
#include <stdlib.h>

struct team {
	char *name;
	struct team *next;
};

typedef struct team TEAM;

struct game {
	TEAM *team_one;
	TEAM *team_two;
};

typedef struct game GAME;

int
main(int argc, char *argv[])
{
	int amount_of_teams;
	TEAM *teams;

	teams = malloc(sizeof(TEAM));
	teams->name = (char *) malloc(sizeof(char) * 40);

	printf("Enter amount of teams: ");
	scanf("%d", &amount_of_teams);

	for (register int i = 0; i < amount_of_teams; i++) {
		teams = realloc(teams, sizeof(TEAM));
		(teams + i + 1)->name = malloc(sizeof(char) * 40);

		scanf("%s", (teams + i + 1)->name);
		(teams + i)->next = (teams + i + 1);
	}
	(teams + amount_of_teams)->next = NULL;

	for (TEAM *p = teams->next; p != NULL; p = p->next) {
		printf("%p\tTeam: %s\n", p, p->name);
		free(p->name);
	}
	free(teams);
	return 0;
}
