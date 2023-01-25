#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

void
clear_input_buffer(void)
{
	scanf("%*c");
}

unsigned int
get_string(char *string, const char *message)
{
	unsigned int amount_of_letters = 0;
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

unsigned int
get_amount(const char *message)
{
	unsigned int amount;
	
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

char
*get_team(TEAM *teams, bool must_be, char group)
{
	unsigned int amount_of_letters_team_name;
	TEAM *last_team_ptr = teams;
	char team_name[MAXIMUM_STRING_LENGTH];

	if (must_be) {

	}
	else {
		do {
			amount_of_letters_team_name = get_string(team_name, "Type the team name: ");

			for (TEAM *team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next) {
				if (!strcmp(team_ptr->name, team_name))
					break;
				last_team_ptr = team_ptr;
			}

		} while (last_team_ptr->next != NULL);

		last_team_ptr->next = (last_team_ptr + 1);	/* pointing to the last position */
		last_team_ptr = last_team_ptr->next;		/* going to a last position	 */

		last_team_ptr->next = NULL;

		last_team_ptr->group = group;
		//last_team_ptr->name = malloc((amount_of_letters_team_name + 1) * sizeof(char));
		strncpy(last_team_ptr->name, team_name, amount_of_letters_team_name + 1);
	}

	return last_team_ptr->name;
}

unsigned int
get_amount_of_registered_teams(TEAM *teams, char group)
{
	unsigned int amount_of_registered_teams = 0;

	for (TEAM *team_ptr = teams->next; team_ptr != NULL; team_ptr = team_ptr->next)
		if (team_ptr->group == group)
			amount_of_registered_teams++;

	return amount_of_registered_teams;
}

unsigned int
number_of_teams_registered(TEAM *teams)
{
	unsigned int number_of_teams_registered = 0;

	for (
			TEAM *team_ptr = teams->next;
			team_ptr != NULL;
			team_ptr = team_ptr->next, number_of_teams_registered++
	   ) ;

	return number_of_teams_registered;
}

unsigned int
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
