int playGame(string line)
{
    string[] splits = line.Split(':');
    int id = Int32.Parse(splits[0].Split(' ')[1]);
    foreach (string set in splits[1].Split(';')) {
        int red = 0, green = 0, blue = 0;
        foreach (string elem in set.Split(',')) {
            string[] tokens = elem.Split(' ');
            int val = Int32.Parse(tokens[1]);
            switch(tokens[2]) {
                case "red":
                    red += val;
                    break;
                case "green":
                    green += val;
                    break;
                case "blue":
                    blue += val;
                    break;
            }
        }
        if ( (red > 12) || (green > 13) || (blue > 14) ) {
            return 0;
        }
    }
    return id;
}

int powerGame(string line)
{
    int red = 1, green = 1, blue = 1;
    string[] splits = line.Split(':');
    foreach (string set in splits[1].Split(';')) {
        foreach (string elem in set.Split(',')) {
            string[] tokens = elem.Split(' ');
            int val = Int32.Parse(tokens[1]);
            switch(tokens[2]) {
                case "red":
                    red = (val > red) ? val : red;
                    break;
                case "green":
                    green = (val > green) ? val : green;
                    break;
                case "blue":
                    blue = (val > blue) ? val : blue;
                    break;
            }
        }
    }
    return red * green * blue;
}

string[] lines = File.ReadAllLines(@"..\..\..\..\input.txt");

//Part One
int sum1 = 0;
foreach (string line in lines) {
    sum1 += playGame(line);
}
Console.WriteLine(string.Format("part one = {0}", sum1));

//Part Two
int sum2 = 0;
foreach (string line in lines) {
    sum2 += powerGame(line);
}
Console.WriteLine(string.Format("part two = {0}", sum2));