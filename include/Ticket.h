#ifndef TICKET_H
#define TICKET_H

// <NAME>_PAGE is important to diff between options
// in home.h -> enum Options { ... }
enum Pages { HOME_PAGE, TIC_TAC_TOE_PAGE };

void change_page(int page);

#endif // TICKET_H