/*
 * The functions and procedures of this file are responsible
 * for editing the teams and games.
 */

#include <stdio.h>
#include <stdbool.h>

#ifndef config_h
#include "config.h"
#endif

extern TEAM *convert_to_team_ptr(const TEAM *first_team, const String team_name);
extern bool  check(const String message);

extern String get_team(const TEAM *first_team, bool is_in);

void edit_team(TEAM *first_team);
void edit_game(TEAM *first_team, GAME *first_game);

void
edit_team(TEAM *first_team)
{
	TEAM  *team;
	String new_team_name;
	String message = "Do you really want to replace first team by second team";

	team	      = convert_to_team_ptr(first_team, get_team(first_team, true));
	new_team_name = get_team(first_team, false);

	if (check(message)) {
		/*
		 * Chain Replacement
		 * The foreign key will be changed
		 * because the primary key has been
		 * changed.
		 */

		team->name = new_team_name;
	}
}

void
edit_game(TEAM *first_team, GAME *first_game)
{
	printf("Editing game\n");
}
