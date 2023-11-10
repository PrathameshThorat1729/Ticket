#include <stdio.h>

#include "Ticket.h"
#include "utils.h"

#include "home.h"

// This is changes by other pages using function
// in Ticket.h -> void change_page(int page);
static int current_page = HOME_PAGE;
static int last_page = HOME_PAGE;

void change_page(int page)
{
  last_page = current_page;
  current_page = page;
}

int main()
{
  signal(SIGINT,SIG_IGN);
  enable_raw_mode();
  
  // Order must be same as defined enum
  // in Ticket.h -> enum Pages { ... }
  void (*pages[])(int) = { home_page };
  
  int csi, key, started = 0;
  do
  {
    key = get_key(csi);
    // Skip Other invalid keys only if program is started
    if (key == NONE && started++) continue;
    
    pages[current_page](key);
    
    // Render new Page, if Changed
    if(last_page != current_page)
    {
      key = NONE;
      pages[current_page](key);
      last_page = current_page;
    }
    
  } while((csi = getc(stdin)) != EOF);
  
  quit();
  return 0;
}