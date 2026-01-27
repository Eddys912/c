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
#define EXIT_OPTION 2
#define DEFAULT_MIN 1
#define DEFAULT_MAX 100
#define MAX_ATTEMPTS 7

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
    printf("=== Smart Guessing Game ===\n");
    printf("1. Play New Game\n2. Exit\n");
    printf("Option: ");

    if (!read_integer(&option)) {
      printf("Error: Invalid input. Please try again.\n");
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("Thank you for playing!\n");
      break;
    }

    if (option == 1) {
      play_game(&games_played, &games_won, &total_attempts_used);
      display_stats(games_played, games_won, total_attempts_used);
    } else {
      printf("Error: Invalid input. Please try again.\n");
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

  printf("\nConfiguration:\n");
  printf("Range: %d-%d\n", DEFAULT_MIN, DEFAULT_MAX);
  printf("Max attempts: %d\n", MAX_ATTEMPTS);
  printf("Secret number generated...\n\n");

  while (attempts < MAX_ATTEMPTS) {
    attempts++;
    printf("Attempt %d/%d: ", attempts, MAX_ATTEMPTS);

    if (!read_integer(&guess)) {
      printf("Error: Invalid input. Please try again.\n");
      attempts--;
      continue;
    }

    if (guess == secret) {
      printf("CORRECT! \n");
      printf("Number found: %d\n", secret);
      printf("Attempts used: %d/%d\n", attempts, MAX_ATTEMPTS);
      double efficiency = ((double)(MAX_ATTEMPTS - attempts + 1) / MAX_ATTEMPTS) * 100;
      printf("Efficiency: %.0f%%\n", efficiency);

      (*total_wins)++;
      won = TRUE;
      break;
    } else if (guess < secret) {
      printf("Hint: The number is HIGHER\n");
      if (guess >= current_min)
        current_min = guess + 1;
    } else {
      printf("Hint: The number is LOWER\n");
      if (guess <= current_max)
        current_max = guess - 1;
    }

    printf("Updated range: %d-%d\n\n", current_min, current_max);
  }

  if (!won) {
    printf("GAME OVER! The number was: %d\n", secret);
  }

  (*total_games)++;
  (*total_attempts) += attempts;
}

void display_stats(int games, int wins, int attempts) {
  printf("\nSession Statistics:\n");
  printf("- Games played: %d\n", games);
  printf("- Victories: %d\n", wins);
  if (games > 0) {
    printf("- Average attempts: %.1f\n\n", (float)attempts / games);
  }
}
