#ifndef TICKET_UTILS_H
#define TICKET_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

enum Keys {
  ARROW_UP,
  ARROW_RIGHT,
  ARROW_DOWN,
  ARROW_LEFT,
  ENTER,
  NONE
};

void clrscr();
void enable_raw_mode();
void disable_raw_mode();
void print_header();
void quit();

int get_key(int CSI);

#endif // TICKET_UTILS_H