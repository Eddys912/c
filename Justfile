# Justfile for c-systems-fundamentals
# Documentation: https://just.systems/man/en/

set shell := ["bash", "-uc"]

# Compiler and Flags
cc      := "gcc"
cflags  := "-Wall -Wextra -std=c99 -pthread"
target  := "exercise"

# Use tput for portable terminal colors
red     := `tput setaf 1 2>/dev/null || echo ""`
green   := `tput setaf 2 2>/dev/null || echo ""`
yellow  := `tput setaf 3 2>/dev/null || echo ""`
cyan    := `tput setaf 6 2>/dev/null || echo ""`
gray    := `tput setaf 8 2>/dev/null || echo ""`
reset   := `tput sgr0 2>/dev/null || echo ""`

error   := red + "ERROR" + reset
info    := yellow + "INFO" + reset
success := green + "SUCCESS" + reset
exec    := cyan + "EXEC" + reset

default: commands

# Run C file with smart file resolution
[no-exit-message]
run file_input:
  #!/usr/bin/env bash
  set -euo pipefail

  if [[ "{{file_input}}" == *"/"* ]] || [[ -f "{{file_input}}" ]]; then
    file_path="{{file_input}}"
  else
    found=$(find src -type f -name "{{file_input}}" 2>/dev/null | head -n 1)
    if [[ -z "$found" ]]; then
      echo "{{error}} file '{{file_input}}' not found in src/"
      echo "{{info}} use full path or just the filename"
      exit 1
    fi
    file_path="$found"
  fi

  if [[ ! -f "$file_path" ]]; then
    echo "{{error}} {{red}}Error: File '$file_path' not found.{{reset}}"
    exit 1
  fi

  if [[ "$file_path" != *.c ]]; then
    echo "{{error}} {{red}}Error: '$file_path' is not a .c file.{{reset}}"
    exit 1
  fi

  mkdir -p files

  echo "{{exec}} {{cyan}}Compiling: $file_path{{reset}}"
  {{cc}} {{cflags}} "$file_path" -o {{target}} || {
    echo "{{error}} {{red}}Error: Compilation failure (gcc){{reset}}"
    exit 1
  }

  echo "{{exec}} {{cyan}}Executing...{{reset}}"
  ./{{target}}

  echo "{{success}} {{green}}Success: Execution finished.{{reset}}"
  rm -f {{target}} files/*.bin

[no-exit-message]
list:
  #!/usr/bin/env bash
  set -euo pipefail

  echo "{{info}} Available exercises:"

  find src -type f -name "*.c" 2>/dev/null | sort | awk -F'/' '
  BEGIN {
    prev_dir = ""
  }
  {
    # Extract directory path (everything except filename)
    dir = $0
    sub(/\/[^\/]+$/, "", dir)

    # Extract filename
    filename = $NF

    # If directory changed, print new header
    if (dir != prev_dir) {
      if (prev_dir != "") print ""
      printf "  \033[1;36m%s/\033[0m\n", dir
      prev_dir = dir
    }

    # Print filename indented
    printf "    • %s\n", filename
  }
  END {
    if (prev_dir == "") {
      print "  \033[0;31mNo exercises found in src/\033[0m"
    }
  }
  '

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
