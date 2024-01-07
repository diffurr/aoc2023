#include <ctime>
#include <fstream>
#include <unordered_map>
#include <numeric>
#include <string>
#include <string_view>
#include <iostream>
#include <vector>

using int64 = long long;
struct Node
{
	std::string left;
	std::string right;
};
struct Input
{
	std::string dirs;
	std::unordered_map<std::string, Node> nodes;
};

const Input getInput(const std::string &fileName)
{
	std::ifstream file(fileName);
	std::string dirs;
	std::unordered_map<std::string, Node> nodes;
	std::string buffer;
	std::getline(file, dirs);
	std::getline(file, buffer);
	while (std::getline(file, buffer)) {
		nodes[buffer.substr(0, 3)] = { buffer.substr(7, 3), buffer.substr(12, 3) };
	}
	return { dirs, nodes };
}

int part1(const Input& input)
{
	std::string_view currNode = "AAA";
	int step = 0;
	int i = 0;
	for (;;)
	{
		if (currNode == "ZZZ") { break; }
		else if (input.dirs[i] == 'L')
		{
			currNode = (*input.nodes.find(currNode.data())).second.left;
		}
		else 
		{
			currNode = (*input.nodes.find(currNode.data())).second.right;
		}
		i = ++i % input.dirs.size();
		step++;
	}
	return step;
}

int64 part2(const Input& input)
{
	std::vector<std::string_view> nodesA;
	std::vector<int> steps;

	for (auto const &n : input.nodes)
	{
		if (n.first[2] == 'A')
		{
			nodesA.push_back(n.first);
		}
	}
	for (auto const& node : nodesA)
	{
		std::string_view currNode = node;
		int step = 0;
		int i = 0;
		for (;;)
		{
			if (currNode[2] == 'Z') { break; }
			else if (input.dirs[i] == 'L')
			{
				currNode = (*input.nodes.find(currNode.data())).second.left;
			}
			else
			{
				currNode = (*input.nodes.find(currNode.data())).second.right;
			}
			i = ++i % input.dirs.size();
			step++;
		}
		steps.push_back(step);
	}
	
	int64 res = 1;
	for (int step: steps)
	{
		res = std::lcm(res, step);
	}
	return res;
}

template <typename F, typename T>
void solution(std::string msg, F func, T arg)
{
	struct timespec start, end;
    timespec_get(&start, TIME_UTC);
	int64 res = func(arg);
	timespec_get(&end, TIME_UTC);
	std::cout << msg << res << std::endl;
	std::cout << "time[us] = " << (end.tv_nsec - start.tv_nsec) / 1000 << std::endl;
}

int main()
{
	const Input input = getInput("..\\input.txt");
	solution("part1 = ", part1, input);
	solution("part2 = ", part2, input);
	return 0;
}
