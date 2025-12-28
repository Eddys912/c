#include <stdio.h>
#include <string.h>

#define FILE_PATH "files/sensor.bin"

typedef struct {
  int id;
  float threshold;
  char status;
} SensorConfig;

void clear_input_buffer();
int read_user_input(SensorConfig *sensor);
int validate_status(char status);
FILE *open_file_safe(const char *filepath, const char *mode);
int close_file_safe(FILE *file);
int write_sensor_to_file(const SensorConfig *sensor, const char *filepath);
int read_sensor_from_file(SensorConfig *sensor, const char *filepath);
void display_sensor(const SensorConfig *sensor);

int main() {
  SensorConfig sensor;

  printf("=== Binary Files ===\n\n");

  if (read_user_input(&sensor) != 0) {
    return 1;
  }

  printf("\nWriting data to binary file...\n");
  if (write_sensor_to_file(&sensor, FILE_PATH) != 0) {
    return 1;
  }
  printf("Data written successfully.\n");

  printf("\nReading data from binary file...\n");
  memset(&sensor, 0, sizeof(SensorConfig));
  if (read_sensor_from_file(&sensor, FILE_PATH) != 0) {
    return 1;
  }

  display_sensor(&sensor);

  return 0;
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int validate_status(char status) {
  if (status != 'A' && status != 'I') {
    fprintf(stderr, "Error: Status must be 'A' (Active) or 'I' (Inactive).\n");
    return 1;
  }
  return 0;
}

int read_user_input(SensorConfig *sensor) {
  int id;
  float threshold;
  char status;

  printf("Enter sensor ID: ");
  if (scanf("%d", &id) != 1) {
    fprintf(stderr, "Error: Invalid ID input.\n");
    return 1;
  }
  clear_input_buffer();

  printf("Enter threshold: ");
  if (scanf("%f", &threshold) != 1) {
    fprintf(stderr, "Error: Invalid threshold input.\n");
    return 1;
  }
  clear_input_buffer();

  printf("Enter status (A/I): ");
  if (scanf("%c", &status) != 1) {
    fprintf(stderr, "Error: Invalid status input.\n");
    return 1;
  }
  clear_input_buffer();

  if (validate_status(status) != 0) {
    return 1;
  }

  sensor->id = id;
  sensor->threshold = threshold;
  sensor->status = status;

  return 0;
}

FILE *open_file_safe(const char *filepath, const char *mode) {
  FILE *file = fopen(filepath, mode);

  if (file == NULL) {
    perror("Error opening file");
  }

  return file;
}

int close_file_safe(FILE *file) {
  if (fclose(file) != 0) {
    perror("Error closing file");
    return 1;
  }
  return 0;
}

int write_sensor_to_file(const SensorConfig *sensor, const char *filepath) {
  FILE *file = open_file_safe(filepath, "wb");

  if (file == NULL) {
    return 1;
  }

  size_t written = fwrite(sensor, sizeof(SensorConfig), 1, file);
  if (written != 1) {
    fprintf(stderr, "Error: Failed to write sensor data to file.\n");
    close_file_safe(file);
    return 1;
  }

  return close_file_safe(file);
}

int read_sensor_from_file(SensorConfig *sensor, const char *filepath) {
  FILE *file = open_file_safe(filepath, "rb");

  if (file == NULL) {
    return 1;
  }

  size_t read = fread(sensor, sizeof(SensorConfig), 1, file);
  if (read != 1) {
    if (feof(file)) {
      fprintf(stderr, "Error: Unexpected end of file.\n");
    } else {
      fprintf(stderr, "Error: Failed to read sensor data from file.\n");
    }
    close_file_safe(file);
    return 1;
  }

  return close_file_safe(file);
}

void display_sensor(const SensorConfig *sensor) {
  printf("\nSensor configuration:\n");
  printf("  %-10s %d\n", "ID:", sensor->id);
  printf("  %-10s %.2f\n", "Threshold:", sensor->threshold);
  printf("  %-10s %c (%s)\n", "Status:", sensor->status,
         sensor->status == 'A' ? "Active" : "Inactive");
}
