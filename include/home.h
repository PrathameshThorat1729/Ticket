#ifndef TICKET_HOME_H
#define TICKET_HOME_H

#include "utils.h"
#include "Ticket.h"

// Here EXIT must be last item ... It use to calculate no. of Options
// in home.c -> void home_page(int key) { ... }
enum Options { TIC_TAC_TOE = 1, HANGMAN, SCORE_BOARD, EXIT };

void print_option(int id, char* option, int selected_option);
void home_page(int key);

#endif // TICKET_HOME_H