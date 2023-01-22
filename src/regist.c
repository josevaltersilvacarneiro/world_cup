#include <stdio.h>
#include <stdbool.h>

#ifndef config_h
#include "config.h"
#endif

extern char get_group(char groups[]);
extern unsigned int get_amount_of_registered_teams(TEAM *teams, char group);
extern char *get_team(TEAM *teams, bool must_be, char group);

extern char groups[];

void
regist_team(TEAM *teams)
{
	char group;

	group = get_group(groups);
	while (get_amount_of_registered_teams(teams, group) > 3) {
		printf("The group %c is already complete\n", group);
		
		group = get_group(groups);
	}

	get_team(teams, false, group);
}
