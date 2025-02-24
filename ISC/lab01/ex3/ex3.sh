#!/bin/bash

files=$(find . -type f -size 987c)

for file in $files; do
	cat "$file"
	echo
done
