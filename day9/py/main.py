from time import perf_counter_ns

def getInput(lines):
    nums = []
    for line in lines:
        nums.append([int(x) for x in line.split(' ')])
    return nums

def extra_end(triangle):
    return sum (x[-1] for x in triangle)

def extra_begin(triangle):
    flip = True
    res = 0
    for n in triangle:
        if flip:
            res += n[0]
        else:
            res -= n[0]
        flip ^= True
    return res

def oasis(nums, extra):
    triangle = []
    triangle.append(nums)
    while (True):
        temp = []
        for i in range(1, len(triangle[-1])):
            temp.append(triangle[-1][i] - triangle[-1][i - 1])
        triangle.append(temp)
        if all(x == 0 for x in temp): break
    return extra(triangle)

def part1(input):
    return sum([oasis(x, extra_end) for x in input])

def part2(input):
    return sum([oasis(x, extra_begin) for x in input])

def measure(func, arg, msg="", unit="us"):
    match unit:
        case "ns": scale = 1
        case "us": scale = 1_000
        case "ms": scale = 1_000_000
        case "s": scale = 1_000_000_000
        case _: return 0
    start = perf_counter_ns()
    res = func(arg)
    end = ((perf_counter_ns() - start) / scale)
    if msg != "": print(msg, res)
    print(f"time[{unit}] = {end:.2f}")

input = getInput(open("../input.txt", "r").readlines())
print("part1 = ", part1(input))
print("part2 = ", part2(input))
