#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef config_h
#include "config.h"
#endif /* config_h */

#define FILENAME "data.json"

bool
does_file_exist(const String filename)
{
	return access(filename, F_OK) == 0;
}

CUP
*get_data(void)
{
	CUP *cup = calloc(1, sizeof(CUP));

	if (!does_file_exist(FILENAME)) {
		cup->teams = calloc(1, sizeof(TEAM));
		cup->games = calloc(1, sizeof(GAME));

		cup->teams->next = NULL;
		cup->games->next = NULL;
	}

	return cup;
}

void
push_data(CUP *cup)
{
	free(cup->games);
	free(cup->teams);
	free(cup);
}
