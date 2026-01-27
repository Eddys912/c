/*
 ===============================================================================
 Exercise: 03_student_grade_system.c
 Description: Student grade management system with statistics
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Manages up to 50 students with 5 grades each
 - Calculates individual and group averages
 - Determines pass/fail status (minimum 60, excellent 90+)
 - Identifies best and worst performing students
 - Computes pass rate percentage
 - Displays sorted list of passing students
 ===============================================================================
*/

#include <stdio.h>
#include <string.h>

#define TRUE 1
#define MAX_STUDENTS 50
#define MAX_NAME_LENGTH 100
#define NUM_GRADES 5
#define MIN_PASS_GRADE 60.0
#define EXCELLENT_GRADE 90.0
#define MAX_STATUS_LENGTH 20

typedef enum { SUCCESS, ERR_INVALID_COUNT, ERR_INVALID_INPUT } Status;

typedef struct {
  double group_average;
  int best_student_idx;
  int worst_student_idx;
  int pass_count;
  double pass_rate;
} GroupStatistics;

void clear_input_buffer(void);
Status read_integer(int *value);
Status read_double(double *value);
void read_string(char *buffer, int max_length);
void handle_error(Status status);

void calculate_student_average(double grades[], double *average);
void determine_status(double average, char status_out[]);
void calculate_group_statistics(int num_students, double avgs[], GroupStatistics *stats);
void sort_indices_by_grade_desc(double avgs[], int indices[], int count);

void run_student_entry(int *num_students, char names[][MAX_NAME_LENGTH],
                       double grades[][NUM_GRADES], double averages[]);
void show_student_report(int num_students, char names[][MAX_NAME_LENGTH],
                         double grades[][NUM_GRADES], double averages[]);
void show_group_statistics(int num_students, char names[][MAX_NAME_LENGTH], double averages[]);

int main(void) {
  char names[MAX_STUDENTS][MAX_NAME_LENGTH];
  double all_grades[MAX_STUDENTS][NUM_GRADES];
  double averages[MAX_STUDENTS];
  int num_students = 0;

  printf("=== Student Grade System ===\n\n");

  run_student_entry(&num_students, names, all_grades, averages);

  if (num_students > 0) {
    show_student_report(num_students, names, all_grades, averages);
    show_group_statistics(num_students, names, averages);
  }

  return 0;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

Status read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    handle_error(ERR_INVALID_INPUT);
    clear_input_buffer();
    return ERR_INVALID_INPUT;
  }
  clear_input_buffer();
  return SUCCESS;
}

Status read_double(double *value) {
  if (scanf("%lf", value) != 1) {
    handle_error(ERR_INVALID_INPUT);
    clear_input_buffer();
    return ERR_INVALID_INPUT;
  }
  clear_input_buffer();
  return SUCCESS;
}

void read_string(char *buffer, int max_length) {
  fgets(buffer, max_length, stdin);
  buffer[strcspn(buffer, "\n")] = 0;
}

void handle_error(Status status) {
  switch (status) {
  case ERR_INVALID_COUNT:
    printf("Error: Invalid number of students (1-%d).\n\n", MAX_STUDENTS);
    break;
  case ERR_INVALID_INPUT:
    printf("Error: Invalid input. Try again.\n\n");
    break;
  case SUCCESS:
    break;
  }
}

void calculate_student_average(double grades[], double *average) {
  double sum = 0.0;
  for (int i = 0; i < NUM_GRADES; i++) {
    sum += grades[i];
  }
  *average = sum / NUM_GRADES;
}

void determine_status(double average, char status_out[]) {
  if (average >= EXCELLENT_GRADE) {
    strcpy(status_out, "EXCELLENT");
  } else if (average >= MIN_PASS_GRADE) {
    strcpy(status_out, "PASS");
  } else {
    strcpy(status_out, "FAIL");
  }
}

