#include "games/tic_tac_toe.h"

// N statnds for none and NONE is used
// in utils.h -> enum Keys { ... }
enum Move { N, X, O, T}; // T -> Tie

int tic_tac_toe()
{
  // Here QUIT must be last item ... It use to calculate no. of Options
  enum EndOpts { REPLAY, QUIT };
  // Here GB must be last item ... It use to calculate no. of Options
  enum StartOpts { PTC, PTP, GB }; // Player to Computer
                                   // Player to Player
                                   // Go Back
  
  // Posible wins in format { x, y } - coordinate
  int win[8][3][2] = {{{0,0},{0,1},{0,2}},
                      {{1,0},{1,1},{1,2}},
                      {{2,0},{2,1},{2,2}},
                      {{0,0},{1,0},{2,0}},
                      {{0,1},{1,1},{2,1}},
                      {{0,2},{1,2},{2,2}},
                      {{0,0},{1,1},{2,2}},
                      {{2,0},{1,1},{0,2}}};
  
  // Current Game board or state
  int game_running = 0;
  int game_mode;
  int winner = N;
  int player = X, starting_player = X;
  int game_state[3][3] = {N};
  int nth_move = 1; // which move is going
  
  // current cursor position
  int pos[2] = {0}; // [0] -> x-coordinate
                    // [1] -> y-coordinate

  int csi = NONE, key, page = TIC_TAC_TOE_PAGE, i = 0;
  
  Options start_opts;
  conf_options(GB + 1, &start_opts);
  add_option(PTC, "Player vs Computer", &start_opts);
  add_option(PTP, "Player vs Player", &start_opts);
  add_option(GB, "Go Back", &start_opts);
  
  Options end_opts;
  conf_options(QUIT + 1, &end_opts);
  add_option(REPLAY, "Replay", &end_opts);
  add_option(QUIT, "Quit", &end_opts);
  
  do
  {
    key = get_key(csi, NULL);
    if (key == NONE && i++) continue;
    
    // Game Starting
    if (game_running == 0 && winner == N)
    {
      print_header();
      change_option(key, &start_opts);
      print_options(&start_opts);
      if (key == ENTER)
      {
        game_mode = get_current_option(&start_opts);
        if(game_mode == GB) {page = HOME_PAGE; break;}
        game_running = 1;
        key = NONE;
      }
      else continue;
    }
    // Game Ends
    else if (game_running == 0 && winner != N)
    {
      change_option(key, &end_opts);
      if (key == ENTER)
      {
        switch(get_current_option(&end_opts))
        {
          case REPLAY:
            memset(game_state, 0, sizeof(game_state));
            pos[0] = 0; pos[1] = 0;
            player = (starting_player == O) ? X : O;
            starting_player = player;
            winner = N;
            game_running = 1;
            key = NONE;
            nth_move = 1;
            break;
          case QUIT: page = HOME_PAGE;
        }
      }
    }
    
    if (game_running == 1 && winner == N)
    {
      if (key == CTRL_Q) { page = HOME_PAGE; continue; }
      else if (key == ARROW_UP && pos[1] > 0) pos[1]--;
      else if (key == ARROW_DOWN && pos[1] < 2) pos[1]++;
      else if (key == ARROW_LEFT && pos[0] > 0) pos[0]--;
      else if (key == ARROW_RIGHT && pos[0] < 2) pos[0]++;
      else if (key == ENTER && game_state[pos[1]][pos[0]] == N)
      {
        nth_move++;
        game_state[pos[1]][pos[0]] = player;
        player = (player == X) ? O : X;
        winner = detect_ttt_win(game_state, win);
      }
      if (game_mode == PTC && player == O && winner == N)
      {
        make_move(nth_move++, game_state);
        winner = detect_ttt_win(game_state, win);
        player = (player == X) ? O : X;
      }
    }
  
    print_header();
    if (player == X) printf("\tPlayer : X\n\n\t");
    else if (player == O) printf("\tPlayer : O\n\n\t");
    for (int i = 0; i < 3; i++) // i -> y-coordinate
    {
      for (int j = 0; j < 3; j++) // j -> x-coordinate
      {
        int p = game_state[i][j];
        if (pos[0] == j && pos[1] == i && winner == N)
        {
          if (p == X) printf(" \033[30;47m X \033[0m ");
          else if (p == O) printf(" \033[30;47m O \033[0m ");
          else printf(" \033[30;47m   \033[0m ");
        }
        else
        {
          if (p == X) printf("  \033[33;1mX\033[0m  ");
          else if (p == O) printf("  \033[36;1mO\033[0m  ");
          else printf("     ");
        }
        if(j < 2) printf(" │ ");
      }
      printf("\n\t");
      if (i < 2) printf("---------------------\n\t");
    }
    
    if (winner != N)
    {
      game_running = 0;
      if (winner == T)
        printf("\n\tNo one won, It's a \033[32;1mTie\033[0m\n\n");
      else
      {
        if (winner == X) printf("\n\t\033[32;1mX\033[0m won\n\n");
        else if (winner == O) printf("\n\t\033[32;1mO\033[0m won\n\n");
      }
      print_options(&end_opts);
    }
  } while(page == TIC_TAC_TOE_PAGE && (csi = getc(stdin)) != EOF);
  free_options(&end_opts);
  
  return page;
}

