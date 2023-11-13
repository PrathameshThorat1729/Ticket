#include "game.h"

int game()
{
  int csi = NONE, key, game = GAME_PAGE, i = 0;
  
  // Only if game has options to navigate with arrow keys
  Options game_options;
  conf_options(total_opts, defualt_opt, &game_options);
  add_option(id, option_desc, &game_options);
  
  do{
    key = get_key(csi);
    if (key == NONE && i++) continue;
    
    // Only if game has options to navigate with arrow keys
    change_option(key, &game_options);
    
    ///////////////////////////
    ///// Game code here //////
    ///// and change page /////
    ///// and after this  /////
    ///// game goes to    /////
    ///// that page       /////
    ///////////////////////////
    
    while(page == GAME_PAGE && (csi = getc(stdin)) != EOF);
  }
  free_options(&game_options);
  
  return page;
}