#!/bin/bash

YLLW=$(tput setaf 3)
GREEN=$(tput setaf 2)
RESET=$(tput sgr0)

SYSTEM_CALLS=(
	"< infile.txt grep 'town' | sort | uniq -c | wc -w > outfile.txt"
	"< infile.txt cat infile.txt | grep 'Date' | sort | uniq -c > outfile.txt"
	"< infile.txt ps aux | grep '_networkd' | sort | uniq -c  > outfile.txt"
	"< infile.txt /usr/bin/df -h | grep '/System/Volumes/Data' | sort | uniq -c > outfile.txt"
	"< infile.txt du -h | grep 'M' | sort | uniq -c > outfile.txt"
	"< infile.txt grep 'town' | cut -d' ' -f1 | sort > outfile.txt"
	"< infile.txt cat infile.txt | grep 'w' | cut -d' ' -f1 | sort  > outfile.txt"
	"< infile.txt ps aux | grep 'process' | cut -d' ' -f1 | sort > outfile.txt"
	"< infile.txt df -h | grep 'File' | cut -d' ' -f1 > outfile.txt"
	"< infile.txt du -h | grep 'M' | cut -d' ' -f1 | sort > outfile.txt"
	"< infile.txt grep 'town' | head -n 10 | tail -n 5 > outfile.txt"
	"< infile.txt cat infile.txt | /usr/bin/grep 'old' | head -n 10 | tail -n 5 > outfile.txt"
	"< infile.txt ps aux | grep '/usr/sbin/systemstats' | head -n 10 | tail -n 5 > outfile.txt"
	"< infile.txt df -h | grep '%' | head -n 10 | tail -n 1 > outfile.txt"
	"< infile.txt du -h | grep 'M' | head -n 1 | tail -n 5 > outfile.txt"
	"< infile.txt ls -l | grep 'x' | tr '[:lower:]' '[:upper:]' | sort | head -n 1 > outfile.txt"
	"< infile.txt cat infile.txt | grep 'note' | tr '[:lower:]' '[:upper:]' | sort > outfile.txt"
	"< infile.txt ps aux | grep 'root' | tr '[:lower:]' '[:upper:]' | sort | head -n 1 > outfile.txt"
	"< infile.txt grep 'wisdom' | tr '[:lower:]' '[:upper:]' | sort > outfile.txt"
	"< infile.txt du -h | grep 'M' | tr '[:lower:]' '[:upper:]' | head -n 1 > outfile.txt"
	"< infile.txt grep 'town' | sed 's/town/village/g' | tr '[:upper:]' '[:lower:]' > outfile.txt"
	"< infile.txt grep 'town' | sed 's/town/village/g' | unexistant > outfile.txt"
	"< infile.txt grep 'town' | unexistant | tr '[:upper:]' '[:lower:]' > outfile.txt"
	"< unexistant.txt grep 'town' | cut -d' ' -f1 | tr '[:upper:]' '[:lower:]' > outfile.txt"
)

PIPEX_CALLS=(
	'./pipex infile.txt "grep town" "sort" "uniq -c" "wc -w" outfile.txt'
	'./pipex infile.txt "cat infile.txt" "grep 'Date'" "sort" "uniq -c" outfile.txt'
	'./pipex infile.txt "ps -a" "grep '_networkd'" "sort" "uniq -c" outfile.txt'
	'./pipex infile.txt "/usr/bin/df -h" "grep '/System/Volumes/Data'" "sort" "uniq -c" outfile.txt'
)

t_counter=0

for cmd in "${PIPEX_CALLS[@]}"; do
  # Increment the test counter
  ((t_counter++))
  echo -e "${YLLW}Executing Test #$t_counter: $cmd${RESET}\n${GREEN}PIPEX Output:${RESET}"
  eval "$cmd"
  cat outfile.txt
  echo -e ""
  echo "--------------------"
  echo -e ""
done


#t_counter=0

#for cmd in "${SYSTEM_CALLS[@]}"; do
  # Increment the test counter
#  ((t_counter++))
#  echo -e "${YLLW}Executing Test #$t_counter: $cmd${RESET}\n${GREEN}Original Output:${RESET}"
#  eval "$cmd"
#  cat outfile.txt
#  echo -e ""
#  echo "--------------------"
#  echo -e ""
#done
