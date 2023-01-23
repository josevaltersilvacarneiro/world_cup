#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef config_h
#include "config.h"
#endif

unsigned int
get_string(char *string, const char *message)
{
	unsigned int amount_of_letters = 0;
	char letter;

	printf(message);
	scanf("\n"); /* Clean the buffer */
	for (register int i = 0; letter != '\n'; i++) {
		scanf("%c", &letter);
		string[i] = letter;

		amount_of_letters++;
	}
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
*get_team(TEAM *teams, bool must_be, char group)
{
	unsigned int amount_of_letters_team_name;
	TEAM *team_ptr;
	char team_name[MAXIMUM_STRING_LENGTH];

	if (must_be) {

	}
	else {
		do {
			amount_of_letters_team_name = get_string(team_name, "Type the team name: ");

			for (
				team_ptr = teams->next;
				team_ptr != NULL || strcmp(team_ptr->name, team_name);
				team_ptr = teams->next
			    ) ;
		} while (team_ptr != NULL);

		teams = realloc(teams, sizeof(TEAM)); /* See the main function in world_cup.c */
		team_ptr->next = (team_ptr + 1);

		team_ptr++;

		team_ptr->group = group;

		team_ptr->name = malloc(amount_of_letters_team_name * sizeof(char) + 1);
		strcpy(team_ptr->name, team_name);
		
		team_ptr->next = NULL;
	}

	return team_ptr->name;
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
	return AMOUNT_OF_GROUPS * 4 - number_of_teams_registered(teams);
}
