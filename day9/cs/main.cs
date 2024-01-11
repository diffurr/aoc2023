using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace aoc
{
    internal class main
    {
        delegate int Extra(List<List<int>> triangle);

        static int extraEnd(List<List<int>> triangle)
        {
            int sum = 0;
            foreach (List<int> nums in triangle)
            {
                sum += nums[nums.Count - 1];
            }
            return sum;
        }

        static int extraBegin(List<List<int>> triangle)
        {
            bool flip = true;
            int sum = 0;
            foreach (List<int> nums in triangle)
            {
                if (flip) sum += nums[0];
                else sum -= nums[0];
                flip = !flip;
            }
            return sum;
        }

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
        
        static int solution(List<int> nums, Extra extra)
        {
            List<List<int>> triangle = new List<List<int>>();
            triangle.Add(nums);
            while (true)
            {
                List<int> subs = new List<int>();
                for (int i = 1, last = triangle.Count - 1; i < triangle[last].Count; i++)
                {
                    subs.Add(triangle[last][i] - triangle[last][i - 1]);
                }
                triangle.Add(subs);
                if (subs.All(x => x == 0)) { break; }
            }
            return extra(triangle);
        }

        static int part1(List<List<int>> input)
        {
            int sum = 0;
            foreach(List<int> nums in input)
            {
                sum += solution(nums, extraEnd);
            }
            return sum;
        }

        static int part2(List<List<int>> input)
        {
            int sum = 0;
            foreach(List<int> nums in input)
            {
                sum += solution(nums, extraBegin);
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
