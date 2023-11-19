#ifndef TICKET_HANGMAN_H
#define TICKET_HANGMAN_H

#include <time.h>
#include "utils.h"
#include "Ticket.h"

int hangman();
void print_hangman(int wrong);
void generate_word(char** word, int *word_len);

#endif // TICKET_HANGMAN_H