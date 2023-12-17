function partOne (lines) {
    let sum = 0
    for (let line of lines) {
        const splits = line.split(':')[1].split('|');
        const wins = new Set();
        const scratch = new Set();

        let part = splits[0].split(' ').filter((num) => num != "");
        for (let n of part) {
            wins.add(n);
        }
        part = splits[1].split(' ').filter((num) => num != "");
        for (let n of part) {
            scratch.add(n);
        }

        let count = 0;
        for (let num of wins) {
            if (scratch.has(num)) { count += 1; }
        }
        if (count > 0) {
            sum += 2**(count - 1);
        }
    }
    return sum;
}

function partTwo (lines) {
    const lucky = [];
    for (let line of lines) {
        const splits = line.split(':')[1].split('|');
        const wins = new Set();
        const scratch = new Set();

        let part = splits[0].split(' ').filter((num) => num != "");
        for (let n of part) {
            wins.add(n);
        }
        part = splits[1].split(' ').filter((num) => num != "");
        for (let n of part) {
            scratch.add(n);
        }

        let count = 0;
        for (let num of wins) {
            if (scratch.has(num)) { count += 1; }
        }
        lucky.push(count)
    }

    const cards = Array(lucky.length).fill(1);
    for (let i = 0; i < cards.length; i += 1) {
        for (let j = i + 1; j < i + 1 + lucky[i]; j += 1) {
            cards[j] += cards[i]
        }
    }
    let sum = 0;
    cards.map((val) => sum += val);
    return sum;
}

const fs = require('fs');
fs.readFile('../input.txt', 'utf8', function (err, data) {
    if (err) {
        console.error(err);
        return;
    }
    
    const input = data.split('\n');

    const start1 = performance.now();
    const res1 = partOne(input);
    const end1 = performance.now();
    console.log("part one =", res1);
    console.log("time[ms] =", end1 - start1);

    const start2 = performance.now();
    const res2 = partTwo(input);
    const end2 = performance.now();
    console.log("part two =", res2);
    console.log("time[ms] =", end2 - start2);
});