def getInput(lines):
    vflag = [1] * (len(lines[0]) - 1)
    hflag = []
    for line in lines:
        empty = True
        for i in range(len(line) - 1):
            if line[i] == '#': 
                vflag[i] = 0
                empty = False 
        if empty:
            hflag.append(1)
        else:
            hflag.append(0)
    return (vflag, hflag)

def path(lines, vflag, hflag, scale):
    planets = []
    maxh = 0
    for h, line in enumerate(lines):
        maxw = 0
        for i in range(len(line) - 1):
            if vflag[i] == 1:
                maxw += scale
            else:
                maxw += 1
                if line[i] == '#':
                    planets.append((maxw, maxh))
        if hflag[h] == 1:
            maxh += scale
        else:
            maxh += 1

    sum = 0
    while (len(planets) > 0):
        x1, y1 = planets.pop()
        for x2, y2 in planets:
            sum += abs(x2 - x1) + abs(y2 - y1)
    return sum

def solution(input):
    vflag, hflag = getInput(input)
    part1 = path(input, vflag, hflag, 2)
    part2 = path(input, vflag, hflag, 1_000_000)
    return (part1, part2)

input = open("../input.txt", "r").readlines()
part1, part2 = solution(input)
print("part1 = ", part1)
print("part2 = ", part2)