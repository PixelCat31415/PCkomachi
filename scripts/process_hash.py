import sys
import subprocess
import argparse

def get_hash(content):
    p = subprocess.run("cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6", shell=True,
            capture_output=True, input=content.encode())
    return p.stdout.decode().strip()


parser = argparse.ArgumentParser()
parser.add_argument('filename')
args = parser.parse_args()
filename = args.filename

with open(filename) as f:
    lines = []
    for line in f:
        lines.append(line)
    output = []
    for i in range(len(lines)):
        line = lines[i]
        if line.strip().endswith("// SCOPE HASH"):
            cnt = 1
            content = [ line ]
            for j in range(i + 1, len(lines)):
                content.append(lines[j])
                for c in lines[j]:
                    if c == '{':
                        cnt += 1
                    if c == '}':
                        cnt -= 1
                    if cnt == 0:
                        break
                if cnt == 0:
                    break
            if cnt != 0:
                print(f"Error: the scope since line {i + 1} is not closed")
                exit(1)
            content = ''.join(content)
            tmp = line.split('// ')
            tmp[-1] = get_hash(content) + '\n'
            output.append('// '.join(tmp))
        elif line.strip() == "// == PART HASH ==":
            content = [ line ]
            for j in range(i + 1, len(lines)):
                if (lines[j].strip() == "// == PART HASH =="):
                    break
                content.append(lines[j])
            content = ''.join(content)
            output.append(f"// == {get_hash(content)} ==\n")
        else:
            output.append(line)
    print(''.join(output))




