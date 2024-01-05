from enum import Enum
from time import perf_counter_ns

class Hand(Enum):
    HIGH = 0
    PAIR1 = 1
    PAIR2 = 2
    THREE = 3
    FULL = 4
    FOUR = 5
    FIVE = 6

#sort, scan and count
def checkHand0(hand):
    hand = sorted(hand)
    three = 0
    pairs = 0
    count = 1
    for i in range(len(hand) - 1):
        if hand[i] == hand[i + 1]:
            count += 1
        else:
            if count == 4:
                return Hand.FOUR
            elif count == 3:
                three += 1
                count = 1
            elif count == 2:
                pairs += 1
                count = 1
            else:
                count = 1
    if count == 5:
        return Hand.FIVE
    elif count == 4:
        return Hand.FOUR
    elif count == 3:
        three += 1
    elif count == 2:
        pairs += 1
    
    if three and pairs:
        return Hand.FULL
    if three:
        return Hand.THREE
    if pairs == 2:
        return Hand.PAIR2
    if pairs == 1:
        return Hand.PAIR1
    return Hand.HIGH

#set, count 
def checkHand1(_hand):
    hand = list(set(_hand))
    match len(hand):
        case 5:
            return Hand.HIGH
        case 4:
            return Hand.PAIR1
        case 1:
            return Hand.FIVE
        case 3:
            for card in hand:
                match _hand.count(card):
                    case 3:
                        return Hand.THREE
                    case 2:
                        return Hand.PAIR2
        case _:
            match _hand.count(hand[0]):
                case 4 | 1:
                    return Hand.FOUR
                case 2 | 3:
                    return Hand.FULL

#hash, count
def checkHand2(_hand):
    hand = {}
    for card in _hand:
        if card in hand:
            hand[card] += 1
        else:
            hand[card] = 1

    if len(hand) == 5:
        return Hand.HIGH
    if len(hand) == 4:
        return Hand.PAIR1
    if len(hand) == 1:
        return Hand.FIVE
    
    hand = sorted(hand.values(), reverse = True)
    if len(hand) == 3:
        if hand[0] == 3:
            return Hand.THREE
        else:
            return Hand.PAIR2
    if len(hand) == 2:
        if (hand[0]) == 4:
            return Hand.FOUR
        else:
            return Hand.FULL

def checkHand3(_hand):
    counts = [0] * 35
    for card in _hand:
        counts[ord(card) - 50] += 1

    hand = list(filter(lambda x: (x > 0), counts))
    if len(hand) == 5:
        return Hand.HIGH
    if len(hand) == 4:
        return Hand.PAIR1
    if len(hand) == 1:
        return Hand.FIVE
    
    hand = sorted(hand, reverse = True)
    if len(hand) == 3:
        if hand[0] == 3:
            return Hand.THREE
        else:
            return Hand.PAIR2
    if len(hand) == 2:
        if (hand[0]) == 4:
            return Hand.FOUR
        else:
            return Hand.FULL


lines = open("../input.txt", "r").readlines()

hands = []
bids = []
for line in lines:
    hands.append(line[0:5])
    bids.append(int(line[6:]))

start = perf_counter_ns()
for n in range(100):
    types0 = []
    for hand in hands:
        types0.append(checkHand0(hand))
print("checkHand0 [us] = ", (perf_counter_ns() - start) // 1000)

start = perf_counter_ns()
for n in range(100):
    types1 = []
    for hand in hands:
        types1.append(checkHand1(hand))
print("checkHand1 [us] = ", (perf_counter_ns() - start) // 1000)

start = perf_counter_ns()
for n in range(100):
    types2 = []
    for hand in hands:
        types2.append(checkHand2(hand))
print("checkHand2 [us] = ", (perf_counter_ns() - start) // 1000)

start = perf_counter_ns()
for n in range(100):
    types3 = []
    for hand in hands:
        types3.append(checkHand3(hand))
print("checkHand3 [us] = ", (perf_counter_ns() - start) // 1000)

for i in range(len(types0)):
    if types0[i] != types1[i] or types0[i] != types2[i] \
          or types0[i] != types3[i]:
        print("WRONG!")
        print(i)
        print(types0[i])
        print(types3[i])
        break