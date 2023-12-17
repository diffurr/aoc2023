
using System.Diagnostics;

List<string> readNumStr(string line, int start, int end)
{
    List<string> list = new List<string>();
    char[] buff = new char[10];
    int count = 0;

    for (int i = start; i < end; i++)
    {
        if (Char.IsDigit(line[i]))
        {
            buff[count++] = line[i];
        } else if (count > 0)
        {
            list.Add(new string(buff, 0, count));
            count = 0;
        }
    }
    if (count > 0)
    {
        list.Add(new string(buff, 0, count));
    }
    return list;
}

List<string> readNumStr2(string line, int start, int end)
{
    List<string> list = new List<string>();

    string[] nums = line.Substring(start, end - start).Split(' ');
    foreach (string str in nums)
    {
        if (str != "") { list.Add(str); }
    }
    return list;
}
List<Card> readInput(string file)
{
    List<Card> cards = new List<Card>();
    List<string> wins = new List<string>();
    List<string> scratch = new List<string>();

    string line;
    StreamReader sr = new StreamReader(file);
    while ((line = sr.ReadLine()) != null)
    {
        int pos1 = line.IndexOf(':');
        int pos2 = line.IndexOf('|');
        wins = readNumStr2(line, pos1 + 1, pos2);
        scratch = readNumStr2(line, pos2 + 1, line.Length);
        cards.Add(new Card { wins = wins,  scratch = scratch });
    }
    return cards;
}

int partOne(List<Card> cards)
{
    int sum = 0;
    foreach (Card card in cards)
    {
        List<string> intersect = new List<string>(card.scratch.Intersect(card.wins));
        int res = intersect.Count;
        if (res > 0) { sum += 1 << (res - 1); }
    }
    return sum;
}

int partTwo(List<Card> cards)
{    
    List<int> lucky = new List<int>();

    foreach (Card card in cards)
    {
        List<string> intersect = new List<string>(card.scratch.Intersect(card.wins));
        lucky.Add(intersect.Count);
    }

    int[] cardnum = new int[lucky.Count];
    Array.Fill(cardnum, 1);
    for (int i = 0; i < cardnum.Length; i++)
    {
        for (int j = i + 1; j < i + 1 + lucky[i]; j++)
        {
            cardnum[j] += cardnum[i];
        }
    }

    int sum = 0;
    foreach (int val in cardnum)
    {
        sum += val;
    }
    return sum;
}

Stopwatch timer = new Stopwatch();

timer.Start();
List<Card> input = readInput(@"..\..\..\..\input.txt");
timer.Stop();
Console.WriteLine(String.Format("loading time[us] = {0}", timer.Elapsed.TotalMicroseconds));

timer.Restart();
int res1 = partOne(input);
timer.Stop();
Console.WriteLine(String.Format("part one = {0}", res1));
Console.WriteLine(String.Format("time[us] = {0}", timer.Elapsed.TotalMicroseconds));

timer.Restart();
int res2 = partTwo(input);
timer.Stop();
Console.WriteLine(String.Format("part two = {0}", res2));
Console.WriteLine(String.Format("time[us] = {0}", timer.Elapsed.TotalMicroseconds));
struct Card
{
    public List<string> wins;
    public List<string> scratch;
};

