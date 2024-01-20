int[,] dirs = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };
Dir[,] tiles =
{
    {Dir.N, Dir.X, Dir.S, Dir.X },
    {Dir.X, Dir.E, Dir.X, Dir.W },
    {Dir.X, Dir.X, Dir.E, Dir.N },
    {Dir.X, Dir.N, Dir.W, Dir.X },
    {Dir.W, Dir.S, Dir.X, Dir.X },
    {Dir.E, Dir.X, Dir.X, Dir.S },
    {Dir.N, Dir.E, Dir.S, Dir.W },
    {Dir.X, Dir.X, Dir.X, Dir.X }
};

int follow(Map map, Map loopMap, int x, int y, Dir dir)
{
    int dist = 0;
    Dir firstd = dir;
    while(true)
    {
        int nx = x + dirs[(int)dir, 0];
        int ny = y + dirs[(int)dir, 1];
        loopMap.set(x, y, map.get(x, y));
        Dir ndir = tiles[(int)map.get(nx, ny), (int)dir];
        if (ndir != Dir.X)
        {
            x = nx;
            y = ny;
            dist++;
            if (map.get(x, y) == Tile.START)
            {
                loopMap.set(x, y, closeLoop(firstd, ndir));
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

Tile closeLoop(Dir firstd, Dir lastd)
{
    for (int i = 0; i < tiles.Length; i++)
    {
        if (tiles[i, (int)lastd] == firstd)
        {
            return (Tile)i;
        }
    }
    return Tile.NADA;
}

(int, Map?) loop(Map map)
{
    foreach(Dir dir in Enum.GetValues(typeof(Dir)))
    {
        Map loopMap = new Map(map.w, map.h, Tile.NADA);
        int dist = follow(map, loopMap, map.startx, map.starty, dir);
        if (dist >= 0)
        {
            return (dist, loopMap);
        }
    }
    return (0, null);
}

int countInside(Map? map)
{
    int count = 0;
    for (int y = 0; y < map.h; y++)
    {
        bool inside = false;
        Tile prev = Tile.NADA;
        for (int x = 0; x < map.w; x++)
        {
            Tile tile = map.get(x, y);
            if (tile == Tile.NS) { inside = !inside; }
            else if (tile == Tile.NW && prev == Tile.SE) { inside = !inside; }
            else if (tile == Tile.SW && prev == Tile.NE) { inside = !inside; }
            else if (inside && tile == Tile.NADA) { count++; }
            if (tile != Tile.EW) { prev = tile; }
        }
    }
    return count;
}

(int, int) solution(Map map)
{
    (int dist, Map? loopMap) = loop(map);
    int inside = countInside(loopMap);
    return (dist, inside);
}

//----------------------------------------------
(int part1, int part2) = solution(new Map(@"..\..\..\..\..\input.txt"));
Console.WriteLine("part1 = {0}", part1);
Console.WriteLine("part2 = {0}", part2);
//----------------------------------------------

enum Tile { NS, EW, NE, NW, SW, SE, START, DOT, NADA }
enum Dir { N, E, S, W, X }

class Map
{
    public int w, h, startx, starty;
    public List<Tile> data;
    public Map(string fileName)
    {
        string[] lines = File.ReadAllLines(fileName);
        data = new List<Tile>();
        h = 0;
        w = lines[0].Length;
        foreach (ReadOnlySpan<char> line in lines)
        {
            for (int i = 0; i < line.Length; i++) 
            {
                Tile tile = Tile.NADA;
                switch (line[i])
                {
                    case '|':
                        tile = Tile.NS; break;
                    case '-':
                        tile = Tile.EW; break;
                    case 'L':
                        tile = Tile.NE; break;
                    case 'J':
                        tile = Tile.NW; break;
                    case '7':
                        tile = Tile.SW; break;
                    case 'F':
                        tile = Tile.SE; break;
                    case 'S':
                        tile = Tile.START;
                        startx = i;
                        starty = h;
                        break;
                    case '.':
                        tile = Tile.DOT; break; 
                }
                data.Add(tile);
            }
            h++;
        }
    }
    public Map(int _w, int _h, Tile init)
    {
        w = _w;
        h = _h;
        data = new List<Tile>(new Tile[w * h]);
        for (int i = 0; i < data.Count; i++)
        {
            data[i] = init;
        }
    }

    public Tile get(int x, int y)
    {
        if (x >= 0 && x < w && y >= 0 && y < h)
        {
            return data[w * y + x];
        }
        return Tile.DOT;
    }

    public void set(int x, int y, Tile tile)
    {
        data[w * y + x] = tile;
    }
}