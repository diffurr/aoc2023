function isDigit(c) {
    return c >= '0' && c <= '9';
}

function isSym(c) {
    return (c >= '!' && c <= '-') || c == '/' || (c >= ':' && c <= '@');
}

function prepInput(lines) {
    const span = lines[0].length + 1;
    const newlines = [];
    newlines.push('.'.repeat(span));
    lines.map((line) => newlines.push('.' + line + '.'));
    newlines.push('.'.repeat(span));
    return newlines;
}

function findSym(lines, row, col, ndigs) {
    const near = lines[row-1].substr(col-1, ndigs+2) +
    lines[row+1].substr(col-1, ndigs+2) +
    lines[row][col-1] + lines[row][col+ndigs];

    for (let c of near) {
        if (isSym(c)) return true;
    }
    return false
}

function findGear(lines, row, col, ndigs) {
    const near = []
    near.push(lines[row-1].substr(col-1, ndigs+2));
    near.push(lines[row].substr(col-1, ndigs+2));
    near.push(lines[row+1].substr(col-1, ndigs+2));
    for (let r = 0; r < near.length; r++) {
        for (let c = 0; c < near[r].length; c++) {
            if (near[r][c] == '*') {
                return (row-1+r).toString() + ',' + (col-1+c).toString();
            }
        }
    }
    return null;
}

function partOne(lines) {
    const nums = [];
    for (let row = 0; row < lines.length; row++) {
        for (let col = 0; col < lines[row].length; col++) {
            if (isDigit(lines[row][col])) {
                const num = parseInt(lines[row].substr(col, 3))
                const ndigs = num.toString().length
                if (findSym(lines, row, col, ndigs)) {
                    nums.push(num)
                }
                col += ndigs
            }
        }
    }

    let sum = 0
    nums.forEach( num => {
        sum += num
    });
    return sum
}

function partTwo(lines) {
    const gears = {}
    for (let row = 0; row < lines.length; row++) {
        for (let col = 0; col < lines[row].length; col++) {
            if (isDigit(lines[row][col])) {
                const num = parseInt(lines[row].substr(col, 3));
                const ndigs = num.toString().length;
                const gearid = findGear(lines, row, col, ndigs);
                if (gearid) {
                    if (gearid in gears) {
                        gears[gearid].push(num)
                    } else {
                        gears[gearid] = [];
                        gears[gearid].push(num)
                    }
                }
                col += ndigs;
            }
        }
    }

    let sum = 0
    Object.entries(gears).forEach(
        ([key, val]) => { 
            if (val.length == 2) {
                sum += val[0] * val[1];
            }
    });
    return sum;
}

const fs = require('fs');
fs.readFile('../input.txt', 'utf8', function (err, data) {
    if (err) {
        console.error(err);
        return;
    }
    var lines = prepInput(data.split('\n'));

    const start1 = performance.now();
    const res1 = partOne(lines);
    const end1 = performance.now();
    console.log("part one =", res1);
    console.log("time[ms] =", end1 - start1);

    const start2 = performance.now();
    const res2 = partTwo(lines)
    const end2 = performance.now();
    console.log("part two =", res2);
    console.log("time[ms] =", end2 - start2);
});