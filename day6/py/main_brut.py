#part one = 3316275
#part two = 27102791
from functools import reduce
from time import perf_counter_ns

def line2nums(line):
    line = line.split(':')[1].strip(' ').strip("\n").split(' ')
    line = list(filter(lambda x: (x != ''), line))
    return list(map(lambda x: (int(x)), line))

def line2num(line):
    line = line.split(':')[1].strip(' ').strip("\n").split(' ')
    line = list(filter(lambda x: (x != ''), line))
    return int(reduce(lambda x, y: (x + y), line, ""))

def part1(lines):
    timenums = line2nums(lines[0])
    distnums = line2nums(lines[1])

    res = 1
    for n in range(len(timenums)):
        dist = distnums[n]
        low = 0
        for i in range(timenums[n] + 1):
            r = i * (timenums[n] - i)
            if r > dist:
                low = i
                break
        top = 0
        for i in reversed(range(timenums[n] + 1)):
            r = i * (timenums[n] - i)
            if r > dist:
                top = i
                break
        res *= top - low + 1
    return res

def part2(lines):
    timenum = line2num(lines[0])
    distnum = line2num(lines[1])

    low = 0
    for i in range(timenum + 1):
        r = i * (timenum - i)
        if r > distnum:
            low = i
            break
    top = 0
    for i in reversed(range(timenum + 1)):
        r = i * (timenum - i)
        if r > distnum:
            top = i
            break
    return top - low + 1

lines = open("../input.txt", "r").readlines()
start = perf_counter_ns()
print("part one = ", part1(lines))
print("time[us] = ", (perf_counter_ns() - start) // 1000)
start = perf_counter_ns()
print("part two = ", part2(lines))
print("time[us] = ", (perf_counter_ns() - start) // 1000)