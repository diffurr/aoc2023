import * as fs from 'fs';

enum HandType {
    HIGH, PAIR1, PAIR2, THREE, FULL, FOUR, FIVE, size = 7
}

const Str1: Map<string, number> = new Map([
    ["A", 12], 
    ["K", 11],
    ["Q", 10],
    ["J", 9],
    ["T", 8],
    ["9", 7],
    ["8", 6],
    ["7", 5],
    ["6", 4],
    ["5", 3],
    ["4", 2],
    ["3", 1],
    ["2", 0],
]);

const Str2: Map<string, number> = new Map([
    ["A", 12], 
    ["K", 11],
    ["Q", 10],
    ["T", 9],
    ["9", 8],
    ["8", 7],
    ["7", 6],
    ["6", 5],
    ["5", 4],
    ["4", 3],
    ["3", 2],
    ["2", 1],
    ["J", 0],
]);

class Hand {
    str: number;
    type: HandType;
    bid: number; 
    constructor(str: number, type: HandType, bid: number) {
        this.str = str;
        this.type = type;
        this.bid = bid;
    }
}

function getHandStr1(_hand: string): number {
    let res:number = 0;
    res |= Str1.get(_hand[0]) << 16;
    res |= Str1.get(_hand[1]) << 12;
    res |= Str1.get(_hand[2]) << 8;
    res |= Str1.get(_hand[3]) << 4;
    res |= Str1.get(_hand[4]);
    return res;
}

function getHandStr2(_hand: string): number {
    let res:number = 0;
    res |= Str2.get(_hand[0]) << 16;
    res |= Str2.get(_hand[1]) << 12;
    res |= Str2.get(_hand[2]) << 8;
    res |= Str2.get(_hand[3]) << 4;
    res |= Str2.get(_hand[4]);
    return res;
}

function getHandType1(_hand: string): HandType {
    const hand: string[] = Array.from(new Set(_hand.split('')));
    switch (hand.length) {
        case 5:
            return HandType.HIGH;
        case 4:
            return HandType.PAIR1;
        case 1:
            return HandType.FIVE;
        case 3:
            for (const card of hand) {
                const len: number = (_hand.match(new RegExp(card, "g")) || []).length
                if (len == 3) {
                    return HandType.THREE;
                } else if (len == 2) {
                    return HandType.PAIR2;
                }
            }
        default:
            const len: number = (_hand.match(new RegExp(hand[0], "g")) || []).length
            if (len == 4 || len == 1) {
                return HandType.FOUR;
            }    
            if (len == 2 || len == 3) {
                return HandType.FULL;
            }
    }
}

function getHandType2(_hand: string): HandType {
    if (!_hand.match(/J/g)) {
        return getHandType1(_hand);
    }
    let max: number = -1;
    for (let c of Str2.keys()) {
        let type: HandType = getHandType1(_hand.replaceAll('J', c));
        if (type == HandType.FIVE) {
            return type;
        }
        if (type > max) {
            max = type;
        }
    }
    return max;
}

function getInput(funcHandStr: Function, funcHandType: Function, lines: string[]): Hand[] {
    const input: Hand[] = []
    for (let line of lines) {
        const handStr: string = line.substring(0, 5); 
        const val: number = parseInt(line.substring(6));
        input.push(new Hand(
            funcHandStr(handStr),
            funcHandType(handStr), 
            val
            ));
    }
    return input;
}

function solution(hands: Hand[]): number {
    hands.sort((a: Hand, b: Hand) => {
        if (a.str < b.str) return -1;
        if (a.str > b.str) return 1;
        return 0;
    });

    hands.sort((a: Hand, b: Hand) => {
        if (a.type < b.type) return -1;
        if (a.type > b.type) return 1;
        return 0;
    });

    let sum: number = 0;
    let idx: number = 1;
    for (var hand of hands) {
        sum += idx++ * hand.bid;
    }
    return sum;
}

function solutio(hands: Hand[]): number {
    const types: Array<Array<Hand>> = [];
    for (let i = 0; i < HandType.size; ++i) {
        types.push(new Array<Hand>);
    }
    for (let hand of hands) {
        types[hand.type].push(hand);
    }
    for (let type of types) {
        type.sort((a: Hand, b: Hand) => {
            if (a.str < b.str) {
                return -1;
            }
            if (a.str > b.str) {
                return 1;
            }
            return 0;
        });
    }
    let sum: number = 0;
    let idx: number = 1;
    for (let type of types) {
        for (let hand of type) {
            sum += idx++ * hand.bid;
        }
    }
    return sum;
}

function part1(lines: string[]): number {
    const hands: Hand[] = getInput(getHandStr1, getHandType1, lines);
    return solution(hands);
}

function part2(lines: string[]): number {
    const hands: Hand[] = getInput(getHandStr2, getHandType2, lines);
    return solution(hands);
}

function showResult(str: string, func: Function, arg: any) {
    const start: number = performance.now();
    const res: any = func(arg)
    const end: number = performance.now();
    console.log(str, res);
    console.log("time[us] = ", (end - start) * 1000);
    return res;
}

const lines: string[] = fs.readFileSync('../input.txt', 'utf8').split('\n');
showResult("part1 = ", part1, lines);
showResult("part2 = ", part2, lines);