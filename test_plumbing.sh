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
	'./pipex infile.txt "cat infile.txt" "grep '\''Date'\''" "sort" "uniq -c" outfile.txt'
	'./pipex infile.txt "ps -a" "grep _networkd" "sort" "uniq -c" outfile.txt'
	'./pipex infile.txt "df -h" "grep /System/Volumes/Data" "sort" "uniq -c" outfile.txt'
	'./pipex infile.txt "du -h" "grep M" "sort" "uniq -c" outfile.txt'
	'./pipex infile.txt "grep '\''town'\''" "cut -d'\'' '\'' -f1" "sort" outfile.txt'
	'./pipex infile.txt "cat infile.txt" "grep w" "cut -d'\'' '\'' -f1" "sort" outfile.txt'
	'./pipex infile.txt "ps -a" "grep process" "cut -d'\'' '\'' -f1" "sort" outfile.txt'
	'./pipex infile.txt "df -h" "grep File" "cut -d'\'' '\'' -f1" outfile.txt'
	'./pipex infile.txt "du -h" "grep M" "cut -d'\'' '\'' -f1" "sort" outfile.txt'
	'./pipex infile.txt "grep town" "head -n 10" "tail -n 5" outfile.txt'
	'./pipex infile.txt "cat infile.txt" "/usr/bin/grep old" "head -n 10" "tail -n 5" outfile.txt'
	'./pipex infile.txt "ps -a" "grep /usr/sbin/systemstats" "head -n 10" "tail -n 5" outfile.txt'
	'./pipex infile.txt "df -h" "grep %" "head -n 10" "tail -n 1" outfile.txt'
	'./pipex infile.txt "du -h" "grep M" "head -n 1" "tail -n 5" outfile.txt'
	'./pipex infile.txt "ls -l" "grep x" "tr '\''[:lower:]'\'' '\''[:upper:]'\''" "sort" "head -n 1" outfile.txt'
	'./pipex infile.txt "cat infile.txt" "grep note" "tr '\''[:lower:]'\'' '\''[:upper:]'\''" "sort" outfile.txt'
	'./pipex infile.txt "ps -a" "grep root" "tr '\''[:lower:]'\'' '\''[:upper:]'\''" "sort" "head -n 1" outfile.txt'
	'./pipex infile.txt "grep wisdom" "tr '\''[:lower:]'\'' '\''[:upper:]'\''" "sort" outfile.txt'
	'./pipex infile.txt "du -h" "grep M" "tr '\''[:lower:]'\'' '\''[:upper:]'\''" "head -n 1" outfile.txt'
	'./pipex infile.txt "grep town" "sed '\''s/town/village/g'\''" "tr '\''[:upper:]'\'' '\''[:lower:]'\''" outfile.txt'
	'./pipex infile.txt "grep town" "sed '\''s/town/village/g'\''" "unexistant" outfile.txt'
	'./pipex infile.txt "grep town" "unexistant" "tr '\''[:upper:]'\'' '\''[:lower:]'\''" outfile.txt'
	'./pipex unexistant.txt "grep town" "cut -d'\'' '\'' -f1" "tr '\''[:upper:]'\'' '\''[:lower:]'\''" outfile.txt'
)

for ((i = 0; i < ${#PIPEX_CALLS[@]}; i++)); do
    echo -e "${YLLW}Executing Test #$((i+1)):"

    # Display the pipex command
    echo -e "${PIPEX_CALLS[i]}"

    # Display the original system pipe command
    echo -e "${SYSTEM_CALLS[i]${RESET}}"

    # Execute the pipex command and display its output
    echo -e "${GREEN}PIPEX Output:${RESET}"
    eval "${PIPEX_CALLS[i]}"
    cat outfile.txt

    # Execute the original system pipe command and display its output
    echo -e "${GREEN}Original Output:${RESET}"
    eval "${SYSTEM_CALLS[i]}"
    cat outfile.txt

    echo -e ""
    echo -e "--------------------"
    echo -e ""
done
