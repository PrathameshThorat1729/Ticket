#include "option.h"

void conf_options(int total_opt, int default_opt, Options* opts)
{
  opts->total_opt = total_opt;
  opts->added_opts = 0;
  opts->current_opt = default_opt;
  opts->opts = calloc(sizeof(Option), total_opt);
}

void print_options(Options* opts)
{
  printf("\n\t\033[37mUse ↑ and ↓ keys to naviagte and \033[3menter\033[0m\n\n");
  for (int i = 0; i < opts->total_opt; i++)
  {
    if (i == opts->current_opt)
      printf("\t\033[32;1m[\033[36m#\033[32m]\033[37m %s\033[0m\n", (opts->opts[i]).desc);
    else
      printf("\t\033[32;2m[\033[36m•\033[32m]\033[37m %s\033[0m\n", (opts->opts[i]).desc);
  }
}

void change_option(int key, Options* opts)
{
  if (key == ARROW_UP)
  {
    if(opts->current_opt == 0) { opts->current_opt += opts->total_opt; }
    opts->current_opt -= 1;
  }
  else if (key == ARROW_DOWN)
  {
    if (opts->current_opt == opts->total_opt - 1) { opts->current_opt = -1; }
    opts->current_opt += 1;
  }
}

int get_current_option(Options* opts)
{
  return (opts->opts[opts->current_opt]).id;
}

void free_options(Options* opts)
{
  free(opts->opts);
}

void add_option(int id, char* desc, Options* opts)
{
  Option opt = { id, desc };
  opts->opts[(opts->added_opts)++] = opt;
}