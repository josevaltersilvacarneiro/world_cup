#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef config_h
#include "config.h"
#endif /* config_h */

extern size_t number_of_teams_registered(TEAM **first_team);

static TEAM *get_team_in_position(TEAM **first_team, size_t position);

static TEAM
*copy_team(TEAM **first_team, size_t position)
{
	TEAM *team;
	TEAM *team_cpy;

	team = get_team_in_position(first_team, position);

	team_cpy = calloc(1, sizeof(TEAM));

	if (team_cpy == NULL) {
		exit(1);
	}

	team_cpy->name = team->name;
	team_cpy->pt   = team->pt;
	team_cpy->gs   = team->gs;
	team_cpy->gc   = team->gc;
	team_cpy->gd   = team->gd;

	team_cpy->next = NULL;
	
	return team_cpy;
}

static TEAM
*get_team_in_position(TEAM **first_team, size_t position)
{
	TEAM *team_ptr;
	size_t pos = -1;

	for (team_ptr = *first_team; team_ptr != NULL && ++pos != position; team_ptr = team_ptr->next) ;

	return team_ptr;
}

static void
switch_teams(TEAM *team_one, TEAM *team_two)
{
	team_one->name = team_two->name;
	team_one->pt   = team_two->pt;
	team_one->gs   = team_two->gs;
	team_one->gc   = team_two->gc;
	team_one->gd   = team_two->gd;
}

void
sort_classification(TEAM **first_team)
{
	size_t length = number_of_teams_registered(first_team);
	register int j;
	unsigned int h = 1;
	TEAM *key;

	while (h < length)
		h = h * 3 + 1;

	h /= 3;

	while (h > 0) {
		for (register int i = h; i < length; i++) {
			key = copy_team(first_team, i); /* alloc */
			j   = i;
			
			while (j >= h && get_team_in_position(first_team, j - h)->pt < key->pt) {
				switch_teams(
						get_team_in_position(first_team, j),
						get_team_in_position(first_team, j - h)
					    );
				j -= h;
			}
			switch_teams(
					get_team_in_position(first_team, j),
					key
				    );

			free(key); /* free */
		}
		h /= 2;
	}
}
