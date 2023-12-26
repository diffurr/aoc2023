const fs = require('fs');
const input = readInput(fs.readFileSync('../test.txt', 'utf8'));
showResult("part one = ", partOne, input);
showResult("part two = ", partTwo, input);

function showResult(str, func, arg) {
    const start = performance.now();
    const res = func(arg)
    const end = performance.now();
    console.log(str, res);
    console.log("time[ms] = ", end - start);
    return res;
}

function readInput(input) {
    const seeds = [];
    const lines = input.split('\n');
    for (let numstr of lines[0].substring(lines[0].indexOf(':') + 2).split(' ')) {
        seeds.push(Number(numstr));
    }

    let map = [];
    const maps = [];
    for (let line of lines.splice(3)) {
        if (!isNaN(line[0]) && line[0] != '\r') {
            const splits = line.split(' ');
            const dst = Number(splits[0]);
            const src = Number(splits[1]);
            const len = Number(splits[2]);
            map.push({lo: src, hi: src + len - 1, slide: dst - src});
        }
        else if (map.length) {
            maps.push(map);
            map = [];
        }
    }
    maps.push(map);
    return { seeds, maps };
}

function partOne(input) {
    const mins = [];
    for (let i = 0; i < input.seeds.length; i += 1) {
        mins.push(sandFilter(input.maps, { lo: input.seeds[i], hi: input.seeds[i] }));
    }
    return Math.min(...mins);
}

function partTwo(input) {
    const mins = [];
    for (let i = 0; i < input.seeds.length; i += 2) {
        mins.push(sandFilter(input.maps, { lo: input.seeds[i], hi: input.seeds[i] + input.seeds[i + 1] - 1 }));
    }
    return Math.min(...mins);
}

function sandFilter(maps, range) {
    let ranges = [];
    ranges.push(range);
    for (map of maps) {
        const newRanges = [];
        while (ranges.length) {
            const range = ranges.pop();
            let passed = false;
            for (xform of map) {
                if ((range.lo < xform.lo) && (range.hi < xform.lo)) {
                    passed = true;
                }
                else if ((range.lo > xform.hi) && (range.hi > xform.hi)) {
                    passed = true;
                }
                else if ((range.lo < xform.lo) && ( range.hi >= xform.lo)) {
                    ranges.push({lo: range.lo, hi: xform.lo - 1});
                    newRanges.push({lo: xform.lo + xform.slide, hi: range.hi + xform.slide});
                    passed = false;
                    break;
                }
                else if ((range.lo >= xform.lo) && (range.hi > xform.hi)) {
                    ranges.push({lo: xform.hi + 1, hi: range.hi});
                    newRanges.push({lo: range.lo + xform.slide, hi: xform.hi + xform.slide});
                    passed = false;
                    break;
                }
                else {
                    newRanges.push({lo: range.lo + xform.slide, hi: range.hi + xform.slide});
                    passed = false;
                    break;
                }
            }
            if (passed) {
                newRanges.push(range);
            }
        }
        ranges = newRanges
    }
    let min = Infinity;
    ranges.map((x) => {
        if (x.lo < min) min = x.lo;
    });
    return min;
}