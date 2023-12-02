#ifndef TICKET_GAME_H
#define TICKET_GAME_H

#include <time.h>
#include "utils.h"
#include "Ticket.h"

int sudoku();
void gen_sudoku(int sudoku[9][9], int empty[9][9], int game_lev);
void swap_row(int x, int y, int sudoku[9][9]);
void swap_cols(int x, int y, int sudoku[9][9]);
int detect_sudoku_win(const int sudoku[9][9]);

#endif // TICKET_GAME_H