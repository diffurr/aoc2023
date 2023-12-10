function isDigit(c) {
    return c >= '0' && c <= '9';
}

const fs = require('fs');
fs.readFile('../input.txt', 'utf8', function (err, data) {
    if (err) {
        console.error(err);
        return;
    }
    let lines = data.split('\n');

//PART ONE    
    let sum = 0;
    lines.forEach((line) => {
        let firstNum = -1;
        let lastNum = -1;
        for (let i = 0; i < line.length; i++) {
            if (isDigit(line[i])) {
                if (firstNum < 0) {
                    firstNum = lastNum = line[i] - '0';
                } else {
                    lastNum = line[i] - '0';
                }
            }
        }
        sum += firstNum * 10 + lastNum;
    });
    console.log("Part One sum: ", sum);    

//PART TWO
    function replaceAt(str, pos, ch) {
        chars = str.split('');
        chars[pos] = ch;
        str = chars.join('');
        return str;
    }
    let digits = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];

    sum = 0;
    lines.forEach((line) => {
        let firstNum = -1;
        let lastNum = -1;
        let newline = line.slice();
        digits.forEach((digit, index) => {
            let pos = line.indexOf(digit);
            if (pos >= 0) {
                newline = replaceAt(newline, pos, index+1);
            }
            pos = line.lastIndexOf(digit);
            if (pos >= 0) {
                newline = replaceAt(newline, pos, index+1);
            }
        })
        for (let i = 0; i < newline.length; i++) {
            if (isDigit(newline[i])) {
                if (firstNum < 0) {
                    firstNum = lastNum = newline[i] - '0';
                } else {
                    lastNum = newline[i] - '0';
                }
            }
        }
        sum += firstNum * 10 + lastNum;
    })    
    console.log("Part Two sum: ", sum);  
});
