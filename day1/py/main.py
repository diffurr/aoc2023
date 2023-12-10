def firstlast(s):
    for ch in s:
        if ch.isnumeric():
            first = ord(ch) - 0x30
            break
    for ch in reversed(s):
        if ch.isnumeric():
            last = ord(ch) - 0x30
            break
    return (first, last)            
#/def

def findrepl(s):
    digits = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
    repls = ["1", "2", "3", "4", "5", "6", "7", "8", "9"]
    for idx, digit in enumerate(digits):
        pos = s.find(digit)
        if pos >= 0:
            temp = list(s)
            temp[pos + 1] = repls[idx]
            s = "".join(temp)
    for idx, digit in enumerate(digits):
        pos = s.rfind(digit)
        if pos >= 0:
            temp = list(s)
            temp[pos + 1] = repls[idx]
            s = "".join(temp)
    return s
#/def

lines = open("../input.txt", "r").readlines()

#Part One
sum = 0
for line in lines:
    res = firstlast(line)
    sum += res[0] * 10 + res[1]
print("part one = ", sum)

#Part Two
sum = 0
for line in lines:
    newline = findrepl(line)
    res = firstlast(newline)
    sum += res[0] * 10 + res[1]
print("part two = ", sum)