#include <algorithm>
#include <cstdio>
#include <climits>
#include <ctime>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define vec std::vector
typedef std::string str;

struct Range
{
	int64_t start, end;
};

struct Map
{
	int64_t start, end, slide;
};

struct Input
{
	vec<int64_t> seeds;
	vec<vec<Map>> maps;
};

Input readInput(const std::string& fname)
{
	std::ifstream input(fname);
	str buffer;
	vec<int64_t> seeds;
	vec<vec<Map>> maps;

	std::getline(input, buffer);
	std::stringstream ss(buffer);
	int64_t val;
	ss >> buffer;
	while (ss >> val) {
		seeds.push_back(val);
	}

	while (std::getline(input, buffer)) {
		if (std::isalpha(buffer[0])) {
			vec<Map> map;
			while (std::getline(input, buffer) && std::isdigit(buffer[0])) {
				std::stringstream ss(buffer);
				int64_t src, dst, len;
				ss >> dst;
				ss >> src;
				ss >> len;
				map.push_back({ src, src + len - 1, dst - src });
			}
			maps.push_back(map);
		}
	}
	return { seeds = seeds, maps = maps };
}

int64_t filterSand(const vec<vec<Map>>& maps, const Range &range)
{
	vec<Range> ranges;
	ranges.push_back(range);
	for (const vec<Map>& map : maps) {
		vec<Range> newRanges;
		while (ranges.size()) {
			Range range = ranges.back();
			ranges.pop_back();
			int64_t rs = range.start;
			int64_t re = range.end;
			bool passed = false;
			for (const Map& xform : map) {
				int64_t ms = xform.start;
				int64_t me = xform.end;
				int64_t s = xform.slide;
				if ((rs < ms) && (re < ms)) {
					passed = true;
				}
				else if ((rs > me) && (re > me)) {
					passed = true;
				}
				else if ((rs < ms) && (re >= ms)) {
					ranges.push_back({ rs, ms - 1 });
					newRanges.push_back({ ms + s, re + s });
					passed = false;
					break;
				}
				else if ((rs >= ms) && (re > me)) {
					ranges.push_back({ me + 1, re });
					newRanges.push_back({ rs + s, me + s});
					passed = false;
					break;
				}
				else {
					newRanges.push_back({ rs + s, re + s});
					passed = false;
					break;
				}
			}
			if (passed) {
				newRanges.push_back(range);
			}
		}
		ranges = newRanges;
	}
	std::sort(ranges.begin(), ranges.end(), [](const Range& r1, const Range& r2) { return r1.start < r2.start; });
	return ranges[0].start;
}

int64_t partOne(const Input& input)
{
	int64_t min = INT64_MAX;
	for (const int64_t seed : input.seeds) {
		int64_t res = filterSand(input.maps, { seed, seed });
		if (res < min) {
			min = res;
		}
	}
	return min;
}

int64_t partTwo(const Input& input)
{
	int64_t min = INT64_MAX;
	for (int i = 0; i < input.seeds.size(); i += 2) {
		int64_t res = filterSand(input.maps, {input.seeds[i], input.seeds[i] + input.seeds[i + 1] - 1});
		if (res < min) {
			min = res;
		}
	}
	return min;
}

int main()
{
	struct timespec start, end;

	timespec_get(&start, TIME_UTC);
	Input data = readInput("..\\input.txt");
	timespec_get(&end, TIME_UTC);
	printf("input read[us] = %ld\n", (end.tv_nsec - start.tv_nsec) / 1000);

	timespec_get(&start, TIME_UTC);
	int64_t res = partOne(data);
	timespec_get(&end, TIME_UTC);
	printf("partOne = %lld\n", res);
	printf("time[us] = %ld\n", (end.tv_nsec - start.tv_nsec) / 1000);

	timespec_get(&start, TIME_UTC);
	int64_t res2 = partTwo(data);
	timespec_get(&end, TIME_UTC);
	printf("partTwo = %lld\n", res2);
	printf("time[us] = %ld\n", (end.tv_nsec - start.tv_nsec) / 1000);
	return 0;
}