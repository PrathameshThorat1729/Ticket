#ifndef TICKET_HOME_H
#define TICKET_HOME_H

#include "utils.h"
#include "Ticket.h"

// Here EXIT must be last item ... It use to calculate no. of Options
// in home.c -> void home_page(int key) { ... }
enum Options { TIC_TAC_TOE, HANGMAN, EXIT };

int home_page();

#endif // TICKET_HOME_H