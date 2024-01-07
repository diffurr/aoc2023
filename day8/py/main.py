from math import lcm
from time import perf_counter_ns

def getInput(lines):
    dirs = lines[0].rstrip('\n')
    nodes = {}
    for line in lines[2:]:
        nodes[line[0:3]] = (line[7:10], line[12:15])
    return (dirs, nodes)
    
def part1(input):
    dirs = input[0]
    nodes = input[1]
    currnode = "AAA"
    idx = 0
    step = 0
    while (True):
        if currnode == "ZZZ":
            break
        if (dirs[idx] == 'L'):
            currnode = nodes[currnode][0]
        else:
            currnode = nodes[currnode][1]
        idx = (idx + 1) % len(dirs)
        step += 1
    return step

def part2(input):
    dirs = input[0]
    nodes = input[1]
    nodesA = [x for x in nodes.keys() if x[2] == 'A']
    cycles = []
    for node in nodesA:
        idx = 0
        currnode = node
        step = 0
        while(True):
            if currnode[2] == 'Z':
                break
            if dirs[idx] == 'L':
                    currnode = nodes[currnode][0]
            else:
                    currnode = nodes[currnode][1]    
            idx = (idx + 1) % len(dirs)
            step += 1
        cycles.append(step)
    return lcm(*cycles)
    
input = getInput(open("../input.txt", "r").readlines())

start = perf_counter_ns()
res = part1(input)
print("part1 = ", res)
print("time[us] = ", (perf_counter_ns() - start) // 1000)

start = perf_counter_ns()
res = part2(input)
print("part2 = ", res)
print("time[us] = ", (perf_counter_ns() - start) // 1000)