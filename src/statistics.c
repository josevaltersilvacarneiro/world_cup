/*
 * The functions of this file are responsible
 * for returning the statistical data.
 */

#include <stddef.h>

#ifndef config_h
#include "config.h"
#endif

float
group_goal_average(GAME **first_game, char group)
{
	/* Reference */
	/* https://pt.wikipedia.org/wiki/M%C3%A9dia_aritm%C3%A9tica */

	size_t num_of_goals, num_of_games;

	num_of_goals = 0;
	num_of_games = 0;

	for (GAME *game_ptr = *first_game; game_ptr != NULL; game_ptr = game_ptr->next) {
		num_of_goals += game_ptr->team_one_goals + game_ptr->team_two_goals;
		num_of_games++;
	}

	/* ZeroDivisionError */

	return (num_of_games == 0) ? num_of_games : num_of_goals / num_of_games;
}

float
goal_average(GAME **first_game)
{
	/*
	 * This function returns the average
	 * number of goals in the World Cup
	 */

	size_t num_of_goals, num_of_games;

	/*
	 * Loop all groups and add the number of goals to the
	 * corresponding accumulator variable. Idem for the
	 * num of matches.
	 */

	num_of_goals = 0;
	num_of_games = 0;

	for (GAME *game_ptr = *first_game; game_ptr != NULL; game_ptr = game_ptr->next) {
		num_of_goals += game_ptr->team_one_goals + game_ptr->team_two_goals;
		num_of_games++;
	}

	/* ZeroDivisionError */

	return num_of_games == 0 ? 0 : num_of_goals / num_of_games;
} 

GAME
*most_goals_in_a_game(GAME **first_game)
{
	GAME *game = *first_game;

	for (GAME *game_ptr = game; game_ptr != NULL; game_ptr = game_ptr->next)
		if (
			(game_ptr->team_one_goals > game->team_one_goals &&
			 game_ptr->team_one_goals > game->team_two_goals) ||
			(game_ptr->team_two_goals > game->team_one_goals &&
			 game_ptr->team_two_goals > game->team_two_goals)
		   ) game = game_ptr;

	return game;
}
