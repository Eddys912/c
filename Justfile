# Justfile for c-systems-fundamentals
# Documentation: https://just.systems/man/en/

# Use bash shell with strict error handling
set shell := ["bash", "-euo", "pipefail", "-c"]

# Compiler and Flags
CC        := "gcc"
CFLAGS    := "-Wall -Wextra -std=c99 -pthread"
TARGET    := "exercise"

# Directories
SRC_DIR   := "src"
FILES_DIR := "files"

# Colors using ANSI escape codes
RED       := '\033[0;31m'
GREEN     := '\033[0;32m'
YELLOW    := '\033[0;33m'
CYAN      := '\033[0;36m'
GRAY      := '\033[0;90m'
END     := '\033[0m'

# Status Prefixes
ERROR     := RED    + "ERROR  " + END
INFO      := YELLOW + "INFO   " + END
SUCCESS   := GREEN  + "SUCCESS" + END
EXEC      := CYAN   + "EXEC   " + END

default: commands

[no-exit-message]
run file_input="":
  #!/usr/bin/env bash
  # Validate input parameter
  if [[ -z "{{file_input}}" ]]; then
    echo -e "{{ERROR}} No file specified"
    echo -e "{{INFO}} Usage: just run <file>"
    exit 1
  fi

  # Validate src directory exists
  if [[ ! -d "{{SRC_DIR}}" ]]; then
    echo -e "{{ERROR}} Directory '{{SRC_DIR}}/' does not exist"
    exit 1
  fi

  # Determine full file path
  if [[ "{{file_input}}" == *"/"* ]]; then
    file_path="{{file_input}}"
  else
    file_path=$(find {{SRC_DIR}} -type f -name "{{file_input}}" -print -quit)
    if [[ -z "$file_path" ]]; then
      echo -e "{{ERROR}} File '{{file_input}}' not found"
      echo -e "{{INFO}} Run 'just list' to see available exercises"
      exit 1
    fi
  fi

    # Validate file exists and has .c extension
    if [[ ! -f "$file_path" ]]; then
      echo -e "{{ERROR}} File '$file_path' does not exist"
      exit 1
    fi

    if [[ "$file_path" != *.c ]]; then
      echo -e "{{ERROR}} File '$file_path' is not a .c file"
      exit 1
    fi

    # Create output directory for file operations
    mkdir -p {{FILES_DIR}}

    # Compile the exercise
    if ! {{CC}} {{CFLAGS}} "$file_path" -o {{TARGET}} 2>&1; then
      echo -e "{{ERROR}} Compilation failed: '$file_path'"
      exit 1
    fi

    # Execute the compiled program
    echo -e "{{EXEC}} Executing '$file_path'"
    ./{{TARGET}} || true

    echo -e "{{SUCCESS}} Execution finished"

    # Clean up generated files
    rm -f {{TARGET}} {{FILES_DIR}}/*.bin

[no-exit-message]
list:
  #!/usr/bin/env bash
  if [[ ! -d "{{SRC_DIR}}" ]]; then
    echo -e "{{ERROR}} Directory '{{SRC_DIR}}/' does not exist"
    exit 1
  fi

  modules=$(find {{SRC_DIR}} -mindepth 1 -maxdepth 1 -type d | sort)
  if [[ -z "$modules" ]]; then
    echo -e "{{ERROR}} No modules found inside '{{SRC_DIR}}/' "
    echo -e "{{INFO}} Expected structure: {{SRC_DIR}}/<module>/<exercise>.c"
    exit 1
  fi

  echo -e "{{INFO}} Available exercises by module:\n"

  while IFS= read -r dir; do
    module_name=$(basename "$dir")
    echo -e "  {{CYAN}}${module_name}/{{END}}"

    exercises=$(find "$dir" -maxdepth 1 -type f -name "*.c" | sort)

    if [[ -z "$exercises" ]]; then
      echo -e "    {{GRAY}}(empty){{END}}\n"
      continue
    fi

    # Format exercises in 3 columns for better readability
    echo "$exercises" | while IFS= read -r file; do
      basename "$file"
    done | awk '{printf "    %-25s", $0; if (NR%4==0) print ""}'

    # Add newline if last row is incomplete
    count=$(echo "$exercises" | wc -l)
    if [[ $((count % 4)) -ne 0 ]]; then echo ""; fi

    echo ""
  done <<< "$modules"

[no-exit-message]
check:
  #!/usr/bin/env bash
  if [[ ! -d "{{SRC_DIR}}" ]]; then
    echo -e "{{ERROR}} Directory '{{SRC_DIR}}/' does not exist"
    exit 1
  fi

  exercises=$(find {{SRC_DIR}} -type f -name "*.c")
  total=$(echo "$exercises" | wc -l)

  if [[ $total -eq 0 ]]; then
    echo -e "{{ERROR}} No exercises found"
    exit 1
  fi

  passed=0
  failed=0
  failed_files=()

  echo -e "{{INFO}} Checking $total exercises ..."

  # Check each exercise
  while IFS= read -r file; do
    if {{CC}} {{CFLAGS}} -fsyntax-only "$file" 2>/dev/null; then
      ((passed++))
    else
      ((failed++))
      failed_files+=("$file")
    fi
  done <<< "$exercises"

  # Show results
  if [[ $failed -eq 0 ]]; then
    echo -e "{{SUCCESS}} All exercises compiled successfully!"
    echo -e "{{INFO}} Results: " \
            "{{GREEN}}$passed passed{{END}}, {{RED}}$failed failed{{END}}"
  else
    echo -e "{{ERROR}} Some exercises failed to compile:"
    for file in "${failed_files[@]}"; do
      echo -e "  {{RED}} -> {{END}} $file"
    done
    echo -e "{{INFO}} Results: " \
            "{{GREEN}}$passed passed{{END}}, {{RED}}$failed failed{{END}}"
    exit 1
  fi

[no-exit-message]
help:
  @echo -e "{{INFO}} Usage:"
  @echo -e "{{GRAY}}  just run <file> {{END}}"
  @echo -e "{{INFO}} Examples:"
  @echo -e "{{GRAY}}  just run 01_multi_calculator.c {{END}}"
  @echo -e "{{GRAY}}  just run src/01_fundamentals/01_multi_calculator.c {{END}}"
  @echo -e "{{INFO}} Tip:"
  @echo -e "{{GRAY}}  Use TAB for path autocompletion {{END}}"

[no-exit-message]
commands:
  @echo -e "{{INFO}} Available commands:"
  @echo -e "{{GRAY}}  just run <file> {{END}}"
  @echo -e "{{GRAY}}  just list       {{END}}"
  @echo -e "{{GRAY}}  just check      {{END}}"
  @echo -e "{{GRAY}}  just help       {{END}}"
