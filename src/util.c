#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

size_t
fact(size_t number)
{
	/* This function calculates the factorial of a number */

	if (number == 1)
		return 1;

	return fact(number - 1);
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
get_amount(const char *message)
{
	size_t amount;
	
	printf(message);
	scanf("%u", &amount);

	return amount;
}

char
get_option(const char options[], unsigned int amount_of_options)
{
	unsigned int option;

	do {
		printf("Type your option: ");
		scanf("%d", &option);

		option--;

	} while (!(option < amount_of_options) || !options[option]);

	return options[option];
}

char
get_group(char groups[])
{
	char group;
	bool found;

	do {
		found = false;
		
		printf("Type a group: ");
		scanf(" %c", &group);

		for (register int i = 0; i < AMOUNT_OF_GROUPS; i++)
			if (group == groups[i]) {
				found = true;
				break;
			}
	} while (!found);

	return group;
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

TEAM
*get_team(const TEAM *teams)
{
	char   team_name[MAXIMUM_STRING_LENGTH];
	TEAM  *team_ptr;

	for (;;) {
		get_string(team_name, "Type a registered team: ");

		for (team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next) {
			if (!strcmp(team_ptr->name, team_name))
				return team_ptr;
			else
				puts("The team typed hasn't added yet");
		}
	}

	return team_ptr;
}

size_t
get_date()
{
	return 0;
}

char
*add_new_team(TEAM *teams, char group)
{
	unsigned int amount_of_letters_team_name;
	char team_name[MAXIMUM_STRING_LENGTH];
	TEAM *last_team_ptr = teams;

	do {
		amount_of_letters_team_name = get_string(team_name, "Type the team name: ");

		for (TEAM *team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next) {
			if (!strcmp(team_ptr->name, team_name))
				break;
			last_team_ptr = team_ptr;
		}

	} while (last_team_ptr->next != NULL);

	last_team_ptr->next = last_team_ptr + 1;	/* pointing to the last position */
	last_team_ptr++;				/* going to a last position	 */

	last_team_ptr->group = group;
	strncpy(last_team_ptr->name, team_name, amount_of_letters_team_name + 1);
	last_team_ptr->pt = 0;
	last_team_ptr->gs = 0;
	last_team_ptr->gc = 0;
	last_team_ptr->gd = 0;

	last_team_ptr->next = NULL;

	return last_team_ptr->name;
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

unsigned int
get_amount_of_registered_teams(const TEAM *teams, char group)
{
	unsigned int amount_of_registered_teams = 0;

	for (TEAM *team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next)
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
	size_t number_of_teams_registered = 0;

	for (
			TEAM *team_ptr = teams->next;
			team_ptr != NULL;
			team_ptr = team_ptr->next, number_of_teams_registered++
	   ) ;

	return number_of_teams_registered;
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

	return AMOUNT_OF_GROUPS * 4 - number_of_teams_registered(teams);
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
