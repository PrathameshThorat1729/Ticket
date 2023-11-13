#ifndef TICKET_OPTION_H
#define TICKET_OPTION_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct {
  int id;
  char* desc;
} Option;

typedef struct {
  int total_opt;
  int current_opt;
  int added_opts;
  Option* opts;
} Options;

void conf_options(int total_opt, int default_opt, Options* opts);
void add_option(int id, char* desc, Options* opts);
void print_options(Options* opts);
void change_option(int key, Options* opts);
int get_current_option(Options* opts);
void free_options(Options* opts);

#endif // TICKET_OPTION_H