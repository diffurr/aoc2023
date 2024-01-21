#include <fstream>
#include <iostream>
#include <tuple>
#include <cmath>
#include <ctime>
#include <string>
#include <string_view>
#include <vector>

typedef long long int64;
typedef std::vector<std::string_view> Lines;
typedef std::vector<bool> Bools;
struct P
{
	int64 x, y;
};

Lines splitLines(const std::string& str)
{
	Lines lines;
	char split = '\n';
	std::string::size_type pos1 = 0;
	std::string::size_type pos2 = 0;
	while ((pos2 = str.find(split, pos1)) != std::string::npos) {
		lines.push_back(std::string_view(str).substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
	};
	if (pos1 < str.length()) {
		lines.push_back(std::string_view(str).substr(pos1));
	}
	return lines;
}

std::tuple<Bools, Bools> getInput(const Lines& lines)
{
	Bools vflag(lines[0].length(), true);
	Bools hflag;

	for (const auto &line : lines)
	{
		bool empty = true;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '#') 
			{
				vflag[i] = false;
				empty = false;
			}
		}
		if (empty) { hflag.push_back(true); }
		else { hflag.push_back(false); }
	}
	return { vflag, hflag };
}

int64 path(const Lines& lines,
	const Bools &vflag, 
	const Bools &hflag, 
	const int scale)
{
	std::vector<P> planets;
	int64 maxh = 0;
	size_t lineLen = lines[0].length();
	for (int h = 0; h < lines.size(); h++)
	{
		int64 maxw = 0;
		const auto& line = lines[h];
		for (int i = 0; i < lineLen; i++)
		{
			if (vflag[i]) {
				maxw += scale;
			}
			else {
				if (line[i] == '#') {
					planets.push_back({ maxw, maxh });
				}
				maxw += 1;
			}
		}
		if (hflag[h]) { maxh += scale; }
		else { maxh += 1; }
	}

	int64 sum = 0;
	while (planets.size() > 0) {
		P p1 = planets.back();
		planets.pop_back();
		for (const auto &p2 : planets) {
			sum += abs(p2.x - p1.x) + abs(p2.y - p1.y);
		}
	}
	return sum;
}

std::tuple<int64, int64> solution(const std::string& fileName)
{
	std::ifstream file(fileName);
	std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	const Lines lines = splitLines(input);
	const auto [vflag, hflag] = getInput(lines);
	int64 part1 = path(lines, vflag, hflag, 2);
	int64 part2 = path(lines, vflag, hflag, 1000000);
	return { part1, part2 };
}

int main()
{
	const auto [part1, part2] = solution("..\\input.txt");
	std::cout << "part1 = " << part1 << "\n";
	std::cout << "part2 = " << part2 << "\n";
	return 0;
}