from time import perf_counter_ns

def partOne(lines):
    matches = []
    for line in lines:
        splits = line.rstrip('\n').split(':')[1].split('|')
        wins = set()
        scratch = set()

        split = list(filter(lambda x: (x != ""), splits[0].split(' ')))
        for n in split:
            wins.add(n)

        split = list(filter(lambda x: (x != ""), splits[1].split(' ')))
        for n in split:
            scratch.add(n)

        count = len(wins & scratch)
        if count > 0:
            matches.append(2 ** (count - 1))

    return sum(matches)

def partTwo(lines):
    lucky = []

    for line in lines:
        splits = line.rstrip('\n').split(':')[1].split('|')
        wins = set()
        scratch = set()

        split = list(filter(lambda x: (x != ""), splits[0].split(' ')))
        for n in split:
            wins.add(n)

        split = list(filter(lambda x: (x != ""), splits[1].split(' ')))
        for n in split:
            scratch.add(n)

        lucky.append(len(wins & scratch))
    
    cards = [1] * len(lucky)
    for i in range(len(cards)):
        for j in range(i + 1, i + 1 + lucky[i]):
            cards[j] += cards[i]
    
    return sum(cards)


lines = open("../input.txt", "r").readlines()

start = perf_counter_ns()
print("part one = ", partOne(lines))
print("time[us] = ", (perf_counter_ns() - start) // 1000)

start = perf_counter_ns()
print("part two = ", partTwo(lines))
print("time[us] = ", (perf_counter_ns() - start) // 1000)