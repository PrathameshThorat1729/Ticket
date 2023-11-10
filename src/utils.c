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
      case 'C': return ARROW_LEFT; break;
      case 'D': return ARROW_RIGHT; break;
    }
  }
  else if (csi == '\n') return ENTER;
  return NONE;
}