CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread
TARGET = exercise

CYAN = \033[0;36m
NC = \033[0m

run:
	@$(CC) $(CFLAGS) $(filter-out $@,$(MAKECMDGOALS)).c -o $(TARGET)
	@printf "$(CYAN)----- Executing: %s -----$(NC)\n" "$(filter-out $@,$(MAKECMDGOALS))"
	@./$(TARGET)
	@rm -f $(TARGET)

%:
	@:
