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
    loopMap = [[0 for x in range(len(map[0]))] for x in range(len(map))]
    points.append((x, y))
    while True:
        nx = x + dirs[dir][0]
        ny = y + dirs[dir][1]
        loopMap[y][x] = '#'
        isCon, ndir = checkCon(map[ny][nx], dir)
        if isCon:
            x = nx
            y = ny
            dist += 1
            if map[y][x] == 'S': 
                return (dist // 2, points, loopMap)
            if ndir != dir:
                dir = ndir
                points.append((x, y))
        else:
            return (-1, points, loopMap)

def loop(map):
    x, y = findStart(map)
    for dir in list("NWSE"):
        dist, points, loopMap = follow(map, x, y, dir)
        if dist > 0: return (dist, points, loopMap)

def flood(map):
    w = len(map[0])
    h = len(map)
    queue = []
    queue.append((1, 1))
    while len(queue) > 0:
        x, y = queue.pop()
        map[y][x] = '1'
        for dx, dy in dirs.values():
            nx = x + dx
            ny = y + dy
            if nx >= 0 and nx < w and ny >= 0 and ny < h:
                if map[ny][nx] != '#' and map[ny][nx] != '1':
                    queue.append((nx, ny))
    return map

def pointInPoly(points, x, y):
    inside = False
    for i in range(len(points)):
        x1, y1 = points[i]
        x2, y2 = points[(i + 1) % len(points)]
        if (y1 < y and y2 >= y) or (y2 < y and y1 >= y):
            if x1 + (y - y1) / (y2 - y1) * (x2 - x1) < x:
                inside = not inside
    return inside

def countPiP(map, points):
    count = 0
    for y in range(len(map)):
        for x in range(len(map[y])):
           if map[y][x] != '1' and map[y][x] != '#':
               if pointInPoly(points, x, y):
                   count += 1
    return count

def solution(map):
    dist, points, loopMap = loop(map)
    floodMap = flood(loopMap)
    inside = countPiP(floodMap, points)
    return (dist, inside)

map = getInput(open("../input.txt", "r").readlines())
part1, part2 = solution(map)
print("part1 = ", part1)
print("part2 = ", part2)