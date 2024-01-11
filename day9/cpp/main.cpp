#include <algorithm>
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>

std::vector<std::vector<int>> getInput(const std::string& fileName)
{
	std::vector<std::vector<int>> input;
	std::ifstream file(fileName);
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<int> nums;
		std::istringstream is(line);
		int num;
		while (is >> num)
		{
			nums.push_back(num);
		}
		input.push_back(nums);
	}
	return input;
}

int extraEnd(const std::vector<std::vector<int>> &triangle)
{
	int sum = 0;
	for (const std::vector<int>& nums : triangle)
	{
		sum += nums.back();
	}
	return sum;
}

int extraBegin(const std::vector<std::vector<int>>& triangle)
{
	int sum = 0;
	bool flip = true;
	for (const std::vector<int> &nums : triangle)
	{
		if (flip) { sum += nums[0]; }
		else { sum -= nums[0]; }
		flip = !flip;
	}
	return sum;
}

template <typename T>
int solution(const std::vector<int> &nums, T extra)
{
	std::vector<std::vector<int>> triangle;
	triangle.push_back(nums);
	for (;;)
	{
		const std::vector<int> &last = triangle.back();
		std::vector<int> subs;
		for (int i = 1; i < last.size(); ++i)
		{
			subs.push_back(last[i] - last[i - 1]);
		}
		triangle.push_back(subs);
		bool allZero = true;
		for (const int num : subs)
		{
			allZero = allZero && !num;
		}
		if (allZero) break;
	}
	return extra(triangle);
}

int part1(const std::vector<std::vector<int>>& input)
{
	int sum = 0;
	for (const std::vector<int>& nums : input)
	{
		sum += solution(nums, extraEnd);
	}
	return sum;
}

int part2(const std::vector<std::vector<int>>& input)
{
	int sum = 0;
	for (const std::vector<int>& nums : input)
	{
		sum += solution(nums, extraBegin);
	}
	return sum;
}

int main()
{
	std::vector<std::vector<int>> input = getInput("..\\input.txt");
	std::cout << "part1 = " << part1(input) << "\n";
	std::cout << "part2 = " << part2(input) << "\n";
	return 0;
}