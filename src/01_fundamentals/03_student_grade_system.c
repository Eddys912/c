#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_NAME_LENGTH 100
#define NUM_GRADES 5
#define MIN_PASS_GRADE 60.0
#define EXCELLENT_GRADE 90.0
#define FALSE 0
#define TRUE 1

static const char *MSG_TITLE = "=== Student Grade System ===\n\n";
static const char *MSG_STUDENTS_TITLE = "\n=== Students ===\n\n";
static const char *MSG_STATS_TITLE = "\n=== General Statistics ===\n\n";
static const char *MSG_PASSED_TITLE = "\nStudents who passed:\n";

static const char *INPUT_NUM_STUDENTS = "Number of students (max 50): ";
static const char *INPUT_NAME = "Enter student %d name: ";
static const char *INPUT_GRADE = "  Enter grade %d: ";

static const char *LABEL_STUDENT_HEADER = "Student %d:\n";
static const char *LABEL_NAME = "Name: %s\n";
static const char *LABEL_GRADES = "Grades (5): ";
static const char *LABEL_RESULT = "Average: %.2f - %s\n\n";

static const char *FMT_STATS_GROUP = "Group average: %.2f\n";
static const char *FMT_STATS_BEST = "Best student: %s (%.2f)\n";
static const char *FMT_STATS_WORST = "Worst student: %s (%.2f)\n";
static const char *FMT_STATS_PASS_RATE = "Pass rate: %.2f%% (%d/%d)\n";
static const char *FMT_PASS_LIST = "%d. %s - %.2f\n";

static const char *ERR_INVALID = "Error: Invalid input. Try again.\n\n";
static const char *ERR_LIMIT = "Error: Max students is %d\n\n";

static const char *STATUS_EXCELLENT = "EXCELLENT";
static const char *STATUS_PASS = "PASS";
static const char *STATUS_FAIL = "FAIL";

void clear_input_buffer(void);
int read_integer(int *value);
int read_double(double *value);
void get_status_string(double avg, char status_out[]);
void process_statistics(int num, char names[][MAX_NAME_LENGTH], double avgs[]);
void sort_indices_by_grade(double avgs[], int indices[], int count);

int main(void) {
  char names[MAX_STUDENTS][MAX_NAME_LENGTH];
  double all_grades[MAX_STUDENTS][NUM_GRADES];
  double averages[MAX_STUDENTS];
  int num_students;

  printf("%s", MSG_TITLE);
  printf("%s", INPUT_NUM_STUDENTS);

  if (!read_integer(&num_students) || num_students > MAX_STUDENTS || num_students <= 0) {
    printf(ERR_LIMIT, MAX_STUDENTS);
    return 1;
  }

  for (int i = 0; i < num_students; i++) {
    printf(INPUT_NAME, i + 1);
    fgets(names[i], MAX_NAME_LENGTH, stdin);
    names[i][strcspn(names[i], "\n")] = 0;

    double sum = 0;
    for (int j = 0; j < NUM_GRADES; j++) {
      printf(INPUT_GRADE, j + 1);
      double grade;
      if (!read_double(&grade) || grade < 0 || grade > 100) {
        printf("%s", ERR_INVALID);
        j--;
        continue;
      }
      all_grades[i][j] = grade;
      sum += grade;
    }
    averages[i] = sum / NUM_GRADES;
  }

  printf(MSG_STUDENTS_TITLE);
  for (int i = 0; i < num_students; i++) {
    char status[20];
    get_status_string(averages[i], status);

    printf(LABEL_STUDENT_HEADER, i + 1);
    printf(LABEL_NAME, names[i]);
    printf("%s", LABEL_GRADES);
    for (int j = 0; j < NUM_GRADES; j++) {
      printf("%.0f ", all_grades[i][j]);
    }
    printf("\n");
    printf(LABEL_RESULT, averages[i], status);
  }

  process_statistics(num_students, names, averages);

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

int read_double(double *value) {
  if (scanf("%lf", value) != 1) {
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

void get_status_string(double avg, char status_out[]) {
  if (avg >= EXCELLENT_GRADE) {
    strcpy(status_out, STATUS_EXCELLENT);
  } else if (avg >= MIN_PASS_GRADE) {
    strcpy(status_out, STATUS_PASS);
  } else {
    strcpy(status_out, STATUS_FAIL);
  }
}

void process_statistics(int num, char names[][MAX_NAME_LENGTH], double avgs[]) {
  double group_sum = 0;
  int best_idx = 0, worst_idx = 0, pass_count = 0;
  int passed_indices[MAX_STUDENTS];

  for (int i = 0; i < num; i++) {
    group_sum += avgs[i];
    if (avgs[i] > avgs[best_idx])
      best_idx = i;
    if (avgs[i] < avgs[worst_idx])
      worst_idx = i;
    if (avgs[i] >= MIN_PASS_GRADE) {
      passed_indices[pass_count] = i;
      pass_count++;
    }
  }

  printf("%s", MSG_STATS_TITLE);
  printf(FMT_STATS_GROUP, group_sum / num);
  printf(FMT_STATS_BEST, names[best_idx], avgs[best_idx]);
  printf(FMT_STATS_WORST, names[worst_idx], avgs[worst_idx]);
  printf(FMT_STATS_PASS_RATE, (pass_count * 100.0) / num, pass_count, num);

  if (pass_count > 0) {
    printf("%s", MSG_PASSED_TITLE);
    sort_indices_by_grade(avgs, passed_indices, pass_count);

    for (int i = 0; i < pass_count; i++) {
      int idx = passed_indices[i];
      printf(FMT_PASS_LIST, i + 1, names[idx], avgs[idx]);
    }
  }
}

void sort_indices_by_grade(double avgs[], int indices[], int count) {
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (avgs[indices[j]] < avgs[indices[j + 1]]) {
        int temp = indices[j];
        indices[j] = indices[j + 1];
        indices[j + 1] = temp;
      }
    }
  }
}
