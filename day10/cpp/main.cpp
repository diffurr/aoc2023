#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

struct P
{
	int x, y;
};

enum Dir { N, E, S, W, X };
enum Tile { NS, EW, NE, NW, SW, SE, START, DOT, NADA};
const P dirs[] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
const Dir tiles[8][4] = {
	{N,X,S,X},//NS
	{X,E,X,W},//EW
	{X,X,E,N},//NE
	{X,N,W,X},//NW
	{W,S,X,X},//SW
	{E,X,X,S},//SE
	{N,E,S,W},//START
	{X,X,X,X}//DOT
};

struct Map
{
	int w, h, startx, starty;
	std::vector<Tile> data;
	Map() {};
	Map(const std::string &fileName)
	{
		h = 0;
		std::ifstream fs(fileName);
		std::string line;
		while (std::getline(fs, line))
		{
			for (int i = 0; i < line.size(); i++)
			{
				Tile tile;
				switch (line[i])
				{
				case '|':
					tile = NS;
					break;
				case '-':
					tile = EW;
					break;
				case 'L':
					tile = NE;
					break;
				case 'J':
					tile = NW;
					break;
				case '7':
					tile = SW;
					break;
				case 'F':
					tile = SE;
					break;
				case 'S':
					tile = START;
					startx = i;
					starty = h;
					break;
				case '.':
					tile = DOT;
					break;
				}
				data.push_back(tile);
			}
			h++;
		}
		w = (int)line.size();
	}

	Map(int w, int h, Tile init) :
		w(w), h(h), data(w * h, init) {}

	Tile operator()(int x, int y) const
	{
		if (x >= 0 && x < w && y >= 0 && y < h)
		{
			return data[w * y + x];
		}
		return DOT;
	}
	void operator()(int x, int y, Tile tile)
	{
		data[w * y + x] = tile;
	}
};

Tile closeLoop(Dir firstd, Dir lastd)
{	
	int len = sizeof(tiles) / sizeof(tiles[0]);
	for (int i = 0; i < len; i++)
	{
		if (tiles[i][lastd] == firstd)
		{
			return (Tile)i;
		}
	}
}

int follow(const Map& map, Map& loopMap, int x, int y, Dir dir)
{
	int dist = 0;
	Dir firstd = dir;
	for (;;)
	{
		int nx = x + dirs[dir].x;
		int ny = y + dirs[dir].y;
		loopMap(x, y, map(x, y));
		Dir ndir = tiles[map(nx, ny)][dir];
		if (ndir != Dir::X)
		{
			x = nx;
			y = ny;
			dist++;
			if (map(x, y) == Tile::START)
			{
				loopMap(x, y, closeLoop(firstd, dir));
				return dist / 2;
			}
			dir = ndir;
		}
		else
		{
			return -1;
		}
	}
}

int countInside(const Map& map)
{
	int count = 0;
	for (int y = 0; y < map.h; y++)
	{
		bool inside = false;
		Tile prev = NADA;
		for (int x = 0; x < map.w; x++)
		{
			Tile tile = map(x, y);
			if (tile == NS) { inside = !inside; }
			else if (tile == NW && prev == SE) { inside = !inside; }
			else if (tile == SW && prev == NE) { inside = !inside; }
			else if (inside && tile == NADA) { count++; }
			if (tile != EW) { prev = tile; }
		}
	}
	return count;
}

std::tuple<int, Map> loop(const Map& map)
{	
	for (int dir = Dir::N; dir != Dir::X; dir++)
	{
		Map loopMap(map.w, map.h, Tile::NADA);
		int dist = follow(map, loopMap, map.startx, map.starty, (Dir)dir);
		if (dist > 0)
		{
			return { dist, loopMap };
		}
	}
}

std::tuple<int, int> solution(const Map& map)
{
	int dist;
	Map loopMap;
	std::tie(dist, loopMap) = loop(map);
	int inside = countInside(loopMap);
	return { dist, inside };
}

int main()
{
	int part1, part2;
	std::tie(part1, part2) = solution(Map("..\\input.txt"));
	std::cout << "part1 = " << part1 << "\n";
	std::cout << "part2 = " << part2 << "\n";
	return 0;
}