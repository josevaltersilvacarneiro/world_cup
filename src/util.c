#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "util.h"

/* Conversion functions */

TEAM
*convert_to_team_ptr(const TEAM **first_team, const String team_name)
{
	/*
	 * This function receives two parameters: a linked list of
	 * TEAM structure and the team name. In the end, it
	 * returns a pointer to the structure that corres-
	 * ponds to the team name passed as argument.
	 */

	TEAM *team_ptr = *first_team;

	for (; team_ptr != NULL; team_ptr = team_ptr->next)
		if (!strcmp(team_name, team_ptr->name))
			return team_ptr;

	return NULL;
}

TEAM
*convert_to_before_team_ptr(TEAM **first_team, const String team_name)
{
	/* See convert_to_team_ptr */

	TEAM *team_ptr = *first_team;

	if (team_ptr == NULL) /* empty list */
		return NULL;
	else
		for (; team_ptr->next != NULL; team_ptr = team_ptr->next)
			if (!strcmp(team_name, team_ptr->next->name))
				return team_ptr;
	return NULL;
}

GAME
*find_game(GAME **first_game, const TEAM *team_one, const TEAM *team_two)
{
	/*
	 * This function receives three parameters: a linked list of
	 * GAME structure and two pointers to TEAM structure. In the
	 * end, it returns a pointer to the structure that corres-
	 * ponds to the team structures passed as arguments.
	 */

	for (GAME *game_ptr = *first_game; game_ptr != NULL; game_ptr = game_ptr->next)
		if (
			(game_ptr->team_one == team_one && game_ptr->team_two == team_two) ||
			(game_ptr->team_two == team_one && game_ptr->team_one == team_two)
		   )
			return game_ptr;

	return NULL;
}

GAME
*find_before_game(GAME **first_game, const TEAM *team_one, const TEAM *team_two)
{
	/* See find_game */

	if (*first_game == NULL) /* empty list */
		return NULL;
	else
		for (GAME *game_ptr = *first_game; game_ptr->next != NULL; game_ptr = game_ptr->next)
			if (
				(game_ptr->next->team_one == team_one && game_ptr->next->team_two == team_two) ||
				(game_ptr->next->team_two == team_one && game_ptr->next->team_one == team_two)
		   	)
				return game_ptr;

	return NULL;
}

bool
check(String message)
{
	/*
	 * This function waits for the user
	 * to type y or N for the question
	 * passed as argument and returns
	 * true (y) or false (any).
	 */

	String check;

	check = input(message);

	return *check == 'Y';
}
	
size_t
get_amount(String message)
{
	char *eptr;
	size_t amount;
	
	amount = strtoul(input(message), &eptr, 10);

	return amount;
}

char
get_option(const char options[], unsigned int amount_of_options)
{
	char *eptr;
	unsigned int option;

	do {
		option = strtoul(input("Type your option: "), &eptr, 10);

		option--;

	} while (!(option < amount_of_options) || !options[option]);

	return options[option];
}

char
get_group(char groups[])
{
	String group;
	bool found;

	do {
		found = false;
		
		group = input("Type a group: ");

		for (register int i = 0; i < AMOUNT_OF_GROUPS; i++)
			if (*group == groups[i]) {
				found = true;
				break;
			}
	} while (!found);

	return *group;
}

String
get_team(const TEAM **first_team, bool is_in)
{
	String team;
	TEAM  *team_ptr;

	for (;;) {
		team = is_in ? input("Type a registered team: ") : input("Type a team: ");

		for (team_ptr = *first_team; team_ptr != NULL; team_ptr = team_ptr->next) {
			if (!strcmp(team_ptr->name, team)) {
				if(is_in)
					return team;
				else
					break;
			}
		}

		if (!is_in && team_ptr == NULL)
			return team; /* The caller function requires a team that hasn't added yet and 
					the team typed hasn't added yet */

		is_in ? puts("The team typed hasn't added yet") : puts("The team typed has already been added");
	}
}

size_t
get_date()
{
	return 0;
}

String
get_place(void)
{
	String place = input("Place: ");

	/* Converting to uppercase */

	for (register int i = 0; i < strlen(place); i++)
		place[i] = toupper(place[i]);

	return place;
}

