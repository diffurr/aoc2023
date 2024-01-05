from time import perf_counter_ns

lines = open("../test.txt", "r").readlines()

val = {
    "A": "12",
    "K": "11",
    "Q": "10",
    "J": "9",
    "T": "8",
    "9": "7",
    "8": "6",
    "7": "5",
    "6": "4",
    "5": "3",
    "4": "2",
    "3": "1",
    "2": "0",
}

hands = []
bids = []
for line in lines:
    hands.append(line[0:5])
    bids.append(int(line[6:]))

def getHandVal1(_hand):
    numstr = []
    for n in _hand:
        if n >= 'A' and n <= 'T':
            match n:
                case 'A': numstr.append("12")
                case 'K': numstr.append("11")
                case 'Q': numstr.append("10")
                case 'J': numstr.append("9")
                case 'T': numstr.append("8")
        else:
            numstr.append(str(ord(n) - 50))
    return int(''.join(numstr))

def getHandVal2(_hand):
    numstr = []
    for n in _hand:
        numstr.append(val[n])

    return int(''.join(numstr))

def getHandVal3(_hand):
    return int(''.join([val[x] for x in _hand]))

start = perf_counter_ns()
for n in range(100):
    vals1 = []
    for hand in hands:
        vals1.append(getHandVal1(hand)) 
print("getHandVal1[us] = ", (perf_counter_ns() - start) // 1000)

start = perf_counter_ns()
for n in range(100):
    vals2 = []
    for hand in hands:
        vals2.append(getHandVal2(hand)) 
print("getHandVal2[us] = ", (perf_counter_ns() - start) // 1000)

start = perf_counter_ns()
for n in range(100):
    vals3 = []
    for hand in hands:
        vals3.append(getHandVal3(hand)) 
print("getHandVal3[us] = ", (perf_counter_ns() - start) // 1000)

for i in range(len(vals1)):
    if vals1[i] != vals3[i]:
        print("WRONG")
        break