#define config_h

#define MAXIMUM_STRING_LENGTH 2024

#define AMOUNT_OF_OPTIONS 8
#define AMOUNT_OF_GROUPS  32

struct team {
	char group;
        char *name;
        struct team *next;
};

typedef struct team TEAM;
   
struct game {
        TEAM *team_one;  
        TEAM *team_two;
        struct game *next;
};

typedef struct game GAME;
