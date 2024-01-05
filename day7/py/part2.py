#part2 = 249138943

from time import perf_counter_ns

Hand = { "HIGH": 0, 'PAIR1': 1, 'PAIR2': 2, 'THREE': 3, 'FULL': 4, 'FOUR': 5, 'FIVE': 6}

Str = {
    "A": 12,
    "K": 11,
    "Q": 10,
    "T": 9,
    "9": 8,
    "8": 7,
    "7": 6,
    "6": 5,
    "5": 4,
    "4": 3,
    "3": 2,
    "2": 1,
    "J": 0,
}

def getHandStr(_hand):
    res = 0
    res |= Str[_hand[0]] << 16
    res |= Str[_hand[1]] << 12
    res |= Str[_hand[2]] << 8
    res |= Str[_hand[3]] << 4
    res |= Str[_hand[4]]
    return res

def getHandType(_hand):
    hand = list(set(_hand))
    match len(hand):
        case 5:
            return Hand["HIGH"]
        case 4:
            return Hand["PAIR1"]
        case 1:
            return Hand["FIVE"]
        case 3:
            for card in hand:
                match _hand.count(card):
                    case 3:
                        return Hand["THREE"]
                    case 2:
                        return Hand["PAIR2"]
        case _:
            match _hand.count(hand[0]):
                case 4 | 1:
                    return Hand["FOUR"]
                case 2 | 3:
                    return Hand["FULL"]

def getHandTypeJoker(_hand):
    if 'J' not in _hand:
        return getHandType(_hand)
    max = -1
    for n in list(Str.keys())[0:-1]:
        type = getHandType(_hand.replace('J', n))
        if type == Hand["FIVE"]:
            return type
        if type > max: 
            max = type
    return max


#return [(type, strength, bid)]
def getInput(lines):
    hands = []
    for line in lines:
        hands.append((
            getHandTypeJoker(line[0:5]),
            getHandStr(line[0:5]),
            int(line[6:])
        ))
    return hands

def part2(lines):
    hands = getInput(lines)
    hands = sorted(hands, key=lambda hand: hand[1])
    hands = sorted(hands, key=lambda hand: hand[0])

    sum = 0
    for idx, hand in enumerate(hands):
        sum += (idx + 1) * hand[2]
    return sum


input = open("../input.txt", "r").readlines()
start = perf_counter_ns()
res = part2(input)
print("part2 = ", res)
print("time[us] = ", (perf_counter_ns() - start) // 1000)