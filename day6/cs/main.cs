//algebraic solution from reddit u/themanushiya
using System.Diagnostics;

int[] lineToNums(string line)
{
    int[] nums = line.Substring(line.IndexOf(':') + 1)
        .Trim(' ')
        .Split(' ')
        .Where(x => x.Length > 0)
        .Select(x => int.Parse(x))
        .ToArray();
    return nums;
}

long lineToNum(string line)
{
    string numstr = line.Substring(line.IndexOf(':') + 1)
        .Trim(' ')
        .Split(' ')
        .Where(x => x.Length > 0)
        .Aggregate("", (x , y) => x + y);
    return long.Parse(numstr);
}

long calcLow(long t, long d)
{
    double val = (t - Math.Sqrt((t * t) - 4 * d)) / 2;
    return (val == (long)val) ? (long)val + 1 : (long)Math.Ceiling(val);
}

long calcHi(long t, long d)
{
    double val = (t + Math.Sqrt((t * t) - 4 * d)) / 2;
    return (val == (long)val) ? (long)val - 1 : (long)Math.Floor(val);
}

long part1(string[] lines)
{
    int[] times = lineToNums(lines[0]);
    int[] dists = lineToNums(lines[1]);

    long res = 1;
    for (int i = 0; i < times.Length; i++)
    {
        long low = calcLow(times[i], dists[i]);
        long hi = calcHi(times[i], dists[i]);
        res *= hi - low + 1;
    }
    return res;
}

long part2(string[] lines)
{
    long time = lineToNum(lines[0]);
    long dist = lineToNum(lines[1]);

    long low = calcLow(time, dist);
    long hi = calcHi(time, dist);
    return hi - low + 1;
}
void show<T1, T2>(string s, Func<T1, T2> func, T1 arg)
{
    Stopwatch timer = Stopwatch.StartNew();
    T2 res = func(arg);
    timer.Stop();
    Console.WriteLine(String.Format(s + "{0}", res));
    Console.WriteLine(String.Format("time[us] = {0}", timer.Elapsed.TotalMicroseconds));
}

string[] lines = File.ReadAllLines(@"..\..\..\..\input.txt");
show<string[], long>("part1 = ", part1, lines);
show<string[], long>("part2 = ", part2, lines);
