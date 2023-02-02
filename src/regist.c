#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef config_h
#include "config.h"
#endif

extern char groups[];

extern size_t fact(size_t number);

extern char get_group(char groups[]);
extern String get_team(const TEAM *teams, bool is_in);
extern size_t get_date();

extern size_t get_amount_of_registered_teams(TEAM *teams, char group);
extern size_t number_of_teams_registered(TEAM *teams);
extern size_t number_of_teams_to_register(TEAM *teams);

extern size_t get_amount_of_registered_games(GAME *games, char group);
extern size_t number_of_games_registered(GAME *games);
extern size_t number_of_games_to_register(const TEAM *teams, GAME *games, char groups[]);
extern size_t maximum_amount_of_registered_games_group(const TEAM *teams, char group);

extern size_t get_amount(const char *message);

TEAM
*convert(const TEAM *teams, String team_name)
{
	TEAM *team_ptr;

	for (team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next)
		if (!strcmp(team_name, team_ptr->name))
			return team_ptr;
	
	return team_ptr;
}

void
regist_team(TEAM *teams)
{
	char group;
	String team;
	TEAM *last_team;

	group = get_group(groups);
	while (get_amount_of_registered_teams(teams, group) > 3) {
		printf("The group %c is already complete\n", group);
		group = get_group(groups);
	}

	team = get_team(teams, false);

	/* Adding a new team */

	for (last_team = teams; last_team->next != NULL; last_team = last_team->next) ;

	last_team->next = last_team + 1;
	last_team++;

	last_team->group = group;
	last_team->name  = team;
	last_team->pt	 = 0;
	last_team->gs	 = 0;
	last_team->gc	 = 0;
	last_team->gd	 = 0;
	last_team->next  = NULL;
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
		team_one = convert(teams, get_team(teams, true));
		
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
	
	team_two = convert(teams, get_team(teams, true));

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
	
	if (amount_of_teams <= 0)
		return teams;  /* The user gave up on registering more teams */

	teams = realloc(
				teams,
				(amount_of_teams + number_of_teams_registered(teams) + 1) * sizeof(TEAM)
		       );	/* See the main function in world_cup.c */

	if (!teams)
		return _teams; /* There wasn't enough memory */

	while (amount_of_teams-- > 0)
		regist_team(teams);

	return teams;
}

GAME
*regist_games(const TEAM *teams, GAME *games)
{
	size_t max_amount, amount_of_games;
	GAME *_games = games;

	max_amount = number_of_games_to_register(teams, games, groups);

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

	games = realloc(
				games,
				(amount_of_games + number_of_games_registered(games) + 1) * sizeof(GAME)
		       );

	if (!games)
		return _games; /* There wasn't enough memory */

	while (amount_of_games-- > 0)
		regist_game(teams, games);
}
