#algebraic solution from reddit u/themanushiya
from functools import reduce
from time import perf_counter_ns
from math import sqrt, ceil, floor

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
        t = timenums[n]
        d = distnums[n]
        low = (t - sqrt((t * t) - 4 * d)) / 2
        low = ceil(low) if low % 1 else low + 1
        top = (t + sqrt((t * t) - 4 * d)) / 2
        top = floor(top) if top % 1 else top - 1
        res *= top - low + 1
    return res

def part2(lines):
    t = line2num(lines[0])
    d = line2num(lines[1])
    low = (t - sqrt((t * t) - 4 * d)) / 2
    low = ceil(low) if low % 1 else low +  1
    top = (t + sqrt((t * t) - 4 * d)) / 2
    top = floor(top) if top % 1 else top - 1
    return top - low + 1

lines = open("../input.txt", "r").readlines()
start = perf_counter_ns()
print("part one = ", part1(lines))
print("time[us] = ", (perf_counter_ns() - start) // 1000)
start = perf_counter_ns()
print("part two = ", part2(lines))
print("time[us] = ", (perf_counter_ns() - start) // 1000)