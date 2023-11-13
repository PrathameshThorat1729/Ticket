#include "home.h"

int home_page()
{
  int csi = NONE, key, page = HOME_PAGE, i = 0;
  
  Options pages;
  conf_options(EXIT + 1, TIC_TAC_TOE, &pages);
  add_option(TIC_TAC_TOE, "Tic-Tac-Toe",&pages);
  add_option(HANGMAN, "Hangman",&pages);
  add_option(EXIT, "Exit",&pages);
  
  do
  {
    key = get_key(csi);
    if (key == NONE && i++) continue;
    change_option(key, &pages);
    
    if (key == ENTER)
    {
      switch(get_current_option(&pages))
      {
        case TIC_TAC_TOE: page = TIC_TAC_TOE_PAGE; break;
        case EXIT: page = QUIT; break;
      }
    }
    else {
      print_header();
      print_options(&pages);
    }
    
  } while(page == HOME_PAGE && (csi = getc(stdin)) != EOF);
  free_options(&pages);
  
  return page;
}