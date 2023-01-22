#include <stdio.h>

#ifndef config_h
#include "config.h"
#endif

void
regist_team(TEAM teams)
{
	char group;

	group = get_group(groups);
	while (get_amount_of_registered_teams(teams, group) > 3) {
		printf("The group %c is already complete\n", group);
		
		group = get_group(groups);
	}

	get_team(teams, false, group);
}
