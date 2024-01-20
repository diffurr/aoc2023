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

def closeLoop(firstd, lastd):
    match lastd:
        case 'N': lastd = 'S'
        case 'S': lastd = 'N'
        case 'W': lastd = 'E'
        case 'E': lastd = 'W'
    for key, value in tiles.items():
        if firstd in value and lastd in value:
            return key

def follow(map, x, y, dir):
    dist = 0
    firstd = dir
    loopMap = [[0 for x in range(len(map[0]))] for x in range(len(map))]
    while True:
        nx = x + dirs[dir][0]
        ny = y + dirs[dir][1]
        loopMap[y][x] = map[y][x]
        isCon, ndir = checkCon(map[ny][nx], dir)
        if isCon:
            x = nx
            y = ny
            dist += 1
            if map[y][x] == 'S': 
                loopMap[y][x] = closeLoop(firstd, dir)
                return (dist // 2, loopMap)
            dir = ndir
        else:
            return (-1, loopMap)

def loop(map):
    x, y = findStart(map)
    for dir in list("NWSE"):
        dist, loopMap = follow(map, x, y, dir)
        if dist > 0: return (dist, loopMap)

def countInside(map):
    count = 0
    for row in map:
        inside = False
        for ch in row:
            if ch == '|': inside = not inside
            elif ch == 'J' and prev == 'F':inside = not inside
            elif ch == '7' and prev == 'L':inside = not inside
            elif inside and ch == 0: count += 1
            if ch != '-': prev = ch
    return count 

def solution(map):
    dist, loopMap = loop(map)
    inside = countInside(loopMap)
    return(dist, inside)

map = getInput(open("../input.txt", "r").readlines())
part1, part2 = solution(map)
print("part1 = ", part1)
print("part2 = ", part2)