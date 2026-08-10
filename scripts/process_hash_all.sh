#!/usr/bin/env bash

if [[ ! -f main.tex ]]; then
    echo "Please execute the script at ideograph_advantage/"
    exit 1
fi

PATTERN='.*.cpp'
find . -regextype posix-egrep -regex "$PATTERN" | while read file; do
    python scripts/process_hash.py "$file" > "$file.auto"
done
