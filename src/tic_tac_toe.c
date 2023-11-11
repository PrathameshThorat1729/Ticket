#include "tic_tac_toe.h"

// N statnds for none and NONE is used
// in utils.h -> enum Keys { ... }
enum Move { N, X, O, T}; // T -> Tie

// Posible wins in format { x, y } - coordinate
static int win[8][3][2] = {{{0,0},{0,1},{0,2}},
                            {{1,0},{1,1},{1,2}},
                            {{2,0},{2,1},{2,2}},
                            {{0,0},{1,0},{2,0}},
                            {{0,1},{1,1},{2,1}},
                            {{0,2},{1,2},{2,2}},
                            {{0,0},{1,1},{2,2}},
                            {{2,0},{1,1},{0,2}}};

// Current Game board or state
static int current_option = 0; // for naviagtion after game ends
static int game_running = 1;
static int winner = N;
static int player = X;
static int game_state[3][3] = {N};
// current cursor position
static int pos[2] = {0}; // [0] -> x-coordinate
                         // [1] -> y-coordinate

void tic_tac_toe(int key)
{
  if (game_running)
  {
    if (key == ARROW_UP && pos[1] > 0) pos[1]--;
    else if (key == ARROW_DOWN && pos[1] < 2) pos[1]++;
    else if (key == ARROW_LEFT && pos[0] > 0) pos[0]--;
    else if (key == ARROW_RIGHT && pos[0] < 2) pos[0]++;
    else if (key == ENTER && game_state[pos[1]][pos[0]] == N)
    {
      game_state[pos[1]][pos[0]] = player;
      player = (player == X) ? O : X;
    }
    else printf("\a");
  }
  else {
    change_current_option(key, 2, &current_option);
    if (key == ENTER)
    {
      switch(current_option)
      {
        case 1: reset(); break;
        case 2: reset(); change_page(HOME_PAGE); return;
      }
    }
  }
  
  print_header();
  printf("\tPlayer : %c\n\n\t", get_move_char(player));
  for (int i = 0; i < 3; i++) // i -> y-coordinate
  {
    for (int j = 0; j < 3; j++) // j -> x-coordinate
    {
      if (pos[0] == j && pos[1] == i)
        printf(" \033[30;47m%c\033[0m ", get_move_char(game_state[i][j]));
      else
        printf(" %c ", get_move_char(game_state[i][j]));
    }
    printf("\n\t");
  }
  
  winner = detect_win(game_state);
  if (winner != N)
  {
    game_running = 0;
    if (winner == T)
      printf("\n\tNo one won, It's a \033[1mTie\033[0m\n");
    else
      printf("\n\t\033[1m%c\033[0m won\n", get_move_char(winner));
    printf("\n\t\033[37mUse ↑ and ↓ keys to naviagte and \033[3menter\033[0m\n\n");
    current_option = (current_option) ? current_option : 1;
    print_option(1, "Restart", current_option);
    print_option(2, "Quit", current_option);
  }
}

char get_move_char(int move)
{
  if (move == X) return 'x';
  if (move == O) return 'o';
  return '-';
}

int detect_win(int game_state[3][3])
{
  int is_tie = 1;
  for (int i = 0; i < 8; i++)
  {
    int x_win = 0, o_win = 0;
    for (int j = 0; j < 3; j++)
    {
      if (game_state[win[i][j][1]][win[i][j][0]] == X) x_win++;
      if (game_state[win[i][j][1]][win[i][j][0]] == O) o_win++;
    }
    if (x_win == 3) return X;
    if (o_win == 3) return O;
  }
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      if (game_state[i][j] == N) is_tie = 0;
  }
  
  if (is_tie) return T;
  return N;
}

void reset()
{
  current_option = 0;
  memset(game_state, 0, sizeof(game_state));
  pos[0] = 0; pos[1] = 0;
  winner = N;
  game_running = 1;
}