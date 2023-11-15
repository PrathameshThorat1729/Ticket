#include "hangman.h"

int hangman()
{
  int csi = NONE, key, page = HANGMAN_PAGE, i = 0;
  
  do
  {
    key = get_key(csi);
    if (key == NONE && i++) continue;
    
    print_header();
    if (key == ENTER) page = HOME_PAGE;
    
  } while(page == HANGMAN_PAGE && (csi = getc(stdin)) != EOF);
  
  return page;
}