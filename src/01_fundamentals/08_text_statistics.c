#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_BUFFER 2048
#define ALPHABET_SIZE 26

static const char *MSG_TITLE = "=== Text Analyzer ===\n";
static const char *MSG_INPUT_PROMPT = "Enter text (type END on a new line to finish):\n";
static const char *MSG_END_TRIGGER = "END";

static const char *MSG_STATS_HEADER = "\n=== Text Statistics ===\n";
static const char *FMT_TOTAL_CHARS = "Total characters: %d\n";
static const char *FMT_CHARS_NO_SPACE = "Characters without spaces: %d\n";
static const char *FMT_WORDS = "Words: %d\n";
static const char *FMT_SENTENCES = "Sentences: %d\n";
static const char *FMT_LINES = "Lines: %d\n";

static const char *FMT_AVG_WORD_LEN = "\nAverage word length: %.2f characters\n";
static const char *FMT_LONGEST_WORD = "Longest word: \"%s\" (%d characters)\n";
static const char *FMT_SHORTEST_WORD = "Shortest word: \"%s\" (%d characters)\n";

static const char *MSG_DIST_HEADER = "\nCharacter Distribution:\n";
static const char *FMT_DIST_LETTERS = "Letters: %d (%.2f%%)\n";
static const char *FMT_DIST_SPACES = "Spaces: %d (%.2f%%)\n";
static const char *FMT_DIST_PUNCT = "Punctuation: %d (%.2f%%)\n";

static const char *MSG_VOWELS_HEADER = "\nVowel Frequency:\n";
static const char *FMT_VOWEL_VAL = "%c: %d";
static const char *MSG_VOWEL_SEP = ", ";

static const char *MSG_PANGRAM_HEADER = "\n\nIs it a pangram? ";
static const char *MSG_PANGRAM_YES = "YES \342\234\223\n";
static const char *MSG_PANGRAM_NO = "NO\n";
static const char *MSG_PANGRAM_DESC = "(Contains all 26 letters of the alphabet)\n";

void analyze_text(const char *text);
int is_vowel(char c);

int main(void) {
  char buffer[MAX_BUFFER] = "";
  char line[256];

  printf("%s", MSG_TITLE);
  printf("%s", MSG_INPUT_PROMPT);

  while (TRUE) {
    if (!fgets(line, sizeof(line), stdin))
      break;
    if (strncmp(line, MSG_END_TRIGGER, 3) == 0 && (line[3] == '\n' || line[3] == '\r'))
      break;
    strcat(buffer, line);
  }

  analyze_text(buffer);

  return 0;
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

  printf("%s", MSG_STATS_HEADER);
  printf(FMT_TOTAL_CHARS, total_chars);
  printf(FMT_CHARS_NO_SPACE, chars_no_space);
  printf(FMT_WORDS, words);
  printf(FMT_SENTENCES, sentences);
  printf(FMT_LINES, lines);

  if (words > 0) {
    printf(FMT_AVG_WORD_LEN, total_word_len / words);
    printf(FMT_LONGEST_WORD, longest_word, (int)strlen(longest_word));
    printf(FMT_SHORTEST_WORD, shortest_word, (int)strlen(shortest_word));
  }

  printf("%s", MSG_DIST_HEADER);
  printf(FMT_DIST_LETTERS, letters, (letters * 100.0) / total_chars);
  printf(FMT_DIST_SPACES, spaces, (spaces * 100.0) / total_chars);
  printf(FMT_DIST_PUNCT, punct, (punct * 100.0) / total_chars);

  printf("%s", MSG_VOWELS_HEADER);
  char vowels[] = "aeiou";
  for (int i = 0; i < 5; i++) {
    printf(FMT_VOWEL_VAL, vowels[i], vowel_counts[i]);
    if (i < 4)
      printf("%s", MSG_VOWEL_SEP);
  }

  int unique_letters = 0;
  for (int i = 0; i < ALPHABET_SIZE; i++)
    if (alpha_present[i])
      unique_letters++;

  printf("%s", MSG_PANGRAM_HEADER);
  if (unique_letters == ALPHABET_SIZE) {
    printf("%s", MSG_PANGRAM_YES);
    printf("%s", MSG_PANGRAM_DESC);
  } else {
    printf("%s", MSG_PANGRAM_NO);
  }
}

int is_vowel(char c) {
  c = tolower(c);
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}
