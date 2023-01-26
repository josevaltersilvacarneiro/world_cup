#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef config_h
#include "config.h"
#endif

extern char groups[];

extern char get_group(char groups[]);
extern unsigned int get_amount_of_registered_teams(TEAM *teams, char group);
extern char *add_new_team(TEAM *teams, char group);

extern unsigned int number_of_teams_to_register(TEAM *teams);
extern unsigned int get_amount(const char *message);

void
regist_team(TEAM *teams)
{
	char group;

	group = get_group(groups);
	while (get_amount_of_registered_teams(teams, group) > 3) {
		printf("The group %c is already complete\n", group);
		group = get_group(groups);
	}

	add_new_team(teams, group);
}

TEAM
*regist_teams(TEAM *teams)
{
	unsigned int max_amount, amount_of_teams;
	TEAM *_teams = teams;
	
	max_amount = number_of_teams_to_register(teams);

	amount_of_teams = get_amount("Number of teams: ");
	while (amount_of_teams > max_amount) {
		printf("Only %u teams left to register\n", max_amount);
		amount_of_teams = get_amount("Number of teams: ");
	}
	
	teams = realloc(teams, amount_of_teams * sizeof(TEAM)); /* See the main function in world_cup.c */

	if (!teams) {
		printf("There was an error\n");
		return _teams; /* There wasn't enough memory */
	} else
		_teams = teams;

	while (amount_of_teams-- > 0)
		regist_team(teams);

	return teams;
}
