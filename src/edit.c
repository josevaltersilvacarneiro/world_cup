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
extern GAME *find_game(GAME *first_game, const TEAM *team_one, const TEAM *team_two);

extern bool  check(const String message);

extern char   get_option(char options[], unsigned int amount_of_options);
extern size_t get_amount(String message);

extern String get_team(const TEAM *first_team, bool is_in);

extern size_t get_date(void);
extern String get_place(void);

/* rank.c */

extern void register_game(GAME *game);
extern void unscramble_game(GAME *game);

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
	TEAM *team_one;
	TEAM *team_two;
	String message = "Do you really want to replace first team vs second team";

	ed_gam:
		team_one = convert_to_team_ptr(first_team, get_team(first_team, true));
		team_two = convert_to_team_ptr(first_team, get_team(first_team, true));

	if (team_one == team_two || team_one->group != team_two->group) {
		puts("Invalid entry");
		goto ed_gam;
	}

	if (check(message)) {
		GAME *game;
		char options[4] = {'o', 't', 'm', 'p'};
		char option;
	
		game = find_game(first_game, team_one, team_two);

		option = get_option(options, 4);

		switch (option) {
			size_t number_of_goals;

			case 'o':
				number_of_goals = get_amount("Number of goals for team one");

				if (game->team_one == team_one)
					game->team_one_goals = number_of_goals;
				else if (game->team_two == team_one)
					game->team_two_goals = number_of_goals;
				
				unscramble_game(game); /* This doesn't exclude the game */
				break;
			case 't':
				number_of_goals = get_amount("Number of goals for team two");

				if (game->team_one == team_two)
					game->team_one_goals = number_of_goals;
				else if (game->team_two == team_two)
					game->team_two_goals = number_of_goals;

				unscramble_game(game); /* This doesn't exclude the game */
				break;
			case 'm':
				game->date = get_date();
				break;
			case 'p':
				game->place = get_place();
				break;
		}

		if (option == 'o' || option == 't')
			register_game(game); /* This doens't allocate memory */
	}
}
