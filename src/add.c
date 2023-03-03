#include <stdlib.h>

#ifndef config_h
#include "config.h"
#endif

extern void register_game(GAME *game); /* See rank.c */

TEAM
*add_team(
		TEAM **first_team,     /* See main.c */
		const  char group,
		const  String team,
		const  unsigned int pt,
		const  unsigned int gs,
		const  unsigned int gc,
		const  int gd
	)
{
	TEAM *last_team;
	TEAM *new_team;

	/* Adding a new team */

	new_team = calloc(1, sizeof(TEAM));

	if (!new_team)
		return *first_team; /* There wasn't enough memory */

        new_team->group = group;
        new_team->name  = team;
        new_team->pt    = pt;
        new_team->gs    = gs;
        new_team->gc    = gc;
	new_team->gd    = gd;
	
	new_team->next  = NULL;

	if (*first_team == NULL)
		*first_team = new_team;
	else {
        	for (last_team = *first_team; last_team->next != NULL; last_team = last_team->next) ;
        	last_team->next = new_team;
	}

	return *first_team;
}

GAME
*add_game(
		const  TEAM **first_team,
		GAME **first_game, /* See main.c */
		TEAM  *team_one,
		TEAM  *team_two,
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
		return *first_game; /* There wasn't enough memory */

        new_game->team_one	  = team_one;
        new_game->team_two	  = team_two;
        new_game->team_one_goals  = team_one_goals;
        new_game->team_two_goals  = team_two_goals;
        new_game->date		  = date;
	new_game->place		  = place;

	new_game->next		  = NULL;

	if (*first_game == NULL)
		*first_game = new_game;
	else {
        	for (last_game = *first_game; last_game->next != NULL; last_game = last_game->next) ;
        	last_game->next = new_game;
	}

	register_game(new_game); /* This doens't allocate memory; only calculates the rank */

	return *first_game;
}
