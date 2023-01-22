#include <stdio.h>
#include <string.h>

unsigned int
get_string(char *string, const char *message)
{
	unsigned int amount_of_letters = 0;
	char letter;

	printf("%s", message);
	for (; letter != '\n' && amount_of_letters < MAXIMUM_STRING_LENGTH; amount_of_letters++) {
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
	TEAM *team_ptr;
	char team_name[MAXIMUM_STRING_LENGTH];

	if (must_be) {

	}
	else {
		do {
			team_name = get_string(team_name);

			for (
				team_ptr = teams->next;
				team_ptr != NULL || strcmp(team_ptr->name, team_name);
				team_ptr = teams->next
			    ) ;
		} while (team_ptr != NULL);

		teams = realloc(sizeof(TEAM)); /* See the main function in world_cup.c */
		team_ptr->next = (team_ptr + 1);

		team_ptr++;

		team_ptr->group = group;
		team_ptr->name = team_name;
		team_ptr->next = NULL;
	}

	return team_ptr->name;
}
