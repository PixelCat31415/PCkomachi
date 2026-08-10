#!/usr/bin/env bash

if [[ ! -f main.tex ]]; then
    echo "Please execute the script at ideograph_advantage/"
    exit 1
fi

PATTERN='.*.cpp.auto'
find . -regextype posix-egrep -regex "$PATTERN" | while read file; do
    rm "$file"
done
