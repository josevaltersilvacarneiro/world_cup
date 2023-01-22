#include <stdio.h>

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
