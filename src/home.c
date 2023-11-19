#include "home.h"

int home_page()
{
  int csi = NONE, key, page = HOME_PAGE, i = 0;
  
  Options pages;
  conf_options(QUIT_PAGE, &pages);
  add_option(TIC_TAC_TOE_PAGE, "Tic-Tac-Toe",&pages);
  add_option(HANGMAN_PAGE, "Hangman",&pages);
  add_option(QUIT_PAGE, "Exit",&pages);
  
  do
  {
    key = get_key(csi, NULL);
    if (key == NONE && i++) continue;
    change_option(key, &pages);
    
    if (key == ENTER)
      page = get_current_option(&pages);
    else
    {
      print_header();
      print_options(&pages);
    }
    
  } while(page == HOME_PAGE && (csi = getc(stdin)) != EOF);
  free_options(&pages);
  
  return page;
}