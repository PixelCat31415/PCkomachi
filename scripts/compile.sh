#!/usr/bin/env bash

set -e

if [[ ! -f main.tex ]]; then
    echo "Please execute the script at ideograph_advantage/"
    exit 1
fi

BLUE='\033[1;34m'
NC='\033[0m'

printf "${BLUE}Check unused files$NC\n"
scripts/check_usage.sh
printf "${BLUE}Check indentations$NC\n"
scripts/check_indent.sh -b
printf "${BLUE}Process partial hash$NC\n"
scripts/process_hash_all.sh
printf "${BLUE}Compile main.tex...$NC\n"
texfot latexmk -xelatex main.tex --shell-escape
printf "${BLUE}Clean$NC\n"
scripts/process_hash_clear.sh
printf "${BLUE}Done$NC\n"

