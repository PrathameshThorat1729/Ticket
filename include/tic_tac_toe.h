#ifndef TICKET_TIC_TAC_TOE_H
#define TICKET_TIC_TAC_TOE_H

#include "utils.h"
#include "Ticket.h"

int tic_tac_toe();
char get_move_char(int move); // Return 'x' or 'o'
int detect_win(int game_state[3][3], int win[8][3][2]);

#endif // TICKET_TIC_TAC_TOE_H