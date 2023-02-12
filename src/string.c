#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_STRING_LENGTH 2024

typedef char *String;

struct string {
	String str;
	size_t references;

	struct string *next;
};

struct string *first_string; /* search */
struct string *last_string; /* append */

void
start_string(void)
{
	first_string = calloc(1, sizeof(struct string *));
	first_string->next = NULL;

	last_string = calloc(1, sizeof(struct string *));
	last_string->next = NULL;
}

String
input(const String message)
{
	 /*
         * This function receives one pointer to
	 * message that will be shown on default
	 * output and returns a pointer to
	 * string typed by the user.
         */

	struct string *new_string;

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

	/* Storing */

	new_string = calloc(1, sizeof(struct string *));
	new_string->str = calloc(amount_of_letters + 1, sizeof(char));
	strncpy(new_string->str, string, amount_of_letters + 1);
	new_string->references = 1;

	last_string->next = new_string;  /* The penultimate string receives the address for the next string */

	last_string = last_string->next; /* The last string now is the new string */
	last_string->next = NULL;

	return new_string->str;
}

void
destroy_string(void)
{
	struct string *next;

	for (; first_string != NULL;) {
		next = first_string->next;
		free(first_string);
		first_string = next;
	}
}
