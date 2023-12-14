using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System;

List<string> readInput(string input)
{
    StreamReader sr = new StreamReader(input);
    List<string> lines = new List<string>();
    StringBuilder line = new StringBuilder();
    string extraline;
    string buffer;

    buffer = sr.ReadLine();
    for (int i = 0; i < buffer.Length + 2; i++) {
        line.Append('.');
    }
    extraline = line.ToString();

    lines.Add(extraline);
    lines.Add('.' + buffer + '.');
    line.Clear();
    while ((buffer = sr.ReadLine()) != null) {
        line.Append('.');
        line.Append(buffer);
        line.Append('.');
        lines.Add(line.ToString());
        line.Clear();
    }
    lines.Add(extraline);

    return lines;
}

bool isSym(char c)
{
    return ((c >= '!' && c <= '-') || ( c == '/') || (c >= ':' && c <= '@')); 
}

bool findSymbol(List<string> lines, int line, int pos, int len)
{
    StringBuilder symbols = new StringBuilder();
    for (int i = pos - 1; i <= pos + len; i++) {
        symbols.Append(lines[line - 1][i]);
        symbols.Append(lines[line + 1][i]);
    }
    symbols.Append(lines[line][pos - 1]);
    symbols.Append(lines[line][pos + len]);

    foreach(char c in symbols.ToString()) {
        if (isSym(c)) {
            return true;
        }
    }
    return false;
}

int findGear(List<string> lines, int line, int pos, int len)
{
    int span = lines[line].Length;

    for (int i = pos - 1; i <= pos + len; i++) {
        if (lines[line - 1][i] == '*') { return ((line - 1) * span + i); }
    }
    for (int i = pos - 1; i <= pos + len; i++) {
        if (lines[line + 1][i] == '*') { return ((line + 1) * span + i); }
    }
    if (lines[line][pos - 1] == '*') { return (line * span + pos - 1); }
    if (lines[line][pos + len] == '*') { return (line * span + pos + len); }

    return -1;
}

int partOne(List<string> lines)
{
    int sum = 0;
    for (int line = 0; line < lines.Count; line++) {
        for (int pos = 0; pos < lines[line].Length; pos++) {
            if (Char.IsDigit(lines[line][pos])) {
                string numstr = "" + lines[line][pos];
                int ndigs = 1;
                while (Char.IsDigit(lines[line][++pos])) {
                    numstr += lines[line][pos];
                    ndigs++;
                }
                int num = Int32.Parse(numstr);
                if (findSymbol(lines, line, pos - ndigs, ndigs)) {
                    sum += num;
                }
            }
        }
    }
    return sum;
}

int partTwo(List<string> lines)
{
    Dictionary<int, List<int>> gears = new Dictionary<int, List<int>>();

    for (int line = 0; line < lines.Count; line++) {
        for (int pos = 0; pos < lines[line].Length; pos++) {
            if (Char.IsDigit(lines[line][pos])) {
                string numstr = "" + lines[line][pos];
                int ndigs = 1;
                while (Char.IsDigit(lines[line][++pos])) {
                    numstr += lines[line][pos];
                    ndigs++;
                }
                int num = Int32.Parse(numstr);
                int gearid = findGear(lines, line, pos - ndigs, ndigs);
                if (gearid >= 0) {
                    if (!gears.ContainsKey(gearid)) {
                        gears.Add(gearid, new List<int>(){num});
                    } else {
                        gears[gearid].Add(num);
                    }
                }
            }
        }
    }

    int sum = 0;
    foreach(List<int> val in gears.Values) {
        if (val.Count == 2) {
            sum += val[0] * val[1];
        }
    }
    return sum;
}

List<string> input = readInput(@"..\..\..\..\input.txt");
Stopwatch timer = new Stopwatch();

timer.Start();
int res1 = partOne(input);
timer.Stop();
Console.WriteLine(String.Format("part one = {0}", res1));
Console.WriteLine(String.Format("time[us] = {0}", timer.Elapsed.TotalMicroseconds));

timer.Restart();
int res2 = partTwo(input);
timer.Stop();
Console.WriteLine(string.Format("part two = {0}", res2));
Console.WriteLine(String.Format("time[us] = {0}", timer.Elapsed.TotalMicroseconds));