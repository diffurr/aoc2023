function playGame(line) {
    var splits = line.split(':');
    var id = parseInt(splits[0].split(' ')[1]);
    var sets = splits[1].split(';');
    for (let idx in sets) {
        var red = green = blue = 0;
        var set = sets[idx].split(',');
        for (let idx in set) {
            var pos = set[idx].lastIndexOf(' ');
            var val = parseInt(set[idx]);
            switch(set[idx].substr(pos+1)) {
                case "red":
                    red += val;
                    break;
                case "green":
                    green += val;
                    break;
                case "blue":
                    blue += val;
                    break;
            }
        }
        if (red > 12 || green > 13 || blue > 14) return 0;
    }
    return id;
}

function powerGame(line) {
    var red = green = blue = 1;
    var sets = line.split(':')[1].split(';');
    for (let idx in sets) {
        var set = sets[idx].split(',');
        for (let idx in set) {
            var pos = set[idx].lastIndexOf(' ');
            var val = parseInt(set[idx]);
            switch(set[idx].substr(pos+1)) {
                case "red":
                    red = val > red ? val : red;
                    break;
                case "green":
                    green = val > green ? val : green;
                    break;
                case "blue":
                    blue = val > blue ? val : blue;
                    break;
            }
        }
    }
    return red * green * blue;
}

const fs = require('fs');
fs.readFile('../input.txt', 'utf8', function (err, data) {
    if (err) {
        console.error(err);
        return;
    }
    var lines = data.split('\n');

    //Part One
    var sum1 = 0;
    lines.forEach((line) => {
        sum1 += playGame(line);
    });
    console.log("part one =", sum1);

    //Part Two
    var sum2 = 0;
    lines.forEach((line) => {
        sum2 += powerGame(line);
    });
    console.log("part two =", sum2);
});