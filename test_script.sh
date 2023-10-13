#!/bin/bash

# Define your pipex executable path
PIPEX=./pipex

# Define input and output files
INFILE=infile.txt
OUTFILE=outfile.txt

# Define test commands
COMMANDS=(
    "cat"
    "grep -i keyword"
    "ls -l"
    "nonexistentcommand"
    "/usr/bin/ls -l"
)

# Function to run pipex command and capture execution time
run_pipex() {
    echo "Running pipex with command: $1"
    start_time=$(date +%s%N)
    $PIPEX $INFILE "$1" "$OUTFILE"
    end_time=$(date +%s%N)
    elapsed_time=$(( (end_time - start_time) / 1000000 ))
    echo "Time taken by pipex: $elapsed_time ms"
}

# Function to run shell command and capture execution time
run_shell_command() {
    echo "Running shell command: $1"
    start_time=$(date +%s%N)
    eval "$1 < $INFILE > $OUTFILE"
    end_time=$(date +%s%N)
    elapsed_time=$(( (end_time - start_time) / 1000000 ))
    echo "Time taken by shell command: $elapsed_time ms"
}

# Run tests for each command
for cmd in "${COMMANDS[@]}"; do
    run_pipex "$cmd"
    run_shell_command "$cmd"
done
