#define config_h

#define MAXIMUM_STRING_LENGTH 2024

#define AMOUNT_OF_OPTIONS 8
#define AMOUNT_OF_GROUPS  8

#define AMOUNT_OF_SPACES 30

struct team {
	char group;
        char name[80];
	unsigned int pt; /* points	    */
	unsigned int gs; /* goals scored    */
	unsigned int gc; /* goals conceded  */
	int gd;		 /* goal difference */

        struct team *next;
};

typedef struct team TEAM;
   
struct game {
        TEAM *team_one;  
        TEAM *team_two;
        struct game *next;
};

typedef struct game GAME;

struct cup {
	TEAM *teams;
	GAME *games;
};

typedef struct cup CUP;

