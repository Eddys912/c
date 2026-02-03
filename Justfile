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
error     := red + "ERROR" + reset
info      := yellow + "INFO" + reset
success   := green + "SUCCESS" + reset
exec      := cyan + "EXEC" + reset

default: commands

[no-exit-message]
run file_input="":
  if [ -z "{{file_input}}" ]; then
    echo "{{error}} No file specified"
    echo "{{info}} Usage: just run <file>"
    exit 0
  fi

  if [[ "{{file_input}}" == *"/"* ]] || [[ -f "{{file_input}}" ]]; then
    file_path="{{file_input}}"
  else
    file_path=$(find src -type f -name "{{file_input}}" 2>/dev/null | head -n 1)
    if [[ -z "$file_path" ]]; then
      echo "{{error}} File '{{file_input}}' not found in src/"
      exit 1
    fi
  fi

  if [[ ! -f "$file_path" ]]; then
    echo "{{error}} File '$file_path' not found"
    exit 1
  fi

  if [[ "$file_path" != *.c ]]; then
    echo "{{error}} '$file_path' is not a .c file"
    exit 1
  fi

  mkdir -p files

  {{cc}} {{cflags}} "$file_path" -o {{target}} || {
    echo "{{error}} Compilation failure (gcc)"
    exit 1
  }

  echo "{{exec}} {{cyan}}Executing...{{reset}}"
  ./{{target}} || exit 0

  echo "{{success}} {{green}}Execution finished{{reset}}"
  rm -f {{target}} files/*.bin

[no-exit-message]
list:
  echo "{{info}} Available exercises by module:"

  find src -mindepth 1 -maxdepth 1 -type d 2>/dev/null | sort | while read dir; do
    echo "  {{cyan}}${dir}{{reset}}"

    find "$dir" -maxdepth 1 -type f -name "*.c" 2>/dev/null | sort | while read file; do
      basename "$file"
    done | awk '{printf "    %-40s", $0; if (NR%3==0) print ""}'

    count=$(find "$dir" -maxdepth 1 -type f -name "*.c" | wc -l)
    if [ $((count % 3)) -ne 0 ]; then echo ""; fi
  done

  if [ ! -d "src" ]; then
    echo "  {{error}} Directory src/ not found"
  fi

help:
  @echo "{{info}} Usage:"
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
