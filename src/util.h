#ifndef config_h
#include "config.h"
#endif /* config_h */

char get_option(const char options[], unsigned int amount_of_options);
char get_group_with_registered_teams(TEAM *teams, char groups[]);
unsigned int get_amount_of_registered_teams(TEAM *teams, char group);