size_t
maximum_amount_of_registered_games_group(const TEAM **first_team, char group)
{
	/* Fundamental Counting Theorem */

	size_t num_of_regist_teams = get_amount_of_registered_teams(first_team, group);

	return num_of_regist_teams * (num_of_regist_teams - 1) / 2;
}

size_t
maximum_amount_of_registered_games(const TEAM **first_team, char groups[])
{
	/*
	 * Using a repetiton loop, all groups looped.
	 * By means of the Fundamental Counting Theo-
	 * rem, the number of possible matches in
	 * each group is found and then added to the
	 * accumulator variable called 'max_amount_-
	 * of_registered_games'. At the end, it's
	 * returned.
	 */

	size_t max_amount_of_registered_games = 0;

	for (register int i = 0; i < AMOUNT_OF_GROUPS; i++)
		max_amount_of_registered_games += maximum_amount_of_registered_games_group(first_team, groups[i]);

	return max_amount_of_registered_games;
}

size_t
get_amount_of_registered_teams(const TEAM **first_team, char group)
{
	size_t amount_of_registered_teams = 0;

	for (
			TEAM *team_ptr = *first_team;
			team_ptr != NULL && amount_of_registered_teams < AMOUNT_OF_TEAMS_PER_GROUP;
			team_ptr = team_ptr->next
	    )
		if (team_ptr->group == group)
			amount_of_registered_teams++;

	return amount_of_registered_teams;
}

size_t
get_amount_of_registered_games(GAME **first_game, char group)
{
	size_t amount_of_registered_games = 0;

	for (GAME *game_ptr = *first_game; game_ptr != NULL; game_ptr = game_ptr->next)
		if (game_ptr->team_one->group == group)
			amount_of_registered_games++;

	return amount_of_registered_games;
}

size_t
number_of_teams_registered(TEAM **first_team)
{
	size_t num_of_teams_registered = 0;

	for (
		TEAM *team_ptr = *first_team;
		team_ptr != NULL;
		team_ptr = team_ptr->next, num_of_teams_registered++
	    ) ;

	return num_of_teams_registered;
}

size_t
number_of_games_registered(GAME **first_game)
{
	size_t num_of_games_registered = 0;

	for (
		GAME *game_ptr = *first_game;
		game_ptr != NULL;
		game_ptr = game_ptr->next, num_of_games_registered++
	    ) ;

	return num_of_games_registered;
}

size_t
number_of_teams_to_register(TEAM **first_team)
{
	/*
	 * The number of teams that can be added is
	 * equal to the number of groups times the
	 * number of teams per group minus the num-
	 * ber of teams that was already added.
	 */

	return AMOUNT_OF_GROUPS * AMOUNT_OF_TEAMS_PER_GROUP - number_of_teams_registered(first_team);
}

size_t
number_of_games_to_register(const TEAM **first_team, GAME **first_game, char groups[])
{
	/*
	 * The amount of games that can be added is
	 * equal to the maximum amount that can be
	 * registered minus the amount that was
	 * already added.
	 */

	return maximum_amount_of_registered_games(first_team, groups) - number_of_games_registered(first_game);
}

bool
are_all_teams_registered(TEAM **first_team)
{
	return number_of_teams_registered(first_team) == AMOUNT_OF_GROUPS * AMOUNT_OF_TEAMS_PER_GROUP;
}

bool
are_all_games_registered(TEAM **first_team, GAME **first_game, char groups[])
{
	/*
	 * If the amount of games registered is less than
	 * the maximum amount, then all game aren't added
	 */

	return number_of_games_registered(first_game) == maximum_amount_of_registered_games(first_team, groups);
}

bool
is_every_registered(TEAM **first_team, GAME **first_game, char groups[])
{
	return
		are_all_teams_registered(first_team) &&
		are_all_games_registered(first_team, first_game, groups);
}

bool
is_any_game_registered(GAME **first_game)
{
	return *first_game != NULL;
}

bool
is_any_team_registered(TEAM *first_team)
{
	return *first_team != NULL;
}
