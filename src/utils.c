#include "utils.h"

static struct termios default_mode, raw_mode;
static int is_raw_enabled = 0;

void clrscr()
{
  system("clear");
}

void enable_raw_mode()
{
  if (is_raw_enabled)
    return;
  
  printf("\033[?25l");
  tcgetattr(STDIN_FILENO, &default_mode);
  raw_mode = default_mode;
  raw_mode.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
  is_raw_enabled = 1;
}

void disable_raw_mode()
{
  if(!is_raw_enabled)
    return;
  printf("\033[?25h");
  tcsetattr(STDIN_FILENO, TCSANOW, &default_mode);
  is_raw_enabled = 0;
}

void print_header()
{
  clrscr();
  printf("\033[96m\n\n\t\t▀█▀ █ █▀▀ █▄▀ █▀▀ ▀█▀\n");
  printf("\t\t░█░ █ █▄▄ █░█ ██▄ ░█░\n\n\033[0m");
  printf("\t\t\033[34mTerminal Arcade\033[0m  \033[37;1m%s\033[0m\n\n\n", VERSION);
}

void quit()
{
  disable_raw_mode();
  clrscr();
  exit(0);
}

int get_key(int csi)
{
  int ch;
  
  if (csi == '[') // Detecting Escape Squence and Arrow Keys
  {
    ch = getc(stdin);
    switch(ch)
    {
      case 'A': return ARROW_UP; break;
      case 'B': return ARROW_DOWN; break;
      case 'C': return ARROW_RIGHT; break;
      case 'D': return ARROW_LEFT; break;
    }
  }
  else if (csi == '\n') return ENTER;
  return NONE;
}

void print_option(int id, char* option, int selected_option)
{
  if (id == selected_option)
    printf("\t\033[32;1m[\033[36m*\033[32m]\033[37m %s\033[0m\n", option);
  else
    printf("\t\033[32;2m[\033[36m%d\033[32m]\033[37m %s\033[0m\n",id, option);
}

void change_current_option(int key, int total_options, int *current_option)
{
  if (key == ARROW_UP)
  {
    if( *current_option == 1) { *current_option += total_options; }
    *current_option -= 1;
  }
  else if (key == ARROW_DOWN)
  {
    if (*current_option == total_options) { *current_option = 0; }
    *current_option += 1;
  }
}