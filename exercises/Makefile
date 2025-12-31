CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread
TARGET = exercise

exec:
	@$(CC) $(CFLAGS) $(filter-out $@,$(MAKECMDGOALS)).c -o $(TARGET)
	@./$(TARGET)
	@rm -f $(TARGET)

%:
	@:
