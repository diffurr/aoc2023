import * as fs from 'fs';

enum Dir { N, E, S, W, X }
const dirs: Array<Array<number>> = [[0,-1], [1,0], [0,1], [-1,0]]
const tiles: Map<string, string> = new Map([
    ['|', "NXSX"],
    ['-', "XEXW"],
    ['L', "XXEN"],
    ['J', "XNWX"],
    ['7', "WSXX"],
    ['F', "EXXS"],
    ['S', "NESW"],
    ['.', "XXXX"]
])

function getInput(lines: string[]): string[] {
    return lines.map((x) => x.trimEnd());
}

function makeMap(w: number, h: number, init: number): number[][] {
    let map: number[][] = []
    while (h-- > 0) {
        map.push(Array<number>(w).fill(init));
    }
    return map;
}

function closeLoop(firstd: Dir, lastd: Dir): number {
    for (const [key, value] of tiles.entries()) {
        if (Dir[value[lastd]] == firstd) {
            return key.charCodeAt(0);
        }
    }
}

function follow(map: string[], x: number, y: number, dir: Dir): [number, number[][]] {
    let dist: number = 0;
    const firstd: Dir = dir;
    const loopMap: number[][] = makeMap(map[0].length, map.length, '0'.charCodeAt(0));
    while (true) {
        const nx: number = x + dirs[dir][0];
        const ny: number = y + dirs[dir][1];
        loopMap[y][x] = map[y][x].charCodeAt(0);
        const ndir: Dir = Dir[tiles.get(map[ny][nx])[dir]]
        if (ndir != Dir.X) {
            x = nx;
            y = ny;
            dist++;
            if (map[y][x] == 'S') {
                loopMap[y][x] = closeLoop(firstd, dir);
                return [dist / 2, loopMap];
            }
            dir = ndir;
        }
        else {
            return [-1, loopMap];
        }
    }
}

function countInside(map: number[][]): number {
    let count: number = 0;
    for (let row of map) {
        let inside: boolean = false;
        let prev: string = '0';
        for (let ch of row) {
            const tile: string = String.fromCharCode(ch);
            if (tile == '|') { inside = !inside; }
            else if (tile == 'J' && prev == 'F') { inside = !inside; }
			else if (tile == '7' && prev == 'L') { inside = !inside; }
            else if (inside && tile == '0') { count++; }
            if (tile != '-') { prev = tile; }
        }
    }
    return count;
}

function findStart(map: string[]): number[] {
    for (const [row, line] of map.entries()) {
        const col: number = line.indexOf('S');
        if (col >= 0) {
            return [col, row];
        }
    }
}

function loop(map: string[]): [number, number[][]] {
    const [x, y] = findStart(map);
    for (const dir of "NESW") {
        const [dist, loopMap] = follow(map, x, y, Dir[dir]);
        if (dist >= 0) return [dist, loopMap];
    }
}

function solution(map: string[]): [number, number] {
    const [dist, loopMap] = loop(map);
    const inside: number = countInside(loopMap);
    return [dist, inside];
}

function measure(func: Function, arg: any) {
    const start: number = performance.now();
    const res: any = func(arg)
    const end: number = performance.now();
    console.log("time[us] = ", (end - start) * 1000);
    return res;
}

const map: string[] = getInput(fs.readFileSync("../input.txt", "utf8").split('\n'));
const [part1, part2] = solution(map)
console.log("part1 = ", part1);
console.log("part2 = ", part2);