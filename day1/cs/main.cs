using System;
using System.IO;

class Aoc
{
    static string[] digits = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    static void Main(string[] args) {
        if (args.Length == 0) {
            System.Console.WriteLine("usage: main.exe inputfile");
            Console.WriteLine(args.Length);
            return; 
        }   

        string[] lines = File.ReadAllLines(args[0]);
        int sum = 0;

        foreach(string line in lines) {
            int firstNum = -1;
            int lastNum = -1;
            foreach(char c in line) {
                if (Char.IsDigit(c)) {
                    if (firstNum < 0) {
                        firstNum = lastNum = c - '0';
                    } else {
                        lastNum = c - '0';
                    }
                }
            }
            sum += firstNum * 10 + lastNum;
        }
        Console.WriteLine(string.Format("Part One Sum = {0}", sum));

        sum = 0;
        foreach(string line in lines) {
            int firstNum = -1;
            int lastNum = -1;
            for(int i = 0; i < line.Length; i++) {
                if (char.IsDigit(line[i])) {
                    if (firstNum < 0) {
                        firstNum = lastNum = line[i] - '0';
                    } else {
                        lastNum = line[i] - '0';
                    }
                } else {
                    for(int j = 0; j < digits.Length; j++) {
                        if ((digits[j].Length <= line.Length - i) && 
                        (line.IndexOf(digits[j], i, digits[j].Length) >= 0)) {
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
        Console.WriteLine(string.Format("Part Two Sum = {0}", sum));
    }
}

