/*
 ===============================================================================
 Exercise: 07_number_guessing_game.c
 Description: Number guessing game with logic hints and statistics
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Random number generation
 - Logic hints (Higher/Lower)
 - Dynamic range updates
 - Session statistics tracking (wins, attempts, efficiency)
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MIN_OPTION 1
#define MAX_OPTION 2
#define DEFAULT_MIN 1
#define DEFAULT_MAX 100
#define MAX_ATTEMPTS 7

typedef enum { SUCCESS, ERR_INVALID_INPUT, ERR_INVALID_OPTION } Status;

typedef struct {
  int games_played;
  int games_won;
  int total_attempts;
} SessionStats;

typedef struct {
  Status status;
  int won;
  int attempts;
  double efficiency;
} GameResult;

void show_menu(void);
void show_stats(const SessionStats *stats);
void handle_error(Status status);
void run_game_session(SessionStats *stats);

void clear_input_buffer(void);
Status read_integer(int *value);

GameResult play_game_logic(int secret_number);
int generate_secret_number(int min, int max);

int main(void) {
  int option = 0;
  SessionStats stats = {0, 0, 0};

  srand((unsigned int)time(NULL));

  while (TRUE) {
    show_menu();

    if (read_integer(&option) != SUCCESS) {
      handle_error(ERR_INVALID_INPUT);
      continue;
    }

    if (option == MAX_OPTION) {
      printf("\nThank you for playing!\n");
      break;
    }

    if (option < MIN_OPTION || option > MAX_OPTION) {
      handle_error(ERR_INVALID_OPTION);
      continue;
    }

    if (option == 1) {
      run_game_session(&stats);
    }
  }

  return 0;
}

void show_menu(void) {
  printf("=== Smart Guessing Game ===\n\n");
  printf("1. Play New Game\n2. Exit\n");
  printf("Option: ");
}

void show_stats(const SessionStats *stats) {
  printf("\n------ Session Statistics ------\n\n");
  printf("  - Games played: %d\n", stats->games_played);
  printf("  - Victories: %d\n", stats->games_won);

  if (stats->games_played > 0) {
    double avg = (double)stats->total_attempts / stats->games_played;
    printf("  - Average attempts: %.1f\n\n", avg);
  } else {
    printf("\n");
  }
}

void handle_error(Status status) {
  switch (status) {
  case ERR_INVALID_INPUT:
    printf("Error: Invalid input. Please try again.\n\n");
    break;
  case ERR_INVALID_OPTION:
    printf("Error: Invalid option selection.\n\n");
    break;
  case SUCCESS:
    break;
  }
}

void run_game_session(SessionStats *stats) {
  int secret = generate_secret_number(DEFAULT_MIN, DEFAULT_MAX);

  printf("\n------ Configuration ------\n\n");
  printf("  - Range: %d-%d\n", DEFAULT_MIN, DEFAULT_MAX);
  printf("  - Max attempts: %d\n", MAX_ATTEMPTS);
  printf("  - Secret number generated...\n\n");

  GameResult result = play_game_logic(secret);

  if (result.status == SUCCESS) {
    stats->games_played++;
    stats->total_attempts += result.attempts;

    if (result.won) {
      stats->games_won++;
      printf("\nCORRECT\n");
      printf("  - Number found: %d\n", secret);
      printf("  - Attempts used: %d/%d\n", result.attempts, MAX_ATTEMPTS);
      printf("  - Efficiency: %.0f%%\n", result.efficiency);
    } else {
      printf("\nGAME OVER\n");
      printf("  - The number was: %d\n", secret);
    }

    show_stats(stats);
  }
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    ;
  }
}

Status read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    clear_input_buffer();
    return ERR_INVALID_INPUT;
  }
  clear_input_buffer();
  return SUCCESS;
}

GameResult play_game_logic(int secret_number) {
  GameResult result = {SUCCESS, FALSE, 0, 0.0};
  int current_min = DEFAULT_MIN;
  int current_max = DEFAULT_MAX;
  int guess = 0;

  while (result.attempts < MAX_ATTEMPTS) {
    result.attempts++;
    printf("Attempt %d/%d: ", result.attempts, MAX_ATTEMPTS);

    if (read_integer(&guess) != SUCCESS) {
      printf("Error: Invalid input. Try again.\n");
      result.attempts--;
      continue;
    }

    if (guess == secret_number) {
      result.won = TRUE;
      result.efficiency = ((double)(MAX_ATTEMPTS - result.attempts + 1) / MAX_ATTEMPTS) * 100.0;
      break;
    } else if (guess < secret_number) {
      printf("  - Hint: The number is HIGHER\n");
      if (guess >= current_min) {
        current_min = guess + 1;
      }
    } else {
      printf("  - Hint: The number is LOWER\n");
      if (guess <= current_max) {
        current_max = guess - 1;
      }
    }

    printf("  - Updated range: %d-%d\n\n", current_min, current_max);
  }

  return result;
}

int generate_secret_number(int min, int max) { return (rand() % (max - min + 1)) + min; }
