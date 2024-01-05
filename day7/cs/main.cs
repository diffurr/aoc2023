using System.Diagnostics;

Type getHandType1(string _hand)
{
    char[] hand = _hand.ToArray();
    Array.Sort(hand);
    int three = 0;
    int pairs = 0;
    int count = 1;
    for (int i = 0; i < hand.Length - 1; i++)
    {
        if (hand[i] == hand[i + 1])
        {
            count++;
        }
        else
        {
            switch (count)
            {
                case 4: return Type.FOUR;
                case 3:
                    three++;
                    count = 1;
                    break;
                case 2:
                    pairs++;
                    count = 1;
                    break;
                default:
                    count = 1;
                    break;
            }
        }
    }
    switch (count)
    {
        case 5: return Type.FIVE;
        case 4: return Type.FOUR;
        case 3:
            three++;
            break;
        case 2:
            pairs++;
            break;
    }
    if (three > 0 && pairs > 0) return Type.FULL;
    if (three > 0) return Type.THREE;
    if (pairs == 2) return Type.PAIR2;
    if (pairs == 1) return Type.PAIR1;
    return Type.HIGH;
}

Type getHandType2(string _hand)
{
    const string cards = "23456789AKQT";
    if (_hand.IndexOf('J') == -1)
    {
        return getHandType1(_hand);
    }
    int max = -1;
    foreach (char c in cards)
    {
        string newHand = _hand.Replace('J', c);
        Type type = getHandType1(newHand);
        if (type == Type.FIVE)
        {
            return type;
        }
        if ((int)type > max) max = (int)type;
    }
    return (Type)max;
}

int card2Val(char c)
{
    if (c >= '2' && c <= '9')
    {
        return c - 50;
    }
    else
    {
        switch (c)
        {
            case 'T': return 8;
            case 'J': return 9;
            case 'Q': return 10;
            case 'K': return 11;
            case 'A': return 12;
        }
    }
    return -1;
}

int joker(char c)
{
    if (c >= '2' && c <= '9')
    {
        return c - 49;
    }
    else
    {
        switch (c)
        {
            case 'T': return 9;
            case 'J': return 0;
            case 'Q': return 10;
            case 'K': return 11;
            case 'A': return 12;
        }
    }
    return -1;
}

int getHandStr(ref string _hand, CardVal cardVal)
{
    int res = 0;
    res |= cardVal(_hand[0]) << 16;
    res |= cardVal(_hand[1]) << 12;
    res |= cardVal(_hand[2]) << 8;
    res |= cardVal(_hand[3]) << 4;
    res |= cardVal(_hand[4]);
    return res;
}

List<Hand> parseInput(string[] lines, CardVal cardVal, HandType handType)
{
    List<Hand> hands = new List<Hand>();
    foreach (string line in lines)
    {
        ReadOnlySpan<char> span = line.AsSpan();
        string hand = span.Slice(0, 5).ToString();
        int bid = int.Parse(span.Slice(6));
        hands.Add(new Hand { 
            str = getHandStr(ref hand, cardVal),
            type = handType(hand), 
            bid = bid 
        });
    }
    return hands;
}

int solution(List<Hand> hands)
{
    IEnumerable<Hand> final = hands.OrderBy(hand => hand.str).OrderBy(hand => hand.type);

    int sum = 0;
    int idx = 1;
    foreach (Hand hand in final)
    {
        sum += idx++ * hand.bid;
    }
    return sum;
}

int part1(string[] lines)
{
    List<Hand> hands = parseInput(lines, card2Val, getHandType1);
    return solution(hands);
}

int part2(string[] lines)
{
    List<Hand> hands = parseInput(lines, joker, getHandType2);
    return solution(hands);
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
show<string[], int>("part1 = ", part1, lines);
show<string[], int>("part2 = ", part2, lines);

struct Hand
{
    public int str;
    public Type type;
    public int bid;
}

enum Type
{
	HIGH, PAIR1, PAIR2, THREE, FULL, FOUR, FIVE
}

delegate int CardVal(char c);
delegate Type HandType(string _hand);