void calculate_group_statistics(int num_students, double avgs[], GroupStatistics *stats) {
  double group_sum = 0;
  stats->best_student_idx = 0;
  stats->worst_student_idx = 0;
  stats->pass_count = 0;

  for (int i = 0; i < num_students; i++) {
    group_sum += avgs[i];

    if (avgs[i] > avgs[stats->best_student_idx]) {
      stats->best_student_idx = i;
    }
    if (avgs[i] < avgs[stats->worst_student_idx]) {
      stats->worst_student_idx = i;
    }
    if (avgs[i] >= MIN_PASS_GRADE) {
      stats->pass_count++;
    }
  }

  stats->group_average = (num_students > 0) ? (group_sum / num_students) : 0.0;
  stats->pass_rate = (num_students > 0) ? ((double)stats->pass_count * 100.0 / num_students) : 0.0;
}

void sort_indices_by_grade_desc(double avgs[], int indices[], int count) {
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

void run_student_entry(int *num_students, char names[][MAX_NAME_LENGTH],
                       double grades[][NUM_GRADES], double averages[]) {
  printf("Number of students (max %d): ", MAX_STUDENTS);

  if (!read_integer(num_students) || *num_students <= 0 || *num_students > MAX_STUDENTS) {
    handle_error(ERR_INVALID_COUNT);
    *num_students = 0;
    return;
  }

  for (int i = 0; i < *num_students; i++) {
    do {
      printf("Enter student name %d: ", i + 1);
      read_string(names[i], MAX_NAME_LENGTH);
    } while (strlen(names[i]) == 0);

    for (int j = 0; j < NUM_GRADES; j++) {
      double grade;
      do {
        printf("  Enter grade (0-100) %d: ", j + 1);
        if (!read_double(&grade)) {
          continue;
        }
        if (grade < 0 || grade > 100) {
          printf("Error: Grade must be between 0 and 100.\n");
        }
      } while (grade < 0 || grade > 100);

      grades[i][j] = grade;
    }

    calculate_student_average(grades[i], &averages[i]);
  }
}

void show_student_report(int num_students, char names[][MAX_NAME_LENGTH],
                         double grades[][NUM_GRADES], double averages[]) {
  char status[MAX_STATUS_LENGTH];

  printf("\n=== Students ===\n\n");

  for (int i = 0; i < num_students; i++) {
    determine_status(averages[i], status);

    printf("Student %d:\n", i + 1);
    printf("  - Name: %s\n", names[i]);
    printf("  - Grades (%d): ", NUM_GRADES);

    for (int j = 0; j < NUM_GRADES; j++) {
      printf("%.0f ", grades[i][j]);
    }

    printf("\n  - Average: %.2f - %s\n\n", averages[i], status);
  }
}

void show_group_statistics(int num_students, char names[][MAX_NAME_LENGTH], double averages[]) {
  GroupStatistics stats;
  int passed_indices[MAX_STUDENTS];
  int pass_index_count = 0;

  calculate_group_statistics(num_students, averages, &stats);

  printf("\n=== General Statistics ===\n\n");
  printf("Group average: %.2f\n", stats.group_average);
  printf("Best student: %s (%.2f)\n", names[stats.best_student_idx],
         averages[stats.best_student_idx]);
  printf("Worst student: %s (%.2f)\n", names[stats.worst_student_idx],
         averages[stats.worst_student_idx]);
  printf("Pass rate: %.2f%% (%d/%d)\n", stats.pass_rate, stats.pass_count, num_students);

  if (stats.pass_count > 0) {
    for (int i = 0; i < num_students; i++) {
      if (averages[i] >= MIN_PASS_GRADE) {
        passed_indices[pass_index_count++] = i;
      }
    }

    sort_indices_by_grade_desc(averages, passed_indices, stats.pass_count);

    printf("\nStudents who passed:\n");
    for (int i = 0; i < stats.pass_count; i++) {
      int idx = passed_indices[i];
      printf("  %d. %s - %.2f\n", i + 1, names[idx], averages[idx]);
    }
  }
}
