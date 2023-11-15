#include "Ticket.h"

int main()
{
  signal(SIGINT,SIG_IGN);
  enable_raw_mode();
  
  // Order must be same as defined enum
  // in Ticket.h -> enum Pages { ... }
  int (*pages[QUIT])() = { home_page, tic_tac_toe, hangman };
  int current_page = HOME_PAGE;
  
  while(1)
  {
    current_page = pages[current_page]();
    
    if (current_page == QUIT) break;
  }
  quit();
  return 0;
}