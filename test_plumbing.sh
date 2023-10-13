#!/bin/bash

WHAT=$(tput setaf 3)
GREEN=$(tput setaf 2)   # Green text
RESET=$(tput sgr0)      # Reset to default text color

SYSTEM_CALLS=(
"< infile.txt grep 'town' | sort | uniq -c | wc -w > outfile.txt"
"< infile.txt cat infile.txt | grep 'Date' | sort | uniq -c > outfile.txt"
"< infile.txt ps aux | grep '_networkd' | sort | uniq -c  > outfile.txt"
"< infile.txt df -h | grep '/System/Volumes/Data' | sort | uniq -c > outfile.txt"
"< infile.txt du -h | grep 'M' | sort | uniq -c > outfile.txt"
"< infile.txt grep 'town' | cut -d' ' -f1 | sort > outfile.txt"
"< infile.txt cat infile.txt | grep 'w' | cut -d' ' -f1 | sort  > outfile.txt"
"< infile.txt ps aux | grep 'process' | cut -d' ' -f1 | sort > outfile.txt"
"< infile.txt df -h | grep 'File' | cut -d' ' -f1 > outfile.txt"
"< infile.txt du -h | grep 'M' | cut -d' ' -f1 | sort > outfile.txt"
"< infile.txt grep 'town' | head -n 10 | tail -n 5 > outfile.txt"
"< infile.txt cat infile.txt | grep 'old' | head -n 10 | tail -n 5 > outfile.txt"
"< infile.txt ps aux | grep '/usr/sbin/systemstats' | head -n 10 | tail -n 5 > outfile.txt"
"< infile.txt df -h | grep '%' | head -n 10 | tail -n 1 > outfile.txt"
"< infile.txt du -h | grep 'M' | head -n 1 | tail -n 5 > outfile.txt"
"< infile.txt ls -l | grep 'x' | tr '[:lower:]' '[:upper:]' | sort | head -n 1 > outfile.txt"
"< infile.txt cat infile.txt | grep 'note' | tr '[:lower:]' '[:upper:]' | sort > outfile.txt"
"< infile.txt ps aux | grep 'root' | tr '[:lower:]' '[:upper:]' | sort | head -n 1 > outfile.txt"
"< infile.txt grep 'wisdom' | tr '[:lower:]' '[:upper:]' | sort > outfile.txt"
"< infile.txt du -h | grep 'M' | tr '[:lower:]' '[:upper:]' | head -n 1 > outfile.txt"
"< infile.txt grep 'town' | sed 's/town/village/g' | tr '[:upper:]' '[:lower:]' > outfile.txt"

)

t_counter=0

for cmd in "${SYSTEM_CALLS[@]}"; do
  # Increment the test counter
  ((t_counter++))
  echo -e "${WHAT}Executing Test #$t_counter: $cmd${RESET}"
  echo -e ""
  eval "$cmd"
  echo -e "${GREEN}Original Output:${RESET}"
  cat outfile.txt
  echo -e ""
  echo "--------------------"
  echo -e ""
done
