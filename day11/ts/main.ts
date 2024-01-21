import * as fs from "fs";

function getInput(lines: string[]): [boolean[], boolean[]] {
    const vflag: boolean[] = new Array(lines[0].length).fill(true);
    const hflag: boolean[] = [];
    for (let line of lines) {
        let empty: boolean = true;
        for (let i = 0; i < line.length; i++) {
            if (line[i] == '#') {
                vflag[i] = false;
                empty = false;
            }
        }
        if (empty) { hflag.push(true); }
        else { hflag.push(false); }
    }
    return [vflag, hflag];
}

function path(lines: string[], vflag: boolean[], hflag: boolean[], scale: number): number {
    const planets = [];
    let maxh: number = 0;
    for (let h = 0; h < lines.length; h++) {
        let maxw: number = 0;
        const line: string = lines[h];
        for (let i = 0; i < line.length; i++) {
            if (vflag[i]) {
                maxw += scale;
            }
            else {
                if (line[i] == '#') {
                    planets.push({x: maxw, y: maxh});
                }
                maxw += 1;
            }
        }
        if (hflag[h]) { maxh += scale; }
        else { maxh += 1; }
    }

    let sum: number = 0;
    while (planets.length > 0) {
        const p1 = planets.pop();
        for (const p2 of planets) {
            sum += Math.abs(p2.x - p1.x) + Math.abs(p2.y - p1.y);
        }
    }
    return sum;
}

function solution(lines: string[]): [number, number] {
    const [vflag, hflag] = getInput(lines);
    const part1: number = path(lines, vflag, hflag, 2);
    const part2: number = path(lines, vflag, hflag, 1000000);
    return [part1, part2];
}

const lines: string[] = fs.readFileSync("../input.txt", "utf8").split('\n');
const [part1, part2] = solution(lines);
console.log("part1 = ", part1);
console.log("part2 = ", part2);