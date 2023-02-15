#ifndef config_h
#include "config.h"
#endif /* config_h */

/* Conversion functions */

TEAM *convert_to_team_ptr(const TEAM *teams, const String team_name);

size_t get_amount(String message);
char get_option(const char options[], unsigned int amount_of_options);
char get_group_with_registered_teams(TEAM *teams, char groups[]);
String get_team(const TEAM *teams, bool is_in);
size_t get_date();
String get_place(void);

size_t maximum_amount_of_registered_games_group(const TEAM *teams, char group);
size_t maximum_amount_of_registered_games(const TEAM *teams, char groups[]);

size_t get_amount_of_registered_teams(const TEAM *teams, char group);
size_t get_amount_of_registered_games(GAME *games, char group);

size_t number_of_teams_registered(TEAM *teams);
size_t number_of_games_registered(GAME *games);

size_t number_of_teams_to_register(TEAM *teams);
size_t number_of_games_to_register(const TEAM *teams, GAME *games, char groups[]);

bool are_all_teams_registered(TEAM *teams);
bool are_all_games_registered(TEAM *teams, GAME *games, char groups[]);

extern String input(const String message);
