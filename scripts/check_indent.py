import sys
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('filename')
parser.add_argument('-b', '--bad-only', action='store_true')
args = parser.parse_args()

filename = args.filename
tab = False
space = False
minlength = 0
with open(filename) as f:
    for line in f:
        length = 0
        for i in range(len(line)):
            if line[i] != ' ' and line[i] != '\t':
                if line[i] == '*':
                    break
                length = i
                break
            elif line[i] == ' ':
                space = True
            else:
                tab = True
        if length == 0:
            continue
        if minlength == 0 or length < minlength:
            minlength = length

RED = '\033[0;31m'
NC = '\033[0m'
if tab and space:
    print(f"{RED}{filename}: mix{NC}")
elif tab:
    if not args.bad_only:
        print(f"{filename}: tab")
else:
    if minlength != 0 and minlength != 2:
        print(f"{RED}{filename}: space width {minlength}{NC}")
    else:
        if not args.bad_only:
            print(f"{filename}: space width {minlength}")
