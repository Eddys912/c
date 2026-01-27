/*
 ===============================================================================
 Exercise: 08_text_statistics.c
 Description: Text analysis tool for statistical reporting
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Character count (total, no spaces, punctuation)
 - Word, sentence, and line counting
 - Vowel frequency analysis
 - Pangram detection (using all alphabet letters)
 - Longest/Shortest word finding
 ===============================================================================
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_BUFFER 2048
#define ALPHABET_SIZE 26

int is_vowel(char c);
void analyze_text(const char *text);

int main(void) {
  char buffer[MAX_BUFFER] = "";
  char line[256];

  printf("=== Text Analyzer ===\n");
  printf("Enter text (type END on a new line to finish):\n");

  while (TRUE) {
    if (!fgets(line, sizeof(line), stdin))
      break;
    if (strncmp(line, "END", 3) == 0 && (line[3] == '\n' || line[3] == '\r'))
      break;
    strcat(buffer, line);
  }

  analyze_text(buffer);

  return 0;
}

int is_vowel(char c) {
  c = tolower(c);
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void analyze_text(const char *text) {
  int total_chars = strlen(text);
  int chars_no_space = 0, words = 0, sentences = 0, lines = 0;
  int letters = 0, spaces = 0, punct = 0;
  int vowel_counts[5] = {0}; // a, e, i, o, u
  int alpha_present[ALPHABET_SIZE] = {0};

  char longest_word[50] = "", shortest_word[50] = "";
  char current_word[50];
  int word_idx = 0;
  double total_word_len = 0;

  for (int i = 0; i <= total_chars; i++) {
    char c = text[i];

    if (c == '\n')
      lines++;
    if (c == '.' || c == '!' || c == '?')
      sentences++;

    if (isalpha(c)) {
      letters++;
      chars_no_space++;
      alpha_present[tolower(c) - 'a'] = TRUE;
      if (is_vowel(c)) {
        char lc = tolower(c);
        if (lc == 'a')
          vowel_counts[0]++;
        else if (lc == 'e')
          vowel_counts[1]++;
        else if (lc == 'i')
          vowel_counts[2]++;
        else if (lc == 'o')
          vowel_counts[3]++;
        else if (lc == 'u')
          vowel_counts[4]++;
      }
      current_word[word_idx++] = c;
    } else {
      if (isspace(c)) {
        if (c != '\n' && c != '\r')
          spaces++;
      } else if (ispunct(c)) {
        punct++;
        chars_no_space++;
      }

      if (word_idx > 0) {
        current_word[word_idx] = '\0';
        words++;
        total_word_len += word_idx;

        if (strlen(longest_word) == 0 || word_idx > (int)strlen(longest_word))
          strcpy(longest_word, current_word);
        if (strlen(shortest_word) == 0 || word_idx < (int)strlen(shortest_word))
          strcpy(shortest_word, current_word);

        word_idx = 0;
      }
    }
  }

  printf("\n=== Text Statistics ===\n");
  printf("Total characters: %d\n", total_chars);
  printf("Characters without spaces: %d\n", chars_no_space);
  printf("Words: %d\n", words);
  printf("Sentences: %d\n", sentences);
  printf("Lines: %d\n", lines);

  if (words > 0) {
    printf("\nAverage word length: %.2f characters\n", total_word_len / words);
    printf("Longest word: \"%s\" (%d characters)\n", longest_word, (int)strlen(longest_word));
    printf("Shortest word: \"%s\" (%d characters)\n", shortest_word, (int)strlen(shortest_word));
  }

  printf("\nCharacter Distribution:\n");
  printf("Letters: %d (%.2f%%)\n", letters, (letters * 100.0) / total_chars);
  printf("Spaces: %d (%.2f%%)\n", spaces, (spaces * 100.0) / total_chars);
  printf("Punctuation: %d (%.2f%%)\n", punct, (punct * 100.0) / total_chars);

  printf("\nVowel Frequency:\n");
  char vowels[] = "aeiou";
  for (int i = 0; i < 5; i++) {
    printf("%c: %d", vowels[i], vowel_counts[i]);
    if (i < 4)
      printf(", ");
  }

  int unique_letters = 0;
  for (int i = 0; i < ALPHABET_SIZE; i++)
    if (alpha_present[i])
      unique_letters++;

  printf("\n\nIs it a pangram? ");
  if (unique_letters == ALPHABET_SIZE) {
    printf("YES \342\234\223\n");
    printf("(Contains all 26 letters of the alphabet)\n");
  } else {
    printf("NO\n");
  }
}
