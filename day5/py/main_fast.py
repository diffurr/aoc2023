import sys
from time import perf_counter_ns

def sandFilter(maps, seeds):
    min = sys.maxsize
    for seed in seeds:
        for map in maps:
            for xform in map:
                rdst = xform[0]
                rsrc = xform[1]
                rlen = xform[2]
                if (seed >= rsrc) and (seed < rsrc + rlen):
                    seed += rdst - rsrc
                    break
                else:
                    continue
                break
        if seed < min:
            min = seed
    return min

def sandFilter2(maps, start, end):
    min = sys.maxsize
    for seed in range(start, end):
        for map in maps:
            for xform in map:
                rdst = xform[0]
                rsrc = xform[1]
                rlen = xform[2]
                if (seed >= rsrc) and (seed < rsrc + rlen):
                    seed += rdst - rsrc
                    break
                else:
                    continue
                break
        if seed < min:
            min = seed 
    return min

def sandFilterRanges(maps, _range):
    top_ranges= []
    top_ranges.append(_range)
    for map in maps:
        new_ranges = []
        while (len(top_ranges) > 0):
            rg_lo, rg_hi = top_ranges.pop()
            for map_lo, map_hi, slide in map:
                if (rg_lo < map_lo) and (rg_hi < map_lo):
                    pass
                elif (rg_lo > map_hi) and (rg_hi > map_hi):
                    pass
                elif (rg_lo < map_lo) and (rg_hi >= map_lo):
                    top_ranges.append([rg_lo, map_lo - 1])
                    new_ranges.append([map_lo + slide, rg_hi + slide])
                    break
                elif (rg_lo >= map_lo) and (rg_hi > map_hi):
                    new_ranges.append([rg_lo + slide, map_hi + slide])
                    top_ranges.append([map_hi + 1, rg_hi])
                    break
                else:
                    new_ranges.append([rg_lo + slide, rg_hi + slide])
                    break
            else: 
                new_ranges.append([rg_lo, rg_hi])
        top_ranges = new_ranges 

    return min([x[0] for x in top_ranges])


def partOne(lines):
    lines = list(filter(lambda x: (x != '\n'), lines))
    seeds = []
    for str in lines[0].split(':')[1].split(' ')[1:]:
        seeds.append(int(str))

    maps = []
    map = []
    for line in lines[2:]:
        if (line[0].isdigit()):
            splits = line.split(' ')
            map.append([int(splits[0]), int(splits[1]), int(splits[2])])
        else:
            maps.append(map[:])
            map.clear()
    maps.append(map)

    return sandFilter(maps, seeds)

def partTwo(lines):
    lines = list(filter(lambda x: (x != '\n'), lines))
    nums = []
    for str in lines[0].split(':')[1].split(' ')[1:]:
        nums.append(int(str))

    ranges = []
    for i in range(0, len(nums), 2):
        ranges.append([nums[i], nums[i] + nums[i + 1] - 1])

    maps = []
    map = []
    for line in lines[2:]:
        if (line[0].isdigit()):
            splits = line.split(' ')
            map.append([int(splits[1]), int(splits[1]) + int(splits[2]) - 1, int(splits[0]) - int(splits[1])])
        else:
            maps.append(map.copy())
            map.clear()
    maps.append(map)

    mins = []
    for _range in ranges:
        mins.append(sandFilterRanges(maps, _range))
    return min(mins)

lines = open("../test.txt", "r").readlines()

start = perf_counter_ns()
print("part one = ", partOne(lines))
print("time[us] = ", (perf_counter_ns() - start) // 1000)
start = perf_counter_ns()
print("part two = ", partTwo(lines))
print("time[us] = ", (perf_counter_ns() - start) // 1000)