from math import ceil

tiles = {
        '|' : "NS",
        '-' : "WE",
        'L' : "NE",
        'J' : "NW",
        'F' : "SE",
        '7' : "SW",
        'S' : "NESW"
        }

dirs = { 'N': (0, -1), 'E': (1, 0), 'S': (0, 1), 'W': (-1, 0) }

def checkCon(tile, dir):
    if tile == '.': return (False, False)
    match dir:
        case 'N': dir = 'S'
        case 'S': dir = 'N'
        case 'W': dir = 'E'
        case 'E': dir = 'W'
    dirs = tiles[tile]
    idx = dirs.find(dir)
    if idx >= 0:
        idx ^= 1
        return (True, dirs[idx])
    else: return (False, False)

def getInput(lines):
    return [[ch for ch in line.rstrip()] for line in lines]

def findStart(map):
    for idx, row in enumerate(map):
        if 'S' in row:
            col = row.index('S')
            return (col, idx)

def follow(map, x, y, dir):
    dist = 0
    points = []
    points.append((x, y))
    while True:
        nx = x + dirs[dir][0]
        ny = y + dirs[dir][1]
        isCon, ndir = checkCon(map[ny][nx], dir)
        if isCon:
            x = nx
            y = ny
            dist += 1
            if map[y][x] == 'S': 
                return (dist // 2, points)
            if ndir != dir:
                dir = ndir
                points.append((x, y))
        else:
            return (-1, points)

def loop(map):
    x, y = findStart(map)
    for dir in list("NWSE"):
        dist, points = follow(map, x, y, dir)
        if dist > 0: return (dist, points)

#shoelace formula
def polyArea(points):
    points.append(points[0])
    res = 0
    for i in range(len(points) - 1):
        res += points[i][0] * points[i + 1][1] - points[i + 1][0] * points[i][1]
    return abs(res / 2)

def solution(map):
    dist, points = loop(map)
    area = polyArea(points)
    return (dist, ceil(area - dist + 1))

map = getInput(open("../input.txt", "r").readlines())
part1, part2 = solution(map)
print("part1 = ", part1)
print("part2 = ", part2)