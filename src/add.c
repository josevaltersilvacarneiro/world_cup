#ifndef config_h
#include "config.h"
#endif

/* See util.c */

extern TEAM *convert(const TEAM *teams, const String team_name);

extern size_t number_of_teams_registered(TEAM *teams);
extern size_t number_of_games_registered(GAME *games);

void
add_team(
		TEAM *teams,
		const char group,
		const String team,
		const unsigned int pt,
		const unsigned int gs,
		const unsigned int gc,
		const int gd
	)
{
	TEAM *_teams = teams; /* backup */
	TEAM *last_team;

	/* Adding a new team */

	teams = realloc(
				teams,
				(number_of_teams_registered(teams) + 2) * sizeof(TEAM)
		       );

	if (!teams)
		return _teams; /* There wasn't enough memory */

        for (last_team = teams; last_team->next != NULL; last_team = last_team->next) ;

        last_team->next = last_team + 1;
        last_team++;

        last_team->group = group;
        last_team->name  = team;
        last_team->pt    = pt;
        last_team->gs    = gs;
        last_team->gc    = gc;
	last_team->gd    = gd;
	
	last_team->next  = NULL;
}

void
add_game(
		const TEAM *teams,
		GAME *games,
		const String first_team_name,
		const String second_team_name,
		const unsigned short team_one_goals,
		const unsigned short team_two_goals,
		const unsigned int date
	)
{
	GAME *_games = games; /* backup */
	TEAM *team_one;
	TEAM *team_two;
	GAME *last_game;

	team_one = convert(teams, first_team_name);
	team_two = convert(teams, second_team_name);

	/* Add the match to the corresponding group */

	games = realloc(
				games,
				(number_of_games_registered(games) + 2) * sizeof(GAME)
			);

	if (!games)
		return _games; /* There wasn't enough memory */

        for (last_game = games->next; last_game->next != NULL; last_game = last_game->next) ;

        last_game->next = last_game + 1;
        last_game++;

        last_game->team_one = team_one;
        last_game->team_two = team_two;
        last_game->team_one_goals = team_one_goals;
        last_game->team_two_goals = team_two_goals;
        last_game->date = date;
}
