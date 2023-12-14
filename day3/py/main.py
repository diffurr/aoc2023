from time import time

def isDig(ch):
    return (ch > 47) and (ch < 58)

def isSym(ch):
    return ((ch > 32) and (ch < 46)) or ((ch > 57) and (ch < 65)) or ch == 47

def isGear(ch):
    return ch == 42

class MyInput:
    def __init__(self, lines):
        self.barray = bytearray()
        self.span = len(lines[0]) + 2
        for line in lines:
            self.barray.extend(b'.')
            self.barray.extend(map(ord, line))
            self.barray.extend(b'.')
        self.barray.extend(map(ord, self.span * '.'))

    def __getitem__(self, index):
        return self.barray[index]

    def __len__(self):
        return len(self.barray)

    def __getxy(self, x, y):
        return self.barray[y*self.span + x]

    def checkSym(self, index):
        y = index // self.span
        x = index % self.span
        for comb in [(0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1)]:
            if (isSym(self.__getxy(x + comb[0], y + comb[1]))):
                return True
        return False

    def checkGear(self, index):
        y = index // self.span
        x = index % self.span
        for comb in [(0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1)]:
            if (isGear(self.__getxy(x + comb[0], y + comb[1]))):
                return (y + comb[1]) * self.span + x + comb[0]
        return -1

def checkAndSum(input):
    nums = []
    numstr = []
    flag = False
    for i in range(len(input)):
        if isDig(input[i]):
            numstr.append(chr(input[i]))
            flag = True if flag else input.checkSym(i)
        elif len(numstr) > 0 and flag:
            nums.append(int(''.join(numstr)))
            numstr.clear()
            flag = False
        elif len(numstr) > 0:
            numstr.clear()
    
    return sum(nums)

def appendKey(dict, key, val):
    if key not in dict:
        dict[key] = list()
    dict[key].append(val)
    return dict

def findGear(input):
    gears = {}
    numstr = []
    gearid = -1
    for i in range(len(input)):
        if isDig(input[i]):
            numstr.append(chr(input[i]))
            gearid = gearid if (gearid >= 0) else input.checkGear(i)
        elif len(numstr) > 0 and gearid >= 0:
            gears = appendKey(gears, gearid, int(''.join(numstr)))
            numstr.clear()
            gearid = -1
        elif len(numstr) > 0:
            numstr.clear()

    res = 0
    for value in gears.values():
        if len(value) == 2:
            res += value[0] * value[1]
    return res

input = \
"""467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598.."""
lines = open("../input.txt", "r").readlines()
myinput = MyInput(lines)

#Part One
start = time()
print("part one =", checkAndSum(myinput))
ms = round((time() - start) * 1000)
print("time[ms] =", ms)

#Part Two
start = time()
print("part two =", findGear(myinput))
ms = round((time() - start) * 1000)
print("time[ms] =", ms)