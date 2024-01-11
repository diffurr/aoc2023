import * as fs from 'fs';

function measure(str: string, func: Function, arg: any) {
    const start: number = performance.now();
    const res: any = func(arg)
    const end: number = performance.now();
    console.log(str, res);
    console.log("time[us] = ", (end - start) * 1000);
    return res;
}

function getInput(lines: string[]): Array<Array<number>> {
    let input: Array<Array<number>> = []
    for (let line of lines){
        input.push(line.split(' ').map((numstr) => Number(numstr)));
    }
    return input;
}

function solution1(nums: number[]): number {
    if (nums.every((x) =>  x == 0 )) return 0;
    let subs: number[] = []
     for (let i = 1; i < nums.length; i++) {
         subs.push(nums[i] - nums[i - 1]);
    }
    return nums[nums.length - 1] + solution1(subs)
}

function solution2(nums: number[]): number {
    if (nums.every((x) =>  x == 0 )) return 0;
    let subs: number[] = []
    for (let i = 1; i < nums.length; i++) {
        subs.push(nums[i] - nums[i - 1]);
    }
    return nums[0] - solution2(subs)
}

function part1(input: Array<Array<number>>): number {
    return input.map(solution1).reduce((acc, elem) => acc + elem, 0);
}

function part2(input: Array<Array<number>>): number {
    return input.map(solution2).reduce((acc, elem) => acc + elem, 0);
}

const input = getInput(fs.readFileSync('../input.txt', 'utf8').split('\n'));
console.log("part1 = ", part1(input))
console.log("part2 = ", part2(input))