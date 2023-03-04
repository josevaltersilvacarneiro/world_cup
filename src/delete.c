#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef config_h
#include "config.h"
#endif /* config_h */

extern TEAM  *convert_to_team_ptr(TEAM **first_team, const String team_name);
extern TEAM  *convert_to_before_team_ptr(TEAM **first_team, const String team_name);

extern GAME  *find_before_game(GAME **first_game, const TEAM *team_one, const TEAM *team_two);

extern String get_team(TEAM **first_team, bool is_in);

extern void   unscramble_game(GAME *game); /* See rank.c */

static void
real_delete_game(GAME *before_game)
{
	GAME *game = before_game->next;

	unscramble_game(game);

	/* If this game isn't the last, it receives the next game; else NULL */
	before_game->next = (game->next != NULL) ? game->next : NULL;

	free(game);
}

void
delete_team(TEAM **first_team, GAME **first_game)
{
	TEAM *before_team;
	TEAM *team;

	before_team = convert_to_before_team_ptr(first_team, get_team(first_team, true));

	if (before_team != NULL) {
		team = before_team->next;

		if ((*first_game) != NULL) {
			GAME *before_game = NULL;

			for (GAME *game_ptr = *first_game; game_ptr->next != NULL; game_ptr = game_ptr->next) {
				if (game_ptr->team_one == team || game_ptr->team_two == team) {
					if (before_game == NULL) {
						unscramble_game(game_ptr);
						
						free(*first_game);
						*first_game = NULL;
					} else
						real_delete_game(before_game); /* before */
				}
				before_game = game_ptr;
			} /* end of the for loop */
		}

		/* This team isn't last */
		before_team->next = (team->next != NULL) ? team->next : NULL;
	
		free(team);
	} else { /* The team is exactly the head of the list */
		free(*first_team);
		*first_team = NULL;
	}
}

void
delete_game(TEAM **first_team, GAME **first_game)
{
	TEAM *team_one;
	TEAM *team_two;
	GAME *before_game;

	del_gam:
		do {
			team_one = convert_to_team_ptr(first_team, get_team(first_team, true));
			team_two = convert_to_team_ptr(first_team, get_team(first_team, true));
		} while (team_one == team_two || team_one->group != team_two->group);

		before_game = find_before_game(first_game, team_one, team_two);
	
	if (before_game == NULL) { /* There are two possibilities */
		if (
			(*first_game)->team_one == team_one ||
			(*first_game)->team_two == team_one
		   ) {		  /* 1 - The game is the head of the list */
			GAME *old_first_game = *first_game;

			unscramble_game(*first_game);

			*first_game = (*first_game)->next;
			free(old_first_game);
		} else {	  /* 2 - The game hasn't been registered yet */
			puts("Invalid entry");
			goto del_gam;
		}
	} else {
		real_delete_game(before_game);
	}
}
