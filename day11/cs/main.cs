using int64 = System.Int64;

static (List<bool>, List<bool>) getInput(string[] lines)
{
    List<bool> vflag = new List<bool>(Enumerable.Repeat(true, lines[0].Length));
    List<bool> hflag = new List<bool>();

    foreach(ReadOnlySpan<char> line in lines)
    {
        bool empty = true;
        for (int i = 0; i < line.Length; i++)
        {
            if (line[i] == '#')
            {
                vflag[i] = false;
                empty = false;
            }
        }
        if (empty) { hflag.Add(true); }
        else { hflag.Add(false); }
    }
    return (vflag, hflag);
}

static int64 path(string[] lines, List<bool> vflag, List<bool> hflag, int scale)
{
    Stack<P> planets = new Stack<P>();
    int64 maxh = 0;
    for (int h = 0; h < lines.Length; h++)
    {
        int64 maxw = 0;
        ReadOnlySpan<char> line = lines[h];
        for (int i = 0; i < line.Length; i++)
        {
            if (vflag[i])
            {
                maxw += scale;
            }
            else
            {
                if (line[i] == '#')
                {
                    planets.Push(new P(maxw, maxh));
                }
                maxw += 1;
            }
        }
        if (hflag[h]) { maxh += scale; }
        else { maxh += 1; }
    }

    int64 sum = 0;
    while (planets.Count > 0)
    {
        P p1 = planets.Pop();
        foreach (P p2 in planets)
        {
            sum += Math.Abs(p2.x - p1.x) + Math.Abs(p2.y - p1.y);
        } 
    }
    return sum;
}

static (int64, int64) solution(string[] lines)
{
    (var vflag, var hflag) = getInput(lines);
    int64 part1 = path(lines, vflag, hflag, 2);
    int64 part2 = path(lines, vflag, hflag, 1_000_000);
    return (part1, part2);
}

//-----------------------------------------------------------
string[] lines = File.ReadAllLines(@"..\..\..\..\input.txt");
(int64 part1, int64 part2) = solution(lines);
Console.WriteLine("part1 = {0}", part1);
Console.WriteLine("part2 = {0}", part2);
//-----------------------------------------------------------

record P(int64 x, int64 y);