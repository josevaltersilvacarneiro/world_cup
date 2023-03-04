#define config_h

#define AMOUNT_OF_OPTIONS 8

#define AMOUNT_OF_GROUPS	  8
#define AMOUNT_OF_TEAMS_PER_GROUP 4
#define AMOUNT_OF_SPACES 	  30

typedef char *String;

struct team {
	char	     group;
        String 	     name;
	unsigned int pt; /* points	    */
	unsigned int gs; /* goals scored    */
	unsigned int gc; /* goals conceded  */
	int	     gd; /* goal difference */

        struct team *next;
};

typedef struct team TEAM;
   
struct game {
        TEAM	      *team_one;  
        TEAM	      *team_two;
	unsigned short team_one_goals;
	unsigned short team_two_goals;
	unsigned int   date;
	String	       place;

        struct game *next;
};

typedef struct game GAME;

struct cup {
	TEAM *first_team;
	GAME *first_game;
};

typedef struct cup CUP;

