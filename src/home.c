#include "home.h"

void home_page(int key)
{
  static int selected_option = 1;
  int total_options = EXIT; // Last Option in Enum is no. of items if Starts with 1
  
  // Add Actions to keys presses
  if (key == ARROW_UP)
  {
    if( selected_option == 1) { selected_option += total_options; }
    selected_option--;
  }
  else if (key == ARROW_DOWN)
  {
    if (selected_option == total_options) { selected_option = 0; }
    selected_option++;
  }
  else if (key == ENTER)
  {
    switch(selected_option)
    {
      case EXIT: quit(); break;
    }
  }
  
  print_header();
  printf("\t\033[37mUse ↑ and ↓ keys to naviagte and \033[3menter\033[0m\n\n");
  print_option(TIC_TAC_TOE,"Tic-Tac-Toe",selected_option);
  print_option(HANGMAN,"Hangman",selected_option);
  print_option(SCORE_BOARD,"Score Board",selected_option);
  print_option(EXIT,"Exit",selected_option);
  
}

void print_option(int id, char* option, int selected_option)
{
  if (id == selected_option)
    printf("\t\033[32;1m[\033[36m*\033[32m]\033[37m %s\033[0m\n", option);
  else
    printf("\t\033[32;2m[\033[36m%d\033[32m]\033[37m %s\033[0m\n",id, option);
}