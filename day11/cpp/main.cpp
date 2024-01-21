#define STB_DS_IMPLEMENTATION
#include <fstream>
#include <iostream>
#include <tuple>
#include <cmath>
#include <ctime>
#include "stb_ds.h"
#include "bstrlib.h"
#include "bstrwrap.h"

typedef long long int64;
struct P
{
	int64 x, y;
};

size_t fsWrap(void* buff, size_t esz, size_t eqty, void* parm)
{
	std::fstream *input = (std::fstream*)parm;
	input->read((char*)buff, esz * eqty);
	return input->gcount();
}

std::tuple<bool*, bool*> getInput(const Bstrlib::CBStringList& lines)
{
	bool *vflag = nullptr, *hflag = nullptr;
	arrsetlen(vflag, lines[0].length());
	memset(vflag, true, arrlen(vflag));

	for (const auto &line : lines)
	{
		bool empty = true;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '#') 
			{
				vflag[i] = 0;
				empty = false;
			}
		}
		if (empty) { arrput(hflag, true); }
		else { arrput(hflag, false); }
	}
	return { vflag, hflag };
}

int64 path(const Bstrlib::CBStringList& lines, const bool* vflag, const bool* hflag, const int scale)
{
	P* planets = nullptr;
	int64 maxh = 0;
	size_t lineLen = lines[0].length();

	for (int h = 0; h < lines.size(); h++)
	{
		int64 maxw = 0;
		const char* line = (const char*)lines[h].data;
		for (int i = 0; i < lineLen; i++)
		{
			if (vflag[i]) {
				maxw += scale;
			}
			else {
				if (line[i] == '#') {
					P p = { maxw, maxh };
					arrput(planets, p);
				}
				maxw += 1;
			}
		}
		if (hflag[h]) { maxh += scale; }
		else { maxh += 1; }
	}

	int64 sum = 0;
	while (arrlen(planets) > 0) {
		P p1 = arrpop(planets);
		for (int i = 0; i < arrlen(planets); i++) {
			P p2 = planets[i];
			sum += abs(p2.x - p1.x) + abs(p2.y - p1.y);
		}
	}
	return sum;
}

std::tuple<int64, int64> solution(const Bstrlib::CBString& fileName)
{
	std::ifstream input(fileName);
	Bstrlib::CBStream bs((bNread) fsWrap, &input);
	Bstrlib::CBStringList lines;
	lines.split(bs.read(), "\n");
	
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
