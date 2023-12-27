//algebraic solution from reddit u/themanushiya
import * as fs from 'fs';

function line2nums(_line: string) {
    const splits: string[] = _line.split(':')[1].trim().split(' ');
    const numstr: string[] = splits.filter((x) => x != '');
    return numstr.map((x) => Number(x));
}

function line2num(_line: string) {
    const splits: string[] = _line.split(':')[1].trim().split(' ');
    const numstr: string[] = splits.filter((x) => x != '');
    return Number(numstr.reduce((x, y) => x + y, ""));
}

function part1(_lines: string[]) {
    const tnums: number[] = line2nums(_lines[0]);
    const dnums: number[] = line2nums(_lines[1]);

    let res = 1;
    for (let i in tnums) {
        const t: number = tnums[i]
        const d: number = dnums[i]
        let low: number = (t - Math.sqrt((t * t) - 4 * d)) / 2;
        low = low % 1 ? Math.ceil(low) : low + 1;
        let top: number = (t + Math.sqrt((t * t) - 4 * d)) / 2;
        top = top % 1 ? Math.floor(top) : top - 1;
        res *= top - low + 1;
    }
    return res
}

function part2(_lines: string[]) {
    const t: number = line2num(_lines[0]);
    const d: number = line2num(_lines[1]);
    let low: number = (t - Math.sqrt((t * t) - 4 * d)) / 2;
    low = low % 1 ? Math.ceil(low) : low + 1;
    let top: number = (t + Math.sqrt((t * t) - 4 * d)) / 2;
    top = top % 1 ? Math.floor(top) : top - 1;
    return top - low + 1;
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