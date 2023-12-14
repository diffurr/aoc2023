#include <cmath>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <string>

bool findSymbol(const std::vector<std::string> &input, int line, int pos, int len)
{
    std::stringstream symbols;
    for (int i = pos - 1; i <= pos + len; i++) {
        symbols << input[line-1][i];
        symbols << input[line+1][i];
    }
    symbols << input[line][pos-1];
    symbols << input[line][pos+len];

    for (const char &c : symbols.str()) {
        if (std::ispunct(c) && c != '.') {
            return true;
        }
    }
    return false;
}

int findGear(const std::vector<std::string> &input, int line, int pos, int len)
{
    int span = input[line].size();

    for (int i = pos - 1; i <= pos + len; i++) {
        if (input[line-1][i] == '*') { return ((line-1) * span + i); }
    }
    for (int i = pos - 1; i <= pos + len; i++) {
        if (input[line+1][i] == '*') { return ((line+1) * span + i); }
    }
    if (input[line][pos-1] == '*') { return (line * span + pos - 1); }
    if (input[line][pos+len] == '*') { return (line * span + pos + len); }

    return -1;
}

int partOne(const std::vector<std::string> &input)
{
    int sum = 0;

    for (int line = 0; line < input.size(); line++) {
        for (int pos = 0; pos < input[line].size(); pos++) {
            if (std::isdigit(input[line][pos])) {
                int num = atoi(&input[line].c_str()[pos]);
                int ndigs = log10(num) + 1;
                if (findSymbol(input, line, pos, ndigs)) {
                    sum += num;
                }
                pos += ndigs;
            }
        }
    }
    return sum;
}

int partTwo(const std::vector<std::string> &input)
{
    std::map<int, std::vector<int>> gears;

    for (int line = 0; line < input.size(); line++) {
        for (int pos = 0; pos < input[line].size(); pos++) {
            if (std::isdigit(input[line][pos])) {
                int num = atoi(&input[line].c_str()[pos]);
                int ndigs = log10(num) + 1;
                int gearid = findGear(input, line, pos, ndigs);
                if (gearid >= 0) {
                    gears[gearid].push_back(num);
                }
                pos += ndigs;
            }
        }
    }

    int sum = 0;
    for (const std::pair<int, std::vector<int>> &key : gears) {
        if (key.second.size() == 2) {
            sum += key.second[0] * key.second[1];
        }
    }
    return sum;
}

std::vector<std::string> readInput(std::stringstream &ss)
{
    std::vector<std::string> lines;
    std::string buffer;
    std::stringstream extraline;

    std::getline(ss, buffer);
    for (int i = 0; i < buffer.size() + 2; i++) {
        extraline << '.';
    }
    lines.push_back(extraline.str());
    lines.push_back('.' + buffer + '.');
    while (std::getline(ss, buffer)) {
        std::stringstream line;
        line << '.' << buffer << '.';
        lines.push_back(line.str());
    }
    lines.push_back(extraline.str());

    return lines;
}

int main()
{
    std::string test = "467..114..\n" \
                        "...*......\n" \
                        "..35..633.\n" \
                        "......#...\n" \
                        "617*......\n" \
                        ".....+.58.\n" \
                        "..592.....\n" \
                        "......755.\n" \
                        "...$.*....\n" \
                        ".664.598..\n";

    struct timespec start, end;
    std::stringstream ss;
    std::ifstream file("..\\input.txt");
    ss << file.rdbuf();
    //ss << test;
    std::vector<std::string> input = readInput(ss);

    timespec_get(&start, TIME_UTC);
    printf("part one = %d\n", partOne(input));
    timespec_get(&end, TIME_UTC);
    printf("time[us]= %d\n", (end.tv_nsec - start.tv_nsec) / 1000);

    timespec_get(&start, TIME_UTC);
    printf("part two = %d\n", partTwo(input));
    timespec_get(&end, TIME_UTC);
    printf("time[us]= %d\n", (end.tv_nsec - start.tv_nsec) / 1000);
    
    return 0;
}