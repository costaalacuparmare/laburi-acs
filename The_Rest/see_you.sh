#!/bin/bash
line=0
lineog=$(tput lines)
col=$(tput cols)
str="See you, space cowboy..."
color="\\033[3;97;40m"
norm="\\033[0m"
line=0
while [[ true ]]
do
line=0
while [[ line -le lineog ]]
do
	echo -e "$color\x1B[K"
	cl=$(($RANDOM % $(($col/4))))
	while [[ cl -lt col ]]
	do
		tput cup "$line" "$(($cl))"
		echo -e "*"
		cl=$(($cl + $RANDOM % $(($col/4))))
	done
	line="$(($line + 1))"
done
done
echo -e "\\033[40m\x1B[K"
tput cup $(tput lines) $(($(tput cols) - 24))
printf "$color$str$norm"
tput cup $(tput lines)  0
