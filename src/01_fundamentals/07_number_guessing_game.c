#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define EXIT_OPTION 2
#define DEFAULT_MIN 1
#define DEFAULT_MAX 100
#define MAX_ATTEMPTS 7

static const char *MSG_MENU_TITLE = "=== Smart Guessing Game ===\n";
static const char *MSG_MENU_OPTIONS = "1. Play New Game\n2. Exit\n";
static const char *MSG_CONFIG_HEADER = "Configuration:\n";
static const char *MSG_RANGE_INFO = "Range: %d-%d\n";
static const char *MSG_ATTEMPTS_LIMIT = "Max attempts: %d\n";
static const char *MSG_GENERATE_SECRET = "Secret number generated...\n\n";

static const char *INPUT_OPTION = "Option: ";
static const char *INPUT_GUESS = "Attempt %d/%d: ";

static const char *HINT_HIGHER = "Hint: The number is HIGHER\n";
static const char *HINT_LOWER = "Hint: The number is LOWER\n";
static const char *HINT_RANGE_UPDATE = "Updated range: %d-%d\n\n";

static const char *LABEL_WIN = "CORRECT! \n";
static const char *LABEL_LOSE = "GAME OVER! The number was: %d\n";
static const char *LABEL_FOUND = "Number found: %d\n";
static const char *LABEL_USED_ATTEMPTS = "Attempts used: %d/%d\n";
static const char *LABEL_EFFICIENCY = "Efficiency: %.0f%%\n";

static const char *MSG_STATS_HEADER = "\nSession Statistics:\n";
static const char *FMT_STATS_PLAYED = "- Games played: %d\n";
static const char *FMT_STATS_WINS = "- Victories: %d\n";
static const char *FMT_STATS_AVG = "- Average attempts: %.1f\n\n";

static const char *ERR_MSG_INVALID = "Error: Invalid input. Please try again.\n";
static const char *MSG_GOODBYE = "Thank you for playing!\n";

void clear_input_buffer(void);
int read_integer(int *value);
void play_game(int *total_games, int *total_wins, int *total_attempts);
void display_stats(int games, int wins, int attempts);

int main(void) {
  int option = 0;
  int games_played = 0;
  int games_won = 0;
  int total_attempts_used = 0;

  srand((unsigned int)time(NULL));

  while (TRUE) {
    printf("%s", MSG_MENU_TITLE);
    printf("%s", MSG_MENU_OPTIONS);
    printf("%s", INPUT_OPTION);

    if (!read_integer(&option)) {
      printf("%s", ERR_MSG_INVALID);
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("%s", MSG_GOODBYE);
      break;
    }

    if (option == 1) {
      play_game(&games_played, &games_won, &total_attempts_used);
      display_stats(games_played, games_won, total_attempts_used);
    } else {
      printf("%s", ERR_MSG_INVALID);
    }
  }

  return 0;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

void play_game(int *total_games, int *total_wins, int *total_attempts) {
  int secret = (rand() % (DEFAULT_MAX - DEFAULT_MIN + 1)) + DEFAULT_MIN;
  int current_min = DEFAULT_MIN;
  int current_max = DEFAULT_MAX;
  int guess = 0;
  int attempts = 0;
  int won = FALSE;

  printf("\n%s", MSG_CONFIG_HEADER);
  printf(MSG_RANGE_INFO, DEFAULT_MIN, DEFAULT_MAX);
  printf(MSG_ATTEMPTS_LIMIT, MAX_ATTEMPTS);
  printf("%s", MSG_GENERATE_SECRET);

  while (attempts < MAX_ATTEMPTS) {
    attempts++;
    printf(INPUT_GUESS, attempts, MAX_ATTEMPTS);

    if (!read_integer(&guess)) {
      printf("%s", ERR_MSG_INVALID);
      attempts--;
      continue;
    }

    if (guess == secret) {
      printf("%s", LABEL_WIN);
      printf(LABEL_FOUND, secret);
      printf(LABEL_USED_ATTEMPTS, attempts, MAX_ATTEMPTS);
      double efficiency = ((double)(MAX_ATTEMPTS - attempts + 1) / MAX_ATTEMPTS) * 100;
      printf(LABEL_EFFICIENCY, efficiency);

      (*total_wins)++;
      won = TRUE;
      break;
    } else if (guess < secret) {
      printf("%s", HINT_HIGHER);
      if (guess >= current_min)
        current_min = guess + 1;
    } else {
      printf("%s", HINT_LOWER);
      if (guess <= current_max)
        current_max = guess - 1;
    }

    printf(HINT_RANGE_UPDATE, current_min, current_max);
  }

  if (!won) {
    printf(LABEL_LOSE, secret);
  }

  (*total_games)++;
  (*total_attempts) += attempts;
}

void display_stats(int games, int wins, int attempts) {
  printf("%s", MSG_STATS_HEADER);
  printf(FMT_STATS_PLAYED, games);
  printf(FMT_STATS_WINS, wins);
  if (games > 0) {
    printf(FMT_STATS_AVG, (float)attempts / games);
  }
}
