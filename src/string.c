#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_STRING_LENGTH 2024

typedef char *String;

size_t amount_of_strings = 0;
char **strings 		 = NULL;

String
input(const char *message)
{
	 /*
         * This function receives one pointer to
	 * message that will be shown on default
	 * output and returns a pointer to
	 * string typed by the user.
         */

        size_t amount_of_letters;
	char letter = '\0';
	char string[MAXIMUM_STRING_LENGTH];
	
        printf(message);
        for (amount_of_letters = 0; letter != '\n' && amount_of_letters < MAXIMUM_STRING_LENGTH; amount_of_letters++) {
                scanf("%c", &letter);
                *(string + amount_of_letters) = letter;
	}
	amount_of_letters--;
	string[amount_of_letters] = '\0';

	strings = realloc(strings, sizeof(char *));
	strings[amount_of_strings] = calloc(amount_of_letters + 1, sizeof(char));
	strncpy(strings[amount_of_strings], string, amount_of_letters + 1);

	return strings[amount_of_strings++];
}
/*
int
main(int argc, char *argv[])
{
	String first_name, last_name;
	
	first_name = input("Type your first name: ");
	last_name  = input("Type your last name: ");

	printf("Your name is: %s %s %d\n", first_name, last_name, amount_of_strings);
	return 0;
}
*/
