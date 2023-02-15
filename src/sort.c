#include <stddef.h>

#ifndef config_h
#include "config.h"
#endif /* config_h */

extern size_t number_of_teams_registered(TEAM *teams);

TEAM
*get_team_in_position(TEAM *first_team, size_t position)
{
	size_t pos = 0;

	for (TEAM *team_ptr = first_team; team_ptr != NULL; team_ptr = team_ptr->next, pos += 1)
		if (pos == position)
			return team_ptr;

	return NULL;
}

void
switch_teams(TEAM *first_team, TEAM *team_one, TEAM *team_two)
{
	TEAM *team_aux;
	TEAM *before_team_one = NULL;
	TEAM *before_team_two = NULL;

	for (TEAM *team_ptr = first_team; team_ptr != NULL; team_ptr = team_ptr->next) {
		if (team_ptr->next == team_one)
			before_team_one = team_ptr;
		else if (team_ptr->next == team_two)
			before_team_two = team_ptr;

		if (before_team_one != NULL && before_team_two != NULL)
			break;
	}

	before_team_one->next = team_two;
	before_team_two->next = team_one;

	team_aux = team_one->next;
	team_one->next = team_two->next;
	team_two->next = team_aux;
}

void
sort_classification(TEAM *first_team)
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
			key = get_team_in_position(first_team, i);
			j = i;
			
			while (j >= h && get_team_in_position(first_team, j - h)->pt > key->pt) {
				switch_teams(
						first_team,
						get_team_in_position(first_team, j),
						get_team_in_position(first_team, j - h)
					    );
				j -= h;
			}
			switch_teams(
					first_team,
					get_team_in_position(first_team, j),
					key
				    );
		}
		h /= 2;
	}
}
