#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

size_t
fact(size_t number)
{
	/* This function calculates the factorial of a number */

	if (number == 0)
		return 1;

	return number * fact(number - 1);
}

void
clear_input_buffer(void)
{
	scanf("%*c");
}

size_t
get_string(char *string, const char *message)
{
	/*
	 * This function receives two parameters:
	 * one pointer to string that will be mo-
	 * dified and one pointer to message that
	 * will be shown on default output.
	 *
	 * It returns the amount of characters
	 * typed by the user.
	 */

	size_t amount_of_letters = 0;
	char letter;

	clear_input_buffer();

	printf(message);
	for (register int i = 0; letter != '\n'; i++) {
		scanf("%c", &letter);
		*(string + i) = letter;

		amount_of_letters++;
	}
	amount_of_letters--;
	string[amount_of_letters] = '\0';

	return amount_of_letters;
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

	return fact(get_amount_of_registered_teams(teams, group) - 1);
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
	return sizeof(teams) / sizeof(GAME) - 1;
}

size_t
number_of_games_registered(GAME *games)
{
	return sizeof(games) / sizeof(GAME) - 1;
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
