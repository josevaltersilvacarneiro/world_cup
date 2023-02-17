#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef config_h
#include "config.h"
#endif

extern char   groups[];

extern TEAM  *convert_to_team_ptr(const TEAM *teams, const String team_name);

extern char   get_group(char groups[]);
extern String get_team(const TEAM *teams, bool is_in);
extern size_t get_date();
extern String get_place();

extern TEAM  *add_team(
			TEAM *teams,
			const char group,
			const String team,
			const unsigned int pt,
			const unsigned int gs,
			const unsigned int gc,
			const unsigned int gd
		    );

extern GAME  *add_game(
			const TEAM *teams,
			GAME *games,
			TEAM *team_one,
			TEAM *team_two,
			const unsigned short team_one_goals,
			const unsigned short team_two_goals,
			const unsigned int date,
			String place
		    );

extern size_t get_amount_of_registered_teams(TEAM *teams, char group);
extern size_t number_of_teams_registered(TEAM *teams);
extern size_t number_of_teams_to_register(TEAM *teams);

extern size_t get_amount_of_registered_games(GAME *games, char group);
extern size_t number_of_games_registered(GAME *games);
extern size_t number_of_games_to_register(const TEAM *teams, GAME *games, char groups[]);
extern size_t maximum_amount_of_registered_games_group(const TEAM *teams, char group);

extern size_t get_amount(const char *message);

TEAM
*regist_team(TEAM *teams)
{
	char group;
	String team;

	group = get_group(groups);
	while (get_amount_of_registered_teams(teams, group) > 3) {
		printf("The group %c is already complete\n", group);
		group = get_group(groups);
	}

	team = get_team(teams, false);
	return add_team(teams, group, team, 0, 0, 0, 0); /* See add.c */
}

GAME
*regist_game(const TEAM *teams, GAME *games)
{
	size_t maximum_amount_of_games;
	
	TEAM *team_one;
	TEAM *team_two;
	unsigned short team_one_goals, team_two_goals;
	size_t date;
	String place;

	GAME *last_game;

	rg_game:
		team_one = convert_to_team_ptr(teams, get_team(teams, true));
		
		for (;;) {
			maximum_amount_of_games = maximum_amount_of_registered_games_group(teams, team_one->group);

			/* ↓ Fundamental Counting Theorem ↓ */
			if (maximum_amount_of_games == AMOUNT_OF_TEAMS_PER_GROUP * (AMOUNT_OF_TEAMS_PER_GROUP - 1) / 2)
				puts("All games in this group already were registered");
			else if (maximum_amount_of_games == get_amount_of_registered_games(games, team_one->group))
				puts("To register more games in this group, add more teams");
			else
				break;
		}
	
	team_two = convert_to_team_ptr(teams, get_team(teams, true));

	if (team_one->group != team_two->group) {
		printf("%s isn't in group %c\n", team_one->name, team_two->group);
		goto rg_game;
	}

	team_one_goals = get_amount("Number of goals for first team: ");
	team_two_goals = get_amount("Number of goals for second team: ");
	date = get_date();
	place = get_place();

	return add_game(
			teams,
			games,
			team_one,
			team_two,
			team_one_goals,
			team_two_goals,
			date,
			place
		); /* See add.c */
}

TEAM
*regist_teams(TEAM *teams)
{
	unsigned int max_amount, amount_of_teams;
	
	max_amount = number_of_teams_to_register(teams);

	amount_of_teams = get_amount("Number of teams: ");
	while (amount_of_teams > max_amount) {
		printf("Only %u teams left to register\n", max_amount);
		amount_of_teams = get_amount("Number of teams: ");
	}
	
	if (amount_of_teams <= 0)
		return teams;  /* The user gave up on registering more teams */

	while (amount_of_teams-- > 0)
		teams = regist_team(teams);

	return teams;
}

GAME
*regist_games(const TEAM *teams, GAME *games)
{
	size_t max_amount, amount_of_games;

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

	while (amount_of_games-- > 0)
		games = regist_game(teams, games);

	return games;
}
