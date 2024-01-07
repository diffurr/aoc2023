import * as fs from 'fs';

type Nodes = Map<string, [string, string]>;

function showResult(str: string, func: Function, arg: any) {
    const start: number = performance.now();
    const res: any = func(arg)
    const end: number = performance.now();
    console.log(str, res);
    console.log("time[us] = ", (end - start) * 1000);
    return res;
}

function gcd(x: number, y: number): number {
    while (x != y) {
        if (x > y) {
            x = x - y;
        }
        else {
            y = y - x;
        }
    }
    return x;
}

function lcmArray(nums: number[]): number {
    let res: number = 1;
    for (let num of nums) {
        res = (res * num) / gcd(res, num);
    }
    return res;
}

function getInput(lines: string[]):[string, Nodes] {
    let nodes: Nodes = new Map();
    const dirs: string = lines[0].trimEnd();
    for (let line of lines.slice(2, lines.length)) {
        nodes.set(
            line.substring(0, 3), 
            [line.substring(7, 10), line.substring(12, 15)]);
    }
    return [dirs, nodes]
}

function part1(input: [string, Nodes]): number {
    const dirs:string = input[0];
    const nodes:Map<string, [string, string]> = input[1];
    let currNode: string = "AAA";
    let idx: number = 0;
    let step: number = 0;
    while(true) {
        if (currNode === "ZZZ") {
            break;
        }
        currNode = dirs[idx] === 'L' 
            ? nodes.get(currNode)[0]
            : nodes.get(currNode)[1];
        idx = (++idx) % dirs.length;
        step++;
    }
    return step;
}

function part2(input: [string, Nodes]): number {
    const dirs:string = input[0];
    const nodes:Map<string, [string, string]> = input[1];
    const nodesA: string[] = []
    const steps: number[] = []

    for (let node of nodes.keys()) {
        if (node[2] === 'A') {
            nodesA.push(node);
        }
    }
    let res = 1
    for (let node of nodesA) {
        let idx: number = 0;
        let currNode: string = node;
        let step: number = 0;
        while(true) {
            if (currNode[2] === 'Z') {
                break;
            }
            currNode = dirs[idx] === 'L' 
                ? nodes.get(currNode)[0]
                : nodes.get(currNode)[1];
            idx = (++idx) % dirs.length;
            step++;
        }
        steps.push(step);
    }

    return lcmArray(steps);
}

const lines: string[] = fs.readFileSync('../input.txt', 'utf8').split('\n');
const input = getInput(lines)
showResult("part1 = ", part1, input);
showResult("part2 = ", part2, input);