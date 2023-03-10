#ifndef config_h
#include "config.h"
#endif /* config_h */

/* Conversion functions */

TEAM *convert_to_team_ptr(TEAM **first_team, const String team_name);
TEAM *convert_to_before_team_ptr(TEAM **first_team, const String team_name);

GAME *find_game(GAME **first_game, const TEAM *team_one, const TEAM *team_two);
GAME *find_before_game(GAME **first_game, const TEAM *team_one, const TEAM *team_two);

bool check(const String message);

size_t get_amount(String message);
char get_option(const char options[], unsigned int amount_of_options);
char get_group_with_registered_teams(TEAM **first_team, char groups[]);
String get_team(TEAM **first_team, bool is_in);
size_t get_date();
String get_place(void);

size_t maximum_amount_of_registered_games_group(TEAM **first_team, char group);
size_t maximum_amount_of_registered_games(TEAM **first_team, char groups[]);

size_t get_amount_of_registered_teams(TEAM **first_team, char group);
size_t get_amount_of_registered_games(GAME **first_game, char group);

size_t number_of_teams_registered(TEAM **first_team);
size_t number_of_games_registered(GAME **first_game);

size_t number_of_teams_to_register(TEAM **first_team);
size_t number_of_games_to_register(TEAM **first_team, GAME **first_game, char groups[]);

bool are_all_teams_registered(TEAM **first_team);
bool are_all_games_registered(TEAM **first_team, GAME **first_game, char groups[]);

bool is_every_registered(TEAM **first_team, GAME **first_game, char groups[]);

bool is_any_game_registered(GAME **first_game);
bool is_any_team_registered(TEAM **first_team);

extern String input(const String message);
