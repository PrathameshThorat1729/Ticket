#include "utils.h"

static struct termios default_mode, raw_mode;
static int is_raw_enabled = 0;

void enable_raw_mode()
{
  if (is_raw_enabled)
    return;
  
  printf("\033[?25l\033[0m");
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
  system("clear");
  printf("\n\t\t\033[96m▀█▀ █ █▀▀ █▄▀ █▀▀ ▀█▀\033[0m\n");
  printf("\t\t\033[96m░█░ █ █▄▄ █░█ ██▄ ░█░\033[0m\n\n");
  printf("\t\t\033[34mTerminal Arcade\033[0m  \033[37;1m%s\033[0m\n\n", VERSION);
}

void quit()
{
  disable_raw_mode();
  system("clear");
  exit(EXIT_SUCCESS);
}

int get_key(int csi, int* raw_key)
{
  int ch;
  if (raw_key != NULL) *raw_key = 0;
  
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
  if (raw_key != NULL) *raw_key = csi;
  return NONE;
}