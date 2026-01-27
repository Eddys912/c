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
#define FALSE 0
#define MAX_STUDENTS 50
#define MAX_NAME_LENGTH 100
#define NUM_GRADES 5
#define MIN_PASS_GRADE 60.0
#define EXCELLENT_GRADE 90.0
#define MAX_STATUS_LENGTH 20

void clear_input_buffer(void);
int read_integer(int *value);
int read_double(double *value);
void get_status_string(double avg, char status_out[MAX_STATUS_LENGTH]);
void show_students(int num, char names[][MAX_NAME_LENGTH], double grades[][NUM_GRADES],
  double avgs[]);
void sort_indices_by_grade_desc(double avgs[], int indices[], int count);
void process_statistics(int num, char names[][MAX_NAME_LENGTH], double avgs[]);

int main(void) {
  char names[MAX_STUDENTS][MAX_NAME_LENGTH];
  double all_grades[MAX_STUDENTS][NUM_GRADES];
  double averages[MAX_STUDENTS];
  int num_students;

  printf("=== Student Grade System ===\n\n");
  printf("Number of students (max 50): ");

  if (!read_integer(&num_students) || num_students > MAX_STUDENTS || num_students <= 0) {
    printf("Error: Max students is %d\n\n", MAX_STUDENTS);
    return 1;
  }

  for (int i = 0; i < num_students; i++) {
    do {
      printf("Enter student name %d: ", i + 1);
      fgets(names[i], MAX_NAME_LENGTH, stdin);
      names[i][strcspn(names[i], "\n")] = 0;
    } while (strlen(names[i]) == 0);

    double sum = 0;
    for (int j = 0; j < NUM_GRADES; j++) {
      printf("  Enter grade (0-100) %d: ", j + 1);
      double grade;
      if (!read_double(&grade) || grade < 0 || grade > 100) {
        printf("Error: Invalid input. Try again.\n\n");
        j--;
        continue;
      }
      all_grades[i][j] = grade;
      sum += grade;
    }
    averages[i] = sum / NUM_GRADES;
  }

  show_students(num_students, names, all_grades, averages);
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

void get_status_string(double avg, char status_out[MAX_STATUS_LENGTH]) {
  if (avg >= EXCELLENT_GRADE) {
    strcpy(status_out, "EXCELLENT");
  } else if (avg >= MIN_PASS_GRADE) {
    strcpy(status_out, "PASS");
  } else {
    strcpy(status_out, "FAIL");
  }
}

void show_students(int num, char names[][MAX_NAME_LENGTH], double grades[][NUM_GRADES],
                   double avgs[]) {
  char status[20];

  printf("\n=== Students ===\n\n");

  for (int i = 0; i < num; i++) {
    get_status_string(avgs[i], status);

    printf("Student %d:\n", i + 1);
    printf("  - Name: %s\n", names[i]);
    printf("  - Grades (5): ");

    for (int j = 0; j < NUM_GRADES; j++) {
      printf("%.0f ", grades[i][j]);
    }

    printf("\n  - Average: %.2f - %s\n\n", avgs[i], status);
  }
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

  printf("\n=== General Statistics ===\n\n");
  printf("Group average: %.2f\n", group_sum / num);
  printf("Best student: %s (%.2f)\n", names[best_idx], avgs[best_idx]);
  printf("Worst student: %s (%.2f)\n", names[worst_idx], avgs[worst_idx]);
  printf("Pass rate: %.2f%% (%d/%d)\n", (pass_count * 100.0) / num, pass_count, num);

  if (pass_count > 0) {
    printf("\nStudents who passed:\n");
    sort_indices_by_grade_desc(avgs, passed_indices, pass_count);

    for (int i = 0; i < pass_count; i++) {
      int idx = passed_indices[i];
      printf("  %d. %s - %.2f\n", i + 1, names[idx], avgs[idx]);
    }
  }
}
