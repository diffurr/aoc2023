#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using vstr = std::vector<std::string>;
using vint = std::vector<int>;
using vint64 = std::vector<long long>;
using str = std::string;
using int64 = long long;

vstr readLines(const str &fileName)
{
	std::ifstream file(fileName);
	vstr lines;
	str line;
	while (std::getline(file, line)) {
		lines.push_back(line);
	}
	return lines;
}

vint lineToNums(const str &line)
{
	vint nums;
	std::istringstream iss(line);
	str trash;
	int val;
	iss >> trash;
	while (iss >> val) {
		nums.push_back(val);
	}
	return nums;
}

int64 lineToNum(const str& line)
{
	std::stringstream ss;
	std::istringstream iss(line);
	str strnum;
	int64 num;
	iss >> strnum;
	while (iss >> strnum) {
		ss << strnum;
	}
	ss >> num;
	return num;
}

int64 calcLow(int64 t, int64 d)
{
	double val = (t - sqrt((t * t) - 4 * d)) / 2;
	return (val == (int64)val) ? (int64)val + 1 : (int64)ceil(val);
}

int64 calcHi(int64 t, int64 d)
{
	double val = (t + sqrt((t * t) - 4 * d)) / 2;
	return (val == (int64)val) ? (int64)val - 1 : (int64)floor(val);
}

int64 part1(const vstr& lines)
{
	vint times = lineToNums(lines[0]);
	vint dists = lineToNums(lines[1]);

	int64 res = 1;
	for (int i = 0; i < times.size(); i++) {
		int64 low = calcLow(times[i], dists[i]);
		int64 hi = calcHi(times[i], dists[i]);
		res *= hi - low + 1;
	}
	return res;
}

int64 part2(const vstr& lines)
{
	int64 time = lineToNum(lines[0]);
	int64 dist = lineToNum(lines[1]);

	int64 low = calcLow(time, dist);
	int64 hi = calcHi(time, dist);
	return hi - low + 1;
}

int main()
{
	vstr lines = readLines("..\\input.txt");
	struct timespec start, end;

	timespec_get(&start, TIME_UTC);
	int64 res = part1(lines);
	timespec_get(&end, TIME_UTC);
	printf("part1 = %lld\n", res);
	printf("time[us] = %ld\n", (end.tv_nsec - start.tv_nsec) / 1000);

	timespec_get(&start, TIME_UTC);
	res = part2(lines);
	timespec_get(&end, TIME_UTC);
	printf("part2 = %lld\n", res);
	printf("time[us] = %ld\n", (end.tv_nsec - start.tv_nsec) / 1000);

	return 0;
}