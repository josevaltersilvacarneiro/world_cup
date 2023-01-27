#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef config_h
#include "config.h"
#endif

extern char groups[];

extern size_t fact(size_t number);

extern char get_group(char groups[]);
extern TEAM *get_team(const TEAM *teams);
extern size_t get_date();
extern char *add_new_team(TEAM *teams, char group);

extern unsigned int get_amount_of_registered_teams(TEAM *teams, char group);
extern unsigned int number_of_teams_to_register(TEAM *teams);

extern size_t get_amount_of_registered_games(GAME *games, char group);
extern size_t number_of_games_to_register(TEAM *teams, GAME *games, char groups[]);
extern size_t maximum_amount_of_registered_games_group(const TEAM *teams, char group);

extern unsigned int get_amount(const char *message);

void
regist_team(TEAM *teams)
{
	char group;

	group = get_group(groups);
	while (get_amount_of_registered_teams(teams, group) > 3) {
		printf("The group %c is already complete\n", group);
		group = get_group(groups);
	}

	add_new_team(teams, group);
}

GAME
*regist_game(const TEAM *teams, GAME *games)
{
	size_t maximum_amount_of_games;
	
	TEAM *team_one, *team_two;
	unsigned short number_of_goals_team_one, number_of_goals_team_two;
	size_t date;

	GAME *last_game;

	rg_game:
		team_one = get_team(teams);
		
		for (;;) {
			maximum_amount_of_games = maximum_amount_of_registered_games_group(teams, team_one->group);

			/* ↓ Fundamental Counting Theorem ↓ */
			if (maximum_amount_of_games == fact(AMOUNT_OF_TEAMS_PER_GROUP - 1))
				puts("All games in this group already were registered");
			else if (maximum_amount_of_games == get_amount_of_registered_games(games, team_one->group))
				puts("To register more games in this group, add more teams");
			else
				break;
		}
	
	team_two = get_team(teams);

	if (team_one->group != team_two->group) {
		printf("%s isn't in group %c\n", team_one->name, team_two->group);
		goto rg_game;
	}

	number_of_goals_team_one = get_amount("Number of goals for first team: ");
	number_of_goals_team_two = get_amount("Number of goals for second team: ");
	date = get_date();

	/* Add the match to the corresponding group */

	for (last_game = games->next; last_game->next != NULL; last_game = last_game->next) ;

	last_game->next = last_game + 1;
	last_game++;

	last_game->team_one = team_one;
	last_game->team_two = team_two;
	last_game->team_one_goals = number_of_goals_team_one;
	last_game->team_two_goals = number_of_goals_team_two;
	last_game->date = date;
	last_game->next = NULL;

	return games;
}

TEAM
*regist_teams(TEAM *teams)
{
	unsigned int max_amount, amount_of_teams;
	TEAM *_teams = teams;
	
	max_amount = number_of_teams_to_register(teams);

	amount_of_teams = get_amount("Number of teams: ");
	while (amount_of_teams > max_amount) {
		printf("Only %u teams left to register\n", max_amount);
		amount_of_teams = get_amount("Number of teams: ");
	}
	
	teams = realloc(teams, amount_of_teams * sizeof(TEAM)); /* See the main function in world_cup.c */

	if (!teams) {
		printf("There was an error\n");
		return _teams; /* There wasn't enough memory */
	} else
		_teams = teams;

	while (amount_of_teams-- > 0)
		regist_team(teams);

	return teams;
}

GAME
*regist_games(TEAM *teams, GAME *games)
{
	size_t max_amount, amount_of_games;
	GAME *_games = games;

	max_amount = number_of_games_to_register(games);

	/*
	 * As long as amount of games typed by the user is higher
	 * than the maximum missing quantity, run; else break
	 */

	amount_of_games = get_amount("Number of games: ");
	while (amount_of_games > max_amount) {
		printf("Only %u games left to register", max_amount);
		amount_of_games = get_amount("Number of games: ");
	}

	if (amount_of_games <= 0)
		return games;  /* The user gave up on registering more games */

	games = realloc(games, amount_of_games * sizeof(GAME));

	if (!games)
		return _games; /* There wasn't enough memory */

	while (amount_of_games-- > 0)
		regist_game(teams, games);
}
