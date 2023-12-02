#include "games/sudoku.h"

enum SudokuStartOpts { EASY, MEDIUM, HARD, INSANE, GB }; 

int sudoku()
{
  int csi = NONE, key, page = SUDOKU_PAGE, i = 0;
  int sudoku[9][9] = {0}, empty[9][9] = {0};
  int pos[2] = {0}; // cursor position
  int win = -1; // -1 for Game Started
                // 0 for Game Running
                // 1 for Game Won
  int game_level = MEDIUM;
  
  
  Options start_opts;
  conf_options(GB + 1, &start_opts);
  add_option(EASY, "Easy Sudoku", &start_opts);
  add_option(MEDIUM, "Medium Sudoku", &start_opts);
  add_option(HARD, "Hard Sudoku", &start_opts);
  add_option(INSANE, "Insane Sudoku", &start_opts);
  add_option(GB, "Go Back", &start_opts);
  
  // Here QUIT must be last item ... It use to calculate no. of Options
  enum EndOpts { REPLAY, QUIT };
  Options end_opts;
  conf_options(QUIT + 1, &end_opts);
  add_option(REPLAY, "Replay", &end_opts);
  add_option(QUIT, "Quit", &end_opts);
  
  do
  {
    int num = 0;
    key = get_key(csi, &num);
    if (key == NONE && i++ && num < '0' && num > '9') continue;
    
    if (win == -1)
    {
      change_option(key, &start_opts);
      if (key == ENTER)
      {
        game_level = get_current_option(&start_opts);
        if (game_level == GB) { page = HOME_PAGE; continue; }
        win = 0;
        gen_sudoku(sudoku, empty, game_level);
      }
    }
    else if (win == 0)
    {
      if (key == CTRL_Q) { page = HOME_PAGE; continue; }
      else if (key == ARROW_UP && pos[1] > 0) pos[1]--;
      else if (key == ARROW_DOWN && pos[1] < 8) pos[1]++;
      else if (key == ARROW_LEFT && pos[0] > 0) pos[0]--;
      else if (key == ARROW_RIGHT && pos[0] < 8) pos[0]++;
    
      if (num >= '0' && num <= '9' && empty[pos[1]][pos[0]] == 1)
      {
        sudoku[pos[1]][pos[0]] = atoi((char*)&num);
      }
      
      win = detect_sudoku_win(sudoku);
    }
    else if (key == ENTER)
    {
      int ch = get_current_option(&end_opts);
      if (ch == QUIT) page = HOME_PAGE;
      else if (ch == REPLAY)
      {
        gen_sudoku(sudoku, empty, game_level);
        win = 0;
        pos[0] = 0; pos[1] = 0;
      }
    }
    else
      change_option(key, &end_opts);
    
    print_header();
    if (win == -1) { print_options(&start_opts); continue;}
    for (int i = 0; i < 9; i++)
    {
      if (i % 3 == 0) printf("\n\t");
      for (int j = 0; j < 9; j++)
      {
        if (j % 3 == 0) printf("  ");
        if (pos[0] == j && pos[1] == i && win == 0)
        {
          if (sudoku[i][j] != 0) printf("\033[30;47m %d \033[0m", sudoku[i][j]);
          else printf("\033[30;47m - \033[0m");
        }
        else
        {
          if (sudoku[i][j] != 0 && empty[i][j] == 0) printf(" \033[34m%d\033[0m ", sudoku[i][j]);
          else if (sudoku[i][j] != 0 && empty[i][j] == 1) printf(" \033[33;1m%d\033[0m ", sudoku[i][j]);
          else printf(" \033[2m•\033[0m ");
        }
      }
      printf("\n\t");
    }
    printf("\n");
    
    if (win == 1)
    {
      print_options(&end_opts);
    }
  } while(page == SUDOKU_PAGE && (csi = getc(stdin)) != EOF);
  free_options(&start_opts);
  free_options(&end_opts);
  return page;
}

