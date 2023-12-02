#ifndef TICKET_H
#define TICKET_H

#include "utils.h"
#include "home.h"

#include "games/tic_tac_toe.h"
#include "games/hangman.h"
#include "games/sudoku.h"

// Here QUIT must be last item ... It use to calculate no. of Options
// in home.c -> void home_page(int key) { ... }
// <NAME>_PAGE is important to diff between options
// in home.h -> enum Options { ... }
enum Pages { HOME_PAGE, TIC_TAC_TOE_PAGE, HANGMAN_PAGE, SUDOKU_PAGE, QUIT_PAGE };

#endif // TICKET_H