def checkgame(line):
    line = line.rstrip('\n')
    splits = line.split(':')
    id = int(splits[0].split(' ')[1])
    sets = splits[1].split(';')
    for set in sets:
        blue = green = red = 0
        for part in set.split(','):
            elems = part.split(' ')
            match elems[2]:
                case "blue":
                    blue += int(elems[1])
                case "green":
                    green += int(elems[1])
                case "red":
                    red += int(elems[1])    
        if red > 12 or green > 13 or blue > 14:
            return 0
    return id 

def powergame(line):
    blue = green = red = 1
    line = line.rstrip('\n')
    splits = line.split(':')
    sets = splits[1].split(';')
    for set in sets:
        for part in set.split(','):
            elems = part.split(' ')
            val = int(elems[1])
            match elems[2]:
                case "blue":
                    blue = val if val > blue else blue
                case "green":
                    green = val if val > green else green
                case "red":
                    red = val if val > red else red
    return blue * green * red

lines = open("../input.txt", "r").readlines()

#Part One
sum = 0
for line in lines:
    sum += checkgame(line)
print("part one =", sum)

#Part Two
sum = 0
for line in lines:
    sum += powergame(line)
print("part two =", sum)