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

	printf("%s", message);
	for (
			register int i = 0;
			letter != '\n' && amount_of_letters < MAXIMUM_STRING_LENGTH;
			amount_of_letters++, i++) {
		scanf("%c" &letter);
		string[i] = letter;
	}
	string[amount_of_letters] = '\0';

	return amount_of_letters;
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
get_group(groups)
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

		team_ptr->name = malloc(amount_of_letters * sizeof(char) + 1);
		strcpy(team_pt->name, team_name);
		
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
