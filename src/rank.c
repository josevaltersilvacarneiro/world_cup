#ifndef config_h
#include "config.h"
#endif /* config_h */

static void handle_game(GAME *game, char option);

void register_game(GAME *game);
void unscramble_game(GAME *game);

static void
handle_game(GAME *game, char option)
{
	if (game->team_one_goals > game->team_two_goals)
                game->team_one->pt += (option == '+') ? 3 : -3;
        else if (game->team_one_goals == game->team_two_goals) {
                game->team_one->pt += (option == '+') ? 1 : -1;
                game->team_two->pt += (option == '+') ? 1 : -1;
        } else
                game->team_two->pt += (option == '+') ? 3 : -3;
        
        /* team_one */

        game->team_one->gs += (option == '+') ? game->team_one_goals : -game->team_one_goals;
        game->team_one->gc += (option == '+') ? game->team_two_goals : -game->team_two_goals;
        game->team_one->gd  = game->team_one->gs - game->team_one->gc;

        /* team_two */

        game->team_two->gs += (option == '+') ? game->team_two_goals : -game->team_two_goals;
        game->team_two->gc += (option == '+') ? game->team_one_goals : -game->team_one_goals;
        game->team_two->gd  = game->team_two->gs - game->team_two->gc;
}

void
register_game(GAME *game)
{
	handle_game(game, '+');
}

void
unscramble_game(GAME *game)
{
	handle_game(game, '-');
}
