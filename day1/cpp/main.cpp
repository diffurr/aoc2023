#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct Digit {
    const char* str;
    int len;
};

struct Digit digits[] = {
    { "one", 3},
    { "two", 3},
    { "three", 5},
    { "four", 4},
    { "five", 4},
    { "six", 3},
    { "seven", 5},
    { "eight", 5},
    { "nine", 4}   
};

int main(int argc, char **argv)
{   
    if (argc < 2) {
        printf("usage: main.exe inputfile\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "rt");
    if (fp == NULL) {
        printf("can't open %s\n", argv[1]);
        return 1;
    }

//part One
    char line[256];
    int sum = 0;
    while (fgets(line, sizeof(line), fp)) {
        int firstNum = -1;
        int lastNum = -1;
        for (int i = 0; i < strlen(line); i++) {
            if (isdigit(line[i])) {
                if (firstNum < 0) {
                    firstNum = lastNum = line[i] - 0x30;
                } else {
                    lastNum = line[i] - 0x30;
                }
            }
        }
        sum += firstNum * 10 + lastNum;
    }
    printf ("part one sum = %d\n", sum);

//part Two
    sum = 0;
    fseek(fp, 0, SEEK_SET);
    while (fgets(line, sizeof(line), fp)) {
        int firstNum = -1;
        int lastNum = -1;
        for (int i = 0; i < strlen(line); i++) {
            if (isdigit(line[i])) {
                if (firstNum < 0) {
                    firstNum = lastNum = line[i] - 0x30;
                } else {
                    lastNum = line[i] - 0x30;
                }
            } else {
                for (int j = 0; j < (sizeof(digits) / sizeof(Digit)); j++) {
                    if (!strncmp(&line[i], digits[j].str, digits[j].len)) {
                        if (firstNum < 0) {
                            firstNum = lastNum = j + 1;
                        } else {
                            lastNum = j + 1;
                        }
                        break;
                    }
                }
            }
        }
        sum += firstNum * 10 + lastNum;
    }
    printf("part two sum = %d\n", sum);
    return 0;
}