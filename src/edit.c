#include <stdio.h>

#ifndef config_h
#include "config.h"
#endif

void edit_team(TEAM *first_team);
void edit_game(TEAM *first_team, GAME *first_game);

void
edit_team(TEAM *first_team)
{
	printf("Editing team\n");
}

void
edit_game(TEAM *first_team, GAME *first_game)
{
	printf("Editing game\n");
}
