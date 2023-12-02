#ifndef TICKET_UTILS_H
#define TICKET_UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "option.h"

enum Keys {
  ARROW_UP,
  ARROW_RIGHT,
  ARROW_DOWN,
  ARROW_LEFT,
  ENTER,
  CTRL_Q,
  NONE
};

void enable_raw_mode();
void disable_raw_mode();
void print_header();
void quit();

// key is store in raw key if not in Keys enum
int get_key(int CSI, int* raw_key);

#endif // TICKET_UTILS_H