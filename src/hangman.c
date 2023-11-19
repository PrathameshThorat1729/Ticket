#include "hangman.h"

int hangman()
{
  srand(time(0));
  int csi = NONE, key, page = HANGMAN_PAGE;
  
  // Here QUIT must be last item ... It use to calculate no. of Options
  enum EndOpts { REPLAY, QUIT };
  
  Options end_opts;
  conf_options(QUIT + 1, &end_opts);
  add_option(REPLAY, "Replay", &end_opts);
  add_option(QUIT, "Quit", &end_opts);
  
  char* word;
  char entered[] = "------";
  int word_len = 0, wrong = 0;
  int win = -1; // -1 for Game Running
                // 0 for Game Lost
                // 1 for Game Won
  
  generate_word(&word, &word_len);
  
  if (word == NULL) page = HOME_PAGE;
  else
  {
    char* tmp_word = (char*)malloc(sizeof(char) * (word_len + 1));
    memset(tmp_word, '-', sizeof(word));
    tmp_word[word_len] = '\0';
    
    do
    {
      int ch;
      key = get_key(csi, &ch);
      
      if (ch >= 'A' && ch <= 'z' && win == -1)
      {
        if (ch <= 'Z') ch += 'a' - 'A'; // converting into lower case
        int match = 0;
        if (strchr(entered, ch) != NULL) match = 1;
        for (int i = 0; i < word_len && match == 0; i++)
        {
          if (ch == word[i] && tmp_word[i] == '-') 
          { tmp_word[i] = (char)ch; match = 1; break; }
        }
        if (!match)
          entered[wrong++] = ch;
      }
      if(!strcmp(word, tmp_word)) win = 1;
      else if (wrong >= 6) win = 0;
      
      if (win != -1)
      {
        change_option(key, &end_opts);
        if (key == ENTER)
        {
          switch(get_current_option(&end_opts))
          {
            case REPLAY:
              generate_word(&word, &word_len);
              free(tmp_word);
              tmp_word = (char*)malloc(sizeof(char) * (word_len + 1));
              memset(tmp_word, '-', sizeof(char) * word_len);
              tmp_word[word_len] = '\0';
              win = -1;
              wrong = 0;
              strcpy(entered, "------");
              break;
            case QUIT: page = HOME_PAGE;
          }
        }
      }
      
      print_header();
      printf("\n\t\033[36;1mTried : \033[0m");
      for (int i = 0; i < 6; i++)
      {
        if (entered[i] == '-')
          printf(" %c ", entered[i]);
        else
          printf(" \033[33;1m%c\033[0m ", entered[i]);
      }
      printf("\n");
      print_hangman(wrong);
      printf("\n\t\033[36;1mWord is : \033[0m");
      for (int i = 0; i < word_len; i++)
      {
        if (tmp_word[i] == '-')
          printf(" %c ", tmp_word[i]);
        else
          printf(" \033[32;1m%c\033[0m ", tmp_word[i]);
      }
      printf("\n\t[\033[36;2m%d letters\033[0m]\n", word_len);
      
      if (win == 1) printf("\n\t\033[1mYou Saved the Man, You won\033[0m\n\n");
      if (win == 0) printf("\n\t\033[1mHe got Hanged,\n\tThe Original word was \033[32;1m%s\033[0m\n\n", word);
      if (win != -1) print_options(&end_opts);
      
      ch = 0;
    } while(page == HANGMAN_PAGE && (csi = getc(stdin)) != EOF);
    free(tmp_word);
  }

  free(word);
  free_options(&end_opts);
  return page;
}

void generate_word(char** word, int* word_len)
{
  char filename[256];
  strcat(strcpy(filename, getenv("HOME")), "/.config/Ticket/hangman_words.txt");
  
  FILE* word_file = fopen(filename,"r");
  
  if (!word_file)
  {
    *word = NULL;
    return;
  }
  
  int total_words, max_word_len;
  fscanf(word_file, "%d %d", &total_words, &max_word_len);
  int nth_word = rand() % total_words + 1;
  
  char tmp_word[max_word_len + 1];
  fseek(word_file, nth_word * (max_word_len + 1), SEEK_SET);
  fscanf(word_file, "%s", tmp_word);
  *word_len = strlen(tmp_word);
  *word = (char*)malloc((*word_len + 1) * sizeof(char));
  strcpy(*word, tmp_word);
  
  fclose(word_file);
}

void print_hangman(int wrong)
{
  printf("\n\t\t   ┏━━━━━━━━┑");
  printf("\n\t\t   \033[30;47;2m▉\033[0m        ╿");
  printf("\n\t\t   ▉        ");
  if (wrong >= 1) printf("O");
  printf("\n\t\t   ▉       ");
  if(wrong >= 3) printf("/"); else printf(" ");
  if (wrong >= 2) printf("╏");
  if (wrong >= 4) printf("\\");
  printf("\n\t\t   ▉       ");
  if (wrong >= 5) printf("/");
  if (wrong >= 6) printf(" \\");
  printf("\n\t\t   ▉");
  printf("\n\t\t\033[31;2m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\033[0m\n");
}