#include "home.h"

void home_page(int key)
{
  static int current_option = 1;
  int total_options = EXIT; // Last Option in Enum is no. of items if Starts with 1
  
  // Add Actions to keys presses
  change_current_option(key, total_options, &current_option);
  
  ////////////////////////////////////////////
  /// Add New Page here in switch statment ///
  ////////////////////////////////////////////
  if (key == ENTER)
  {
    // If change_page() is called input must be from
    // enum Pages { ... } in Ticket.h
    switch(current_option)
    {
      case TIC_TAC_TOE: change_page(TIC_TAC_TOE_PAGE); break;
      case EXIT: quit(); break;
    }
  }
  
  print_header();
  printf("\t\033[37mUse ↑ and ↓ keys to naviagte and \033[3menter\033[0m\n\n");
  print_option(TIC_TAC_TOE,"Tic-Tac-Toe",current_option);
  print_option(HANGMAN,"Hangman",current_option);
  print_option(EXIT,"Exit",current_option);
  
}