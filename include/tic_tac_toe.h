#ifndef TICKET_TIC_TAC_TOE_H
#define TICKET_TIC_TAC_TOE_H

#include "utils.h"
#include "Ticket.h"

int tic_tac_toe();
int detect_win(int game_state[3][3], int win[8][3][2]);
void make_move(int nth_move, int game_state[3][3]);

#endif // TICKET_TIC_TAC_TOE_H