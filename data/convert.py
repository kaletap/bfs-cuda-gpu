"""
Converts vertices indexed from one to vertices indexed from zero.
"""

import sys

if __name__ == "__main__":
    file = sys.argv[1]
    new_file = sys.argv[2]
    new_lines = []
    with open(file) as f:
        lines = f.readlines()
        new_lines.append(lines[0])
        for line in lines[1:]:
            nums = line.split(" ")
            new_lines.append(" ".join([str(int(n) - 1) for n in nums if n and n != "\n"]) + "\n")
    with open(new_file, "w") as new_f:
        new_f.writelines(new_lines)

    
