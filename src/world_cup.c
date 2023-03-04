#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef config_h
#include "config.h"
#endif /* config_h */

char groups[] = {
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
};

extern void start_string();
extern void destroy_string();

extern CUP *get_data(void);
extern void push_data(CUP *cup);

extern char get_option(const char options[], unsigned int amount_of_options);

extern bool are_all_teams_registered(TEAM **first_team);
extern bool are_all_games_registered(TEAM **first_team, GAME **first_game, char groups[]);

extern bool is_any_game_registered(GAME **first_game);
extern bool is_any_team_registered(TEAM **first_team);
extern bool is_every_registered(TEAM **first_team, GAME **first_game, char groups[]);

extern TEAM *regist_teams(TEAM **first_team);
extern GAME *regist_games(const TEAM **first_team, GAME **first_game);

extern void edit_team(TEAM **first_team);
extern void edit_game(TEAM **first_team, GAME **first_game);

extern void delete_team(TEAM **first_team, GAME **first_game);
extern void delete_game(TEAM **first_team, GAME **first_game);

extern float group_goal_average(GAME **first_game, char group);
extern float goal_average(GAME **first_game);
extern GAME *most_goals_in_a_game(GAME **first_game);

extern void sort_classification(TEAM **first_team);

void print_group_goal_average(CUP *cup);
void print_goal_average(CUP *cup);
void print_team_with_most_goals_in_the_cup(CUP *cup);

void
print_hyphens(void)
{
	for (register int i = 0; i < AMOUNT_OF_SPACES; i++)
		printf("-");
	printf("\n");
}

void
print_spaces(size_t amount)
{
	for (register int i = amount; i != 0; i--)
		printf(" ");
}

void
regist(CUP *cup)
{
	char options[2];
	char option;

	if (!are_all_teams_registered(cup->teams)) {
		printf("1 → Register teams\n");
		options[0] = 't';
	}

	if (!are_all_games_registered(cup->teams, cup->games, groups)) {
		printf("2 → Register games\n");
		options[1] = 'g';
	}

	option = get_option(options, 2);

	switch (option) {
		case 't':
			cup->first_team = regist_teams(&cup->first_team);
			break;
		case 'g':
			cup->first_game = regist_games(&cup->first_team, &cup->first_game);
			break;
	}
}

void
edit(CUP *cup)
{
	char option;
	char options[2];

	printf("1 → Edit team\n");
	options[0] = 't';

	if (is_any_game_registered(&cup->first_game)) {
		printf("2 → Edit game\n");
		options[1] = 'g';
	}

	option = get_option(options, 2);

	switch (option) {
		case 't':
			edit_team(&cup->first_team);
			break;
		case 'g':
			edit_game(&cup->first_team, &cup->first_game);
			break;
	}
}

void
delete(CUP *cup)
{
	char option;
	char options[2];

	puts("1 → Delete team");
	options[0] = 't';

	if (is_any_game_registered(&cup->first_game)) {
		puts("2 → Delete game");
		options[1] = 'g';
	}

	option = get_option(options, 2);

	switch (option) {
		case 't':
			delete_team(&cup->first_team, &cup->first_game);
			break;
		case 'g':
			delete_game(&cup->first_team, &cup->first_game);
	}
}

void
print_statistics(CUP *cup)
{
	print_hyphens();
	puts("Statistics");
	print_hyphens();

	print_group_goal_average(cup);
	print_goal_average(cup);
	print_team_with_most_goals_in_the_cup(cup);

	print_hyphens();
}

void
print_group_goal_average(CUP *cup)
{
	float group_goal_aver;

	puts("# Group Goal Average");

	for (register int i = 0; i < AMOUNT_OF_GROUPS; i++) {
		group_goal_aver = group_goal_average(&cup->first_game, groups[i]); /* See statistics.c */

		printf("%c\t%.1f\n", groups[i], group_goal_aver);
	}

	puts("");
}

void
print_goal_average(CUP *cup)
{
	float goal_aver;

	goal_aver = goal_average(&cup->first_game);

	printf("# Goal Average: %f", goal_aver);
}

void
print_team_with_most_goals_in_the_cup(CUP *cup)
{
	GAME *game = most_goals_in_a_game(&cup->first_game);

	printf("# More goals in a match: %s\n",
		(game->team_one_goals > game->team_two_goals) ? game->team_one->name : game->team_two->name
	      );

	printf("%s\n", game->place);
	printf("%s %u vs %u %s",
		game->team_one->name, game->team_one_goals, game->team_two_goals, game->team_one->name
	      );
}

void
print_teams(CUP *cup)
{
	sort_classification(&cup->first_team);

	for (register int i = 0; i < AMOUNT_OF_GROUPS; i++) {
		print_hyphens();
		printf("%15c\n", groups[i]);
		print_hyphens();

		printf("NAME%20sGDGSGC\n", "PT");

		for (TEAM *team_ptr = cup->first_team; team_ptr != NULL; team_ptr = team_ptr->next)
			if (team_ptr->group == groups[i]) {
				printf("%s", team_ptr->name);

				print_spaces(22 - strlen(team_ptr->name));
				
				printf("%2u%2d%2u%2u\n",
				      team_ptr->pt,
				      team_ptr->gd,
				      team_ptr->gs,
				      team_ptr->gc);
			}
	}
	print_hyphens();
}

int
main(int argc, char *argv[])
{
	bool quit;
	CUP *cup;

	start_string();

	cup = get_data();

	quit = false;
	do {
		char options[AMOUNT_OF_OPTIONS];
		char option;

		if (!is_every_registered(&cup->first_team, &cup->first_game, groups)) {
			printf("1 → Register\n");
			options[0] = 'r';
		}

		if (is_any_team_registered(&cup->first_team)) {
			printf("2 → Edit\n");
			options[1] = 'e';

			puts("3 → Delete");
			options[2] = 'd';
		}

		if (is_every_registered(&cup->first_team, &cup->first_game, groups)) {
			puts("4 → Statistic");
			puts("5 → Release of the next phase games");

			options[3] = 's';
			options[4] = 'n';
		}
		
		printf("6 → Show the teams\n");
		options[5] = 'p';

		printf("7 → Exit without saving changes\n");
		options[6] = 'w';

		printf("8 → Exit and save changes\n");
		options[7] = 'c';

		option = get_option(options, AMOUNT_OF_OPTIONS);

		switch (option) {
			case 'r':
				regist(cup);
				break;
			case 'e':
				edit(cup);
				break;
			case 'd':
				delete(cup);
				break;
			case 's':
				print_statistics(cup);
				break;
			case 'n':
				break;
			case 'p':
				print_teams(cup);
				break;
			case 'w':
				break;
			case 'c':
				quit = true;
				break;
		}
	} while (!quit);

	push_data(cup);

	destroy_string();

	return 0;
}
