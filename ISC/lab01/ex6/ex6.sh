#!/bin/bash

binwalk -e 06-Idea.jpg
dd if=06-Idea.jpg of=archive.7z bs=1 skip=33519
7z x archive.7z
feh flag4.jpg