int detect_ttt_win(int game_state[3][3], int win[8][3][2])
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

void make_move(int nth_move, int game_state[3][3])
{
  if (nth_move == 1) {game_state[0][0] = O; return;}
  else if (nth_move == 3)
  {
    if (game_state[1][1] == X || game_state[0][2] == X || game_state[2][0] == X) {game_state[2][2] = O;return;}
    else if (game_state[2][2] == X) { game_state[0][2] = O; return;}
    else if (game_state[0][1] == X || game_state[1][0] == X ||
             game_state[1][2] == X || game_state[2][1] == X) {game_state[1][1] = O; return;}
  }
  else if (nth_move == 5)
  {
    if (game_state[1][1] == X)
    {
      if (game_state[0][2] == X) {game_state[2][0] = O; return;}
      if (game_state[2][0] == X) {game_state[0][2] = O; return;}
      if (game_state[2][2] == X) {game_state[0][2] = O; return;}
    }
    else if (game_state[1][1] == O) {
      if (game_state[0][1] == X) {game_state[2][0] = O; return;}
      if (game_state[1][0] == X) {game_state[0][2] = O; return;}
    }
    else if (game_state[0][1] == X && game_state[2][2] == X) {game_state[2][0] = O; return;}
  }
  else if (nth_move == 2)
  {
    if (game_state[1][1] == X) {game_state[0][0] = O; return;}
    else {game_state[1][1] = O; return;}
  }
  else if (nth_move == 4)
  {
    if (game_state[2][2] == X && game_state[1][1] == X)
    { game_state[0][2] = O; return;}
    else if (game_state[2][2] == X && game_state[0][0] == X)
    { game_state[0][1] = O; return;}
    else if (game_state[0][2] == X && game_state[2][0] == X)
    { game_state[0][1] = O; return;}
  }
  
  int moved = 0;
  int emp[2] = { -1 }; // empty cell location
  
  // Horizontal
  for (int i = 0; i < 3 && moved == 0; i++)
  {
    int t = -1, n = -1;
    for (int j = 0; j < 3; j++)
    {
      if (game_state[i][j] == N)
      {
        if (n != -1) break;
        n = j;
        emp[0] = i; emp[1] = j;
      }
      else if (t == -1) t = game_state[i][j];
      else if (t == game_state[i][j]) t = -2;
    }
    if (t == -2 && n != -1)
    {
      game_state[i][n] = O;
      moved = 1;
    }
  }
  
  // Vertical
  for (int j = 0; j < 3 && moved == 0; j++)
  {
    int t = -1, n = -1;
    for (int i = 0; i < 3; i++)
    {
      if (game_state[i][j] == N)
      {
        if (n != -1) break;
        n = i;
        emp[0] = i; emp[1] = j;
      }
      else if (t == -1) t = game_state[i][j];
      else if (t == game_state[i][j]) t = -2;
    }
    if (t == -2 && n != -1)
    {
      game_state[n][j] = O;
      moved = 1;
    }
  }
  
  int t = -1, n = -1;
  
  // Diagonal 1
  for (int i = 0; i < 3 && moved == 0; i++)
  {
    if (game_state[i][i] == N)
    {
      if (n != -1) break;
      n = i;
    }
    else if (t == -1) t = game_state[i][i];
    else if (t == game_state[i][i]) t = -2;
  }
  if (t == -2 && n != -1)
  {
    game_state[n][n] = O;
    moved = 1;
  }
  
  t = -1, n = -1;
  // Diagonal 2
  for (int i = 0; i < 3 && moved == 0; i++)
  {
    if (game_state[i][2 - i] == N)
    {
      if (n != -1) break;
      n = i;
    }
    else if (t == -1) t = game_state[i][2 - i];
    else if (t == game_state[i][2 - i]) t = -2;
  }
  if (t == -2 && n != -1)
  {
    game_state[n][2 - n] = O;
    moved = 1;
  }
  
  if (moved == 0) game_state[emp[0]][emp[1]] = O;
}