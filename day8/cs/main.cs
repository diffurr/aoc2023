using System.Diagnostics;
using System.Numerics;
using Nodes = System.Collections.Generic.Dictionary<short, Node>;

void solution<T1, T2>(string s, Func<T1, T2> func, T1 arg)
{
    Stopwatch timer = Stopwatch.StartNew();
    T2 res = func(arg);
    timer.Stop();
    Console.WriteLine(String.Format(s + "{0}", res));
    Console.WriteLine(String.Format("time[us] = {0}", timer.Elapsed.TotalMicroseconds));
}

short c2n(ReadOnlySpan<char> chars)
{
    int num = 0;
    num |= (chars[0] - 65) << 10;
    num |= (chars[1] - 65) << 5;
    num |= (chars[2] - 65);
    return (short)num;
}

//long gcd(long x, long y)
//{
//    while (x != y)
//    {
//        if (x > y) x -= y;
//        else y -= x;
//    }
//    return x;
//}
long gcd(long x, long y)
{
    return (long)BigInteger.GreatestCommonDivisor(x, y);
}

long lcm(long x, long y)
{
    return (x * y) / gcd(x, y);
}

Input parseInput(string[] lines)
{
    Nodes nodes = new Nodes();
    string dirs = lines[0];

    ReadOnlySpan<string> _lines = new ReadOnlySpan<string>(lines[2..]);
    foreach (ReadOnlySpan<char> _line in _lines)
    {
        nodes.Add(
            c2n(_line.Slice(0, 3)),
            new Node(c2n(_line.Slice(7, 3)), c2n(_line.Slice(12, 3)))
            );
    }
    return new Input(dirs, nodes);
}

int part1(Input input)
{
    short currNode = c2n("AAA");
    short zzz = c2n("ZZZ");
    int step = 0;
    int i = 0;
    while(true) 
    {
        if (currNode == zzz) break;
        else
        {
            currNode = input.dirs[i] == 'L'
                ? input.nodes[currNode].left
                : input.nodes[currNode].right;
        }
        i = ++i % input.dirs.Length;
        step++;
    }
    return step;
}

long part2(Input input)
{
    List<short> nodesA = new List<short>();
    foreach (short n in input.nodes.Keys)
    {
        //zero bits 5:10
        if ((n & 0x1f) == 0)
        {
            nodesA.Add(n);
        }
    }

    long total = 1;
    foreach (short node in nodesA)
    {
        short currNode = node;
        int step = 0;
        int i = 0;
        while (true)
        {
            //zero bits 5:10 and check if equal 'Z'
            if ((currNode & 0x1f) == 25) break;
            else
            {
                currNode = input.dirs[i] == 'L'
                    ? input.nodes[currNode].left
                    : input.nodes[currNode].right;
            }
            i = ++i % input.dirs.Length;
            step++;
        }
        total = lcm(total, step);
    }
    return total;
}

Input input = parseInput(File.ReadAllLines(@"..\..\..\..\input.txt"));
solution("part1 = ", part1, input);
solution("part2 = ", part2, input);


readonly struct Node
{
    readonly public short left;
    readonly public short right;
    public Node(short _left, short _right)
    {
        left = _left;
        right = _right;
    }
}

class Input
{
    public readonly string dirs;
    public Nodes nodes;
    public Input(string _dirs, Nodes _nodes)
    {
        this.dirs = _dirs;
        this.nodes = _nodes;
    }
}