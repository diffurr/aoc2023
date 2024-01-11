using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace aoc
{
    internal class main
    {
        static List<List<int>> parseInput(string fileName)
        {
            List<List<int>> input = new List<List<int>>();
            StreamReader sr = new StreamReader(fileName);
            string line;
            while ((line = sr.ReadLine()) != null)
            {
                List<int> nums = new List<int>();
                foreach (string strnum in line.Split(' '))
                { 
                    nums.Add(int.Parse(strnum));
                }
                input.Add(nums);
            }
            return input;
        }
        
        static int solution1(List<int> nums)
        {
            if (nums.All(x => x == 0)) { return 0; }
            List<int> subs = new List<int>();
            for (int i = 1; i < nums.Count; i++)
            {
                subs.Add(nums[i] - nums[i - 1]);
            }
            return nums[nums.Count - 1] + solution1(subs);
        }
        static int solution2(List<int> nums)
        {
            if (nums.All(x => x == 0)) { return 0; }
            List<int> subs = new List<int>();
            for (int i = 1; i < nums.Count; i++)
            {
                subs.Add(nums[i] - nums[i - 1]);
            }
            return nums[0] - solution2(subs);
        }

        static int part1(List<List<int>> input)
        {
            int sum = 0;
            foreach(List<int> nums in input)
            {
                sum += solution1(nums);
            }
            return sum;
        }

        static int part2(List<List<int>> input)
        {
            int sum = 0;
            foreach(List<int> nums in input)
            {
                sum += solution2(nums);
            }
            return sum;
        }
        static void show<T1, T2>(string s, Func<T1, T2> func, T1 arg)
        {
            Stopwatch timer = Stopwatch.StartNew();
            T2 res = func(arg);
            timer.Stop();
            Console.WriteLine(String.Format(s + "{0}", res));
            Console.WriteLine(String.Format("time[ms] = {0}", timer.Elapsed.TotalMilliseconds));
        }

        static void Main(string[] args)
        {
            List<List<int>> input = parseInput(@"..\..\..\input.txt");
            Console.WriteLine("part1 = {0}", part1(input));
            Console.WriteLine("part2 = {0}", part2(input));
        }
    }
}
