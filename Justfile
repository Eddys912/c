# Justfile for c-systems-fundamentals
# Documentation: https://just.systems/man/en/

set shell := ["bash", "-uc"]

# Compiler and Flags
cc        := "gcc"
cflags    := "-Wall -Wextra -std=c99 -pthread"
target    := "exercise"

# Colors for the terminal
red       := `tput setaf 1 2>/dev/null || echo ''`
green     := `tput setaf 2 2>/dev/null || echo ''`
yellow    := `tput setaf 3 2>/dev/null || echo ''`
cyan      := `tput setaf 6 2>/dev/null || echo ''`
gray      := `tput setaf 8 2>/dev/null || echo ''`
reset     := `tput sgr0 2>/dev/null || echo ''`

# Status Prefixes
error     := red    + "ERROR  " + reset
info      := yellow + "INFO   " + reset
success   := green  + "SUCCESS" + reset
exec      := cyan   + "EXEC   " + reset

default: commands

[no-exit-message]
run file_input="":
  #!/usr/bin/env bash
  set -euo pipefail
  trap 'exit 0' SIGINT

  if [ -z "{{file_input}}" ]; then
    echo "{{error}} No file specified"
    echo "{{info}} Usage: just run <file>"
    exit 1
  fi

  if [ ! -d "src" ]; then
    echo "{{error}} Directory 'src/' does not exist"
    exit 1
  fi

  total_exercises=$(find src -mindepth 2 -maxdepth 2 -type f -name "*.c" | wc -l)
  if [ "$total_exercises" -eq 0 ]; then
    echo "{{error}} No exercises found inside 'src/'"
    echo "{{info}} Expected structure: src/<module>/<exercise>.c"
    exit 1
  fi

  if [[ "{{file_input}}" == *"/"* ]]; then
    file_path="{{file_input}}"
  else
    file_path=$(find src -type f -name "{{file_input}}" | head -n 1)
    if [ -z "$file_path" ]; then
      echo "{{error}} File '{{file_input}}' not found"
      echo "{{info}} Run 'just list' to see available exercises"
      exit 1
    fi
  fi

  if [ ! -f "$file_path" ]; then
    echo "{{error}} File '$file_path' does not exist"
    exit 1
  fi

  if [[ "$file_path" != *.c ]]; then
    echo "{{error}} File '$file_path' is not a .c file"
    exit 1
  fi

  mkdir -p files

  if ! {{cc}} {{cflags}} "$file_path" -o {{target}} 2>&1; then
    echo "{{error}} Compilation failed: '$file_path'"
    exit 1
  fi

  echo "{{exec}} Executing '$file_path'"
  ./{{target}} || true

  echo "{{success}} Execution finished"

  rm -f {{target}} files/*.bin

[no-exit-message]
list:
  #!/usr/bin/env bash

  if [ ! -d "src" ]; then
    echo "{{error}} Directory 'src/' does not exist"
    exit 1
  fi

  modules=$(find src -mindepth 1 -maxdepth 1 -type d | sort)
  if [ -z "$modules" ]; then
    echo "{{error}} No modules found inside 'src/'"
    echo "{{info}} Expected structure: src/<module>/<exercise>.c"
    exit 1
  fi

  echo "{{info}} Available exercises by module:"

  while IFS= read -r dir; do
    echo "  {{cyan}}${dir}/{{reset}}"

    exercises=$(find "$dir" -maxdepth 1 -type f -name "*.c" | sort)

    if [ -z "$exercises" ]; then
      echo "    {{gray}}(empty){{reset}}"
      continue
    fi

    echo "$exercises" | while IFS= read -r file; do
      basename "$file"
    done | awk '{printf "    %-40s", $0; if (NR%3==0) print ""}'

    count=$(echo "$exercises" | wc -l)
    if [ $((count % 3)) -ne 0 ]; then echo ""; fi

  done <<< "$modules"

help:
  @echo "{{info}} Usage:"
  @echo "{{gray}}  just list {{reset}}"
  @echo "{{gray}}  just run <file> {{reset}}"
  @echo "{{info}} Examples:"
  @echo "{{gray}}  just run 01_multi_calculator.c {{reset}}"
  @echo "{{gray}}  just run src/01_fundamentals/01_multi_calculator.c {{reset}}"
  @echo "{{info}} Tip:"
  @echo "{{gray}}  use TAB for path autocompletion {{reset}}"

commands:
  @echo "{{info}} Available commands:"
  @echo "{{gray}}  just run <file> {{reset}}"
  @echo "{{gray}}  just list {{reset}}"
  @echo "{{gray}}  just help {{reset}}"
