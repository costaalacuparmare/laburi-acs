#!/bin/bash

rm -rf *.hlt

if [ "$#" -lt 4 ]; then
    echo "Usage: $0 <map_size1> <map_size2> <seed> <num_players> [<bot_paths>]"
    exit 1
fi

map_size1=$1
map_size2=$2
seed=$3
num_players=$4
browser=$5

if [ "$num_players" -gt 1 ]; then
    shift 4
    bots=("$@")

    ./utils/halite -t -d "$map_size1 $map_size2" -s "$seed" "python3 MyBot.py" "${bots[@]}"
    rm *.log
else
    ./utils/halite -t -d "$map_size1 $map_size2" -s "$seed" -n "$num_players" "python3 MyBot.py"
fi

file_name=$(find . -maxdepth 1 -type f -name "*.hlt" -print -quit)

mv "$file_name" utils

cd utils || exit

python3 vis.py "$browser" "$file_name"

rm "$file_name"

cd ..

