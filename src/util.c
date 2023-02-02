#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

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

char
get_group_with_registered_teams(TEAM *teams, char groups[])
{
	char group;

	for (;;) {
		group = get_group(groups);

		if (get_amount_of_registered_teams(teams, group) > 1)
			return group;
	}
}

String
get_team(const TEAM *teams, bool is_in)
{
	String team;
	TEAM  *team_ptr;

	for (;;) {
		team = is_in ? input("Type a registered team: ") : input("Type a team: ");

		for (team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next) {
			if (!strcmp(team_ptr->name, team)) {
				if(is_in)
					return team;
				else
					break;
			}
		}

		if (team_ptr == NULL)
			return team;

		is_in ? puts("The team typed hasn't added yet") : puts("The team typed has already been added");
	}
}

size_t
get_date()
{
	return 0;
}

size_t
maximum_amount_of_registered_games_group(const TEAM *teams, char group)
{
	/* Fundamental Counting Theorem */

	size_t num_of_regist_teams = get_amount_of_registered_teams(teams, group);

	return num_of_regist_teams * (num_of_regist_teams - 1) / 2;
}

size_t
maximum_amount_of_registered_games(const TEAM *teams, char groups[])
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
		max_amount_of_registered_games += maximum_amount_of_registered_games_group(teams, groups[i]);

	return max_amount_of_registered_games;
}

size_t
get_amount_of_registered_teams(const TEAM *teams, char group)
{
	size_t amount_of_registered_teams = 0;

	for (
			TEAM *team_ptr = teams->next;
			team_ptr != NULL && amount_of_registered_teams < AMOUNT_OF_TEAMS_PER_GROUP;
			team_ptr = team_ptr->next
	    )
		if (team_ptr->group == group)
			amount_of_registered_teams++;

	return amount_of_registered_teams;
}

size_t
get_amount_of_registered_games(GAME *games, char group)
{
	size_t amount_of_registered_games;

	for (GAME *game_ptr = games->next; game_ptr != NULL; game_ptr = game_ptr->next)
		if (game_ptr->team_one->group == group)
			amount_of_registered_games++;

	return amount_of_registered_games;
}

size_t
number_of_teams_registered(TEAM *teams)
{
	size_t num_of_teams_registered = 0;

	for (
		TEAM *team_ptr = teams->next;
		team_ptr != NULL;
		team_ptr = team_ptr->next, num_of_teams_registered++
	    ) ;

	return num_of_teams_registered;
}

size_t
number_of_games_registered(GAME *games)
{
	size_t num_of_games_registered = 0;

	for (
		GAME *game_ptr = games->next;
		game_ptr != NULL;
		game_ptr = game_ptr->next, num_of_games_registered++
	    ) ;

	return num_of_games_registered;
}

size_t
number_of_teams_to_register(TEAM *teams)
{
	/*
	 * The number of teams that can be added is
	 * equal to the number of groups times the
	 * number of teams per group minus the num-
	 * ber of teams that was already added.
	 */

	return AMOUNT_OF_GROUPS * AMOUNT_OF_TEAMS_PER_GROUP - number_of_teams_registered(teams);
}

size_t
number_of_games_to_register(const TEAM *teams, GAME *games, char groups[])
{
	/*
	 * The amount of games that can be added is
	 * equal to the maximum amount that can be
	 * registered minus the amount that was
	 * already added.
	 */

	return maximum_amount_of_registered_games(teams, groups) - number_of_games_registered(games);
}

bool
are_all_teams_registered(TEAM *teams)
{
	return number_of_teams_registered(teams) == AMOUNT_OF_GROUPS * AMOUNT_OF_TEAMS_PER_GROUP;
}

bool
are_all_games_registered(TEAM *teams, GAME *games, char groups[])
{
	/*
	 * If the amount of games registered is less than
	 * the maximum amount, then all game aren't added
	 */

	return number_of_games_registered(games) == maximum_amount_of_registered_games(teams, groups);
}
