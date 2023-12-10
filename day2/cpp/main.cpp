#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int playGame(const std::string &line)
{
    int pos = line.find(':') + 1;
    int id = std::stoi(line.substr(line.find(' '), pos), nullptr);
    std::istringstream sets(line.substr(pos, line.size()));
    for (std::string set; std::getline(sets, set, ';'); ) {
        int blue = 0, green = 0, red = 0;
        std::istringstream elems(set);
        for (std::string elem; std::getline(elems, elem, ',') ;) {
            int delim = elem.find_last_of(' ');
            int val = std::stoi(elem.substr(0, delim), nullptr);
            std::string color = elem.substr(delim + 1, elem.size());
            if (color == "blue") {
                blue += val;
            } else if (color == "green") {
                green += val;
            } else {
                red += val;
            }
        }
        if ((red > 12) || (green > 13) || (blue > 14)) {
            return 0;
        }
    }
    return id;
}

int powerGame(const std::string &line)
{
    int blue = 1, green = 1, red = 1;
    int pos = line.find(':') + 1;
    std::istringstream sets(line.substr(pos, line.size()));
    for (std::string set; std::getline(sets, set, ';'); ) {
        std::istringstream elems(set);
        for (std::string elem; std::getline(elems, elem, ',') ;) {
            int delim = elem.find_last_of(' ');
            int val = std::stoi(elem.substr(0, delim), nullptr);
            std::string color = elem.substr(delim + 1, elem.size());
            if (color == "blue") {
                blue = (val > blue) ? val : blue;
            } else if (color == "green") {
                green = (val > green) ? val : green;
            } else {
                red = (val > red) ? val : red;
            }
        }
    }
    return blue * green * red;
}

int main()
{
    std::ifstream input("..\\input.txt");
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

//Part One
    int sum = 0;
    for(const std::string &line : lines) {
        sum += playGame(line);
    }
    printf("part one = %d\n", sum);

//Part Two
    sum = 0;
    for(const std::string &line : lines) {
        sum += powerGame(line);
    }
    printf("part two = %d\n", sum);

    return 0;
}