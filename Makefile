# Makefile for c-systems-fundamentals
# Documentation: https://www.gnu.org/software/make/manual/make.html
# Usage: make run src/path/<file.pl>

# Compiler and Flags
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -pthread
TARGET  = exercise

# Colors for the terminal
RED     = \033[0;31m
GREEN   = \033[0;32m
CYAN    = \033[0;36m
NC      = \033[0m

.PHONY: run help

run:
	@if [ -z "$(file)" ]; then \
		printf "$(RED)Error: No file specified.$(NC)\n"; \
		printf "$(GREEN)Usage: make run file=<path/to/file.c>$(NC)\n"; \
		exit 1; \
	fi
	@if [ ! -f "$(file)" ]; then \
		printf "$(RED)Error: File '$(file)' not found.$(NC)\n"; \
		exit 1; \
	fi

	@case "$(file)" in \
		*.c) ;; \
		*) printf "$(RED)Error: '$(file)' is not a .c file.$(NC)\n"; exit 1 ;; \
	esac

	@mkdir -p files
	@$(CC) $(CFLAGS) "$(file)" -o $(TARGET) || \
		(printf "$(RED)Error: Compilation failure (gcc)$(NC)\n" && exit 1)

	@printf "$(CYAN)----- Executing C: %s -----$(NC)\n" "$(file)"
	@./$(TARGET)

	@rm -f $(TARGET) files/*.bin

help:
	@printf "$(GREEN)Usage:$(NC) make run file=src/path/<file.c>\n"
	@printf "$(GREEN)Example:$(NC) $(CYAN)make run file=src/01_fundamentals/01_multi_calculator.c$(NC)\n"
