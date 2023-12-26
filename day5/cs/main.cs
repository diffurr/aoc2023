using System.Diagnostics;
using Map = System.Collections.Generic.List<Xform>;

Input readInput(string fileName)
{
    List<Map> maps = new List<Map>();
    StreamReader sr = new StreamReader(fileName);
    string line;

    line = sr.ReadLine();
    long[] seeds = line.Replace("seeds: ", "").Split(' ').Select(x => long.Parse(x)).ToArray();

    Map map = new Map(); 
    while ((line = sr.ReadLine()) != null)
    {
        if (line.Length == 0) continue;
        if (Char.IsLetter(line[0]))
        {
            if (map.Count > 0)
            {
                maps.Add(map);
                map = new Map();
                continue;
            }
        } 
        else
        {
            long[] nums = line.Split(' ').Select(x => long.Parse(x)).ToArray();
            long dst = nums[0];
            long src = nums[1];
            long len = nums[2];
            map.Add(new Xform() { start = src, end = src + len - 1, slide = dst - src });
        }
    }
    maps.Add(map);

    return new Input() { seeds = seeds, maps = maps };
}

long filterSand(List<Map> maps, Range _range)
{
    Stack<Range> ranges = new Stack<Range>();
    ranges.Push(_range);
    foreach (Map map in maps)
    {
        Stack<Range> newRanges = new Stack<Range>(32);
        while (ranges.Count > 0)
        {
            Range range = ranges.Pop();
            long rs = range.start;
            long re = range.end;
            bool passed = true;
            foreach (Xform xform in map)
            {
                long ms = xform.start;
                long me = xform.end;
                long s = xform.slide;
                if ((rs < ms) && (re < ms)) {}
                else if ((rs > me) && (re > me)) {}
                else if ((rs < ms) && (re >= ms))
                {
                    ranges.Push(new Range() { start = rs, end = ms - 1 });
                    newRanges.Push(new Range() { start = ms + s, end = re + s });
                    passed = false;
                    break;
                }
                else if ((rs >= ms) && (re > me))
                {
                    ranges.Push(new Range() { start = me + 1, end = re });
                    newRanges.Push(new Range() { start = rs + s, end = me + s });
                    passed = false;
                    break;
                }
                else
                {
                    newRanges.Push(new Range() { start = rs + s, end = re + s });
                    passed = false;
                    break;
                }
            }
            if (passed)
            {
                newRanges.Push(range);
            }
        }
        ranges = newRanges;
    }

    List<Range> sortedRanges = ranges.ToList();
    sortedRanges.Sort(delegate (Range r1, Range r2)
    {
        return (r1.start < r2.start) ? -1 : 1;
    });
    return sortedRanges[0].start;
}
long filterSandSimple(List<Map> maps, long seed)
{
    foreach (Map map in maps)
    {
        foreach (Xform xform in map)
        {
            if (seed >= xform.start && seed <= xform.end)
            {
                seed += xform.slide;
                break;
            }
            else { continue; }
            break;
        }
    }
    return seed;
}
long partOne(Input input)
{
    long min = long.MaxValue;
    foreach (long seed in input.seeds)
    {
        long res = filterSandSimple(input.maps, seed);
        if (res < min)
        {
            min = res;
        }
    }
    return min;
}

long partTwo(Input input)
{
    long min = long.MaxValue;
    for (int i = 0; i < input.seeds.Length; i += 2)
    {
        long res = filterSand(input.maps, new Range() { 
            start = input.seeds[i], end = input.seeds[i] + input.seeds[i + 1] - 1 });
        if (res < min)
        {
            min = res;
        }
    }
    return min;
}

void show<T1, T2>(string s, Func<T1, T2> func, T1 arg)
{
    Stopwatch timer = new Stopwatch();
    timer.Start();
    T2 res = func(arg);
    timer.Stop();
    s += "{0}";
    Console.WriteLine(String.Format(s, res));
    Console.WriteLine(String.Format("time[us] = {0}", timer.Elapsed.TotalMicroseconds));
}
T2 measure<T1, T2>(string s, Func<T1, T2> func, T1 arg)
{
    Stopwatch timer = new Stopwatch();
    timer.Start();
    T2 res = func(arg);
    timer.Stop();
    Console.WriteLine(s);
    Console.WriteLine(String.Format("time[us] = {0}", timer.Elapsed.TotalMicroseconds));
    return res;
}

Input input = measure<string, Input>("loading", readInput, @"..\..\..\..\..\input.txt");
show<Input, long>("part one = ", partOne, input);
show<Input, long>("part two = ", partTwo, input);


struct Range
{
    public long start, end;
}
struct Xform
{
    public long start, end, slide;
}
struct Input
{
    public long[] seeds;
    public List<Map> maps;
}
