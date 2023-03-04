#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef config_h
#include "config.h"
#endif

extern char   groups[];

extern TEAM  *convert_to_team_ptr(const TEAM **first_team, const String team_name);

extern char   get_group(char groups[]);
extern String get_team(const TEAM **first_team, bool is_in);
extern size_t get_date();
extern String get_place();

extern TEAM  *add_team(
			TEAM **first_team,
			const char group,
			const String team,
			const unsigned int pt,
			const unsigned int gs,
			const unsigned int gc,
			const unsigned int gd
		    );

extern GAME  *add_game(
			const TEAM **first_team,
			GAME **first_game,
			TEAM *team_one,
			TEAM *team_two,
			const unsigned short team_one_goals,
			const unsigned short team_two_goals,
			const unsigned int date,
			String place
		    );

extern size_t get_amount_of_registered_teams(TEAM **first_team, char group);
extern size_t number_of_teams_registered(TEAM **first_team);
extern size_t number_of_teams_to_register(TEAM **first_team);

extern size_t get_amount_of_registered_games(GAME **first_game, char group);
extern size_t number_of_games_registered(GAME **first_game);
extern size_t number_of_games_to_register(const TEAM **first_team, GAME **first_game, char groups[]);
extern size_t maximum_amount_of_registered_games_group(const TEAM **first_team, char group);

extern size_t get_amount(const char *message);

TEAM
*regist_team(TEAM **first_team)
{
	char group;
	String team;

	group = get_group(groups);
	while (get_amount_of_registered_teams(first_team, group) > 3) {
		printf("The group %c is already complete\n", group);
		group = get_group(groups);
	}

	team = get_team(first_team, false);
	return add_team(first_team, group, team, 0, 0, 0, 0); /* See add.c */
}

GAME
*regist_game(const TEAM **first_team, GAME **first_game)
{
	size_t maximum_amount_of_games;
	
	TEAM *team_one;
	TEAM *team_two;
	unsigned short team_one_goals, team_two_goals;
	size_t date;
	String place;

	GAME *last_game;

	rg_game:
		team_one = convert_to_team_ptr(first_team, get_team(first_team, true));
		
		for (;;) {
			maximum_amount_of_games = maximum_amount_of_registered_games_group(
					first_team, team_one->group
				);

			/* ↓ Fundamental Counting Theorem ↓ */
			if (maximum_amount_of_games == AMOUNT_OF_TEAMS_PER_GROUP * (AMOUNT_OF_TEAMS_PER_GROUP - 1) / 2)
				puts("All games in this group already were registered");
			else if (maximum_amount_of_games == get_amount_of_registered_games(first_game, team_one->group))
				puts("To register more games in this group, add more teams");
			else
				break;
		}
	
	team_two = convert_to_team_ptr(first_team, get_team(first_team, true));

	if (team_one->group != team_two->group) {
		printf("%s isn't in group %c\n", team_one->name, team_two->group);
		goto rg_game;
	}

	team_one_goals = get_amount("Number of goals for first team: ");
	team_two_goals = get_amount("Number of goals for second team: ");
	date = get_date();
	place = get_place();

	return add_game(
			first_team,
			first_game,
			team_one,
			team_two,
			team_one_goals,
			team_two_goals,
			date,
			place
		); /* See add.c */
}

TEAM
*regist_teams(TEAM **first_team)
{
	unsigned int max_amount, amount_of_teams;
	
	max_amount = number_of_teams_to_register(first_team);

	amount_of_teams = get_amount("Number of teams: ");
	while (amount_of_teams > max_amount) {
		printf("Only %u teams left to register\n", max_amount);
		amount_of_teams = get_amount("Number of teams: ");
	}
	
	if (amount_of_teams <= 0)
		return *first_team;  /* The user gave up on registering more teams */

	while (amount_of_teams-- > 0)
		*first_team = regist_team(first_team);

	return *first_team;
}

GAME
*regist_games(const TEAM **first_team, GAME **first_game)
{
	size_t max_amount, amount_of_games;

	max_amount = number_of_games_to_register(first_team, first_game, groups);

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
		return *first_game;  /* The user gave up on registering more games */

	while (amount_of_games-- > 0)
		*first_game = regist_game(first_team, first_game);

	return *first_game;
}
