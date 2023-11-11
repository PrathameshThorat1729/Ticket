#ifndef TICKET_TIC_TAC_TOE_H
#define TICKET_TIC_TAC_TOE_H

#include "utils.h"
#include "Ticket.h"
#include <time.h>

void tic_tac_toe(int key);
char get_move_char(int move); // Return 'x' or 'o'
int detect_win(int game_state[3][3]);
void reset();

#endif // TICKET_TIC_TAC_TOE_H