void gen_sudoku(int sudoku[9][9], int empty[9][9], int game_level)
{
  int no_of_empty_cells = 30;
  if (game_level == EASY) no_of_empty_cells = 15;
  else if (game_level == MEDIUM) no_of_empty_cells = 30;
  else if (game_level == HARD) no_of_empty_cells = 45;
  else if (game_level == INSANE) no_of_empty_cells = 60;
  
  // used to create a new sudoku
  int raw[9][9] = {
    {1,2,3,  4,5,6,  7,8,9},
    {4,5,6,  7,8,9,  1,2,3},
    {7,8,9,  1,2,3,  4,5,6},

    {2,3,1,  5,6,4,  8,9,7},
    {5,6,4,  8,9,7,  2,3,1},
    {8,9,7,  2,3,1,  5,6,4},

    {3,1,2,  6,4,5,  9,7,8},
    {6,4,5,  9,7,8,  3,1,2},
    {9,7,8,  3,1,2,  6,4,5}
  };
  // copy sudoku
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
      sudoku[i][j] = raw[i][j];
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
      empty[i][j] = 0;
  }
  
  int r; // random no
  srand(time(0));
  
  // replace numbers
  int ntr[9] = {0}; // numbers to replace
  memset(ntr, 0, 9*sizeof(int));
  for (int i = 0; i < 9; i++)
  {
    r = rand() % 9 + 1;
    for (int j = 0; j < i; j++)
    {
      if (ntr[j] == r)
      {
        r = rand() % 9 + 1;
        j = -1;
      }
    }
    ntr[i] = r;
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
      sudoku[i][j] = ntr[sudoku[i][j] - 1];
  }
  
  // shruffle group column-wise
  r = rand() % 2 + 1;
  for (int i = 0; i < 3; i++)
  {
    swap_cols(i, i + 3 * r, sudoku);
  }
  
  // shruffle group row-wise
  r = rand() % 2 + 1;
  for (int i = 0; i < 3; i++)
  {
    swap_row(i, i + 3 * r, sudoku);
  }
  
  // shruffle rows in groups
  for (int i = 0; i < 9; i += 3)
  {
    r = rand() % 2 + 1;
    swap_row(i, i + r, sudoku);
  }
  
  // shruffle cols in groups
  for (int i = 0; i < 9; i += 3)
  {
    r = rand() % 2 + 1;
    swap_cols(i, i + r, sudoku);
  }
  
  // make cells empty 
  for (int i = 0; i < no_of_empty_cells; i++)
  {
    int x = rand() % 9, y = rand() % 9;
    if (empty[x][y] == 0) { empty[x][y] = 1; sudoku[x][y] = 0; }
    else i--;
  }
}

void swap_row(int x, int y, int sudoku[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    int t = sudoku[x][i];
    sudoku[x][i] = sudoku[y][i];
    sudoku[y][i] = t;
  }
}

void swap_cols(int x, int y, int sudoku[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    int t = sudoku[i][x];
    sudoku[i][x] = sudoku[i][y];
    sudoku[i][y] = t;
  }
}

int detect_sudoku_win(const int sudoku[9][9])
{
  int win = 1;
  for (int i = 0; i < 9 && win == 1 ; i++)
  {
    int num[9] = {0};
    for (int j = 0; j < 9 && win == 1; j++)
    {
      if (sudoku[i][j] == 0)
        win = 0;
      else if (num[sudoku[i][j] - 1] != 0)
        win = 0;
      else
        num[sudoku[i][j] - 1] = 1;
    }
  }
  
  for (int i = 0; i < 9 && win == 1; i++)
  {
    int num[9] = {0};
    for (int j = 0; j < 9 && win == 1; j++)
    {
      if (sudoku[j][i] == 0)
        win = 0;
      else if (num[sudoku[j][i] - 1] != 0)
        win = 0;
      else
        num[sudoku[j][i] - 1] = 1;
    }
  }
  
  for (int i = 0; i < 9 && win == 1; i += 3)
  {
    for (int l = 0; l < 9 && win == 1; l += 3)
    {
      int num[9] = {0};
      for (int j = 0; j < 9 && win == 1; j++)
      {
        int k = j % 3;
        
        if (num[sudoku[i + (j / 3)][k + l] - 1] != 0)
        {
          win = 0;
        }
        else
          num[sudoku[i + (j / 3)][k + l] - 1] = 1;
      }
    }
  }
  
  return win;
}