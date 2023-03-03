#include <stdlib.h>

#ifndef config_h
#include "config.h"
#endif

extern void register_game(GAME *game); /* See rank.c */

TEAM
*add_team(
		TEAM *teams,
		const char group,
		const String team,
		const unsigned int pt,
		const unsigned int gs,
		const unsigned int gc,
		const int gd
	)
{
	TEAM *last_team;
	TEAM *new_team;

	/* Adding a new team */

	new_team = calloc(1, sizeof(TEAM));

	if (!new_team)
		return teams; /* There wasn't enough memory */

        new_team->group = group;
        new_team->name  = team;
        new_team->pt    = pt;
        new_team->gs    = gs;
        new_team->gc    = gc;
	new_team->gd    = gd;
	
	new_team->next  = NULL;

        for (last_team = teams; last_team->next != NULL; last_team = last_team->next) ;

        last_team->next = new_team;

	return teams;
}

GAME
*add_game(
		const TEAM *teams,
		GAME *games,
		TEAM *team_one,
		TEAM *team_two,
		const unsigned short team_one_goals,
		const unsigned short team_two_goals,
		const unsigned int date,
		const String place
	)
{
	GAME *last_game;
	GAME *new_game;

	/* Add the match to the corresponding group */

	new_game = calloc(1, sizeof(GAME));

	if (!new_game)
		return games; /* There wasn't enough memory */

        new_game->team_one	  = team_one;
        new_game->team_two	  = team_two;
        new_game->team_one_goals  = team_one_goals;
        new_game->team_two_goals  = team_two_goals;
        new_game->date		  = date;
	new_game->place		  = place;

	new_game->next		  = NULL;

        for (last_game = games; last_game->next != NULL; last_game = last_game->next) ;

        last_game->next = new_game;

	register_game(new_game); /* This doens't allocate memory; only calculates the rank */

	return games;
}
