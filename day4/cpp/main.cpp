#include <algorithm>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <string>
#include <tuple>

#define vec std::vector
#define str std::string
#define set std::set
typedef std::tuple<vec<str>, vec<str>> card;

vec<card> readInput(std::ifstream &file)
{
	vec<card> cards;
	str val;
	file >> val;
	while (file >> val) {
		vec<str> wins;
		vec<str> scratch;
		while (file >> val) {
			if (val != "|") {
				wins.push_back(val);
			} else break;
		}
		while (file >> val) {
			if (val != "Card") {
				scratch.push_back(val);
			} else break;
		}
		cards.push_back({ wins, scratch });
	}
	return cards;
}

int partOne(const vec<card> &input)
{
	int sum = 0;
	for (const card &card: input) {
		vec<str> wins = std::get<0>(card);
		vec<str> scratch = std::get<1>(card);
		std::sort(wins.begin(), wins.end());
		std::sort(scratch.begin(), scratch.end());
		vec<str> intersect;
		std::set_intersection(wins.begin(), wins.end(), scratch.begin(), scratch.end(), std::back_inserter(intersect));
		int res = intersect.size();
		if (res > 0) {
			sum += 1 << (res - 1);
		}
	}
	return sum;
}

int partTwo(const vec<card> &input)
{
	vec<int> lucky;
	for (const card &card: input) {
		vec<str> wins = std::get<0>(card);
		vec<str> scratch = std::get<1>(card);
		std::sort(wins.begin(), wins.end());
		std::sort(scratch.begin(), scratch.end());
		vec<str> intersect;
		std::set_intersection(wins.begin(), wins.end(), scratch.begin(), scratch.end(), std::back_inserter(intersect));
		lucky.push_back(intersect.size());
	}
	
	vec<int> cardnum(lucky.size(), 1);
	for (int i = 0; i < cardnum.size(); i++) {
		for (int j = i + 1; j < i + 1 + lucky[i]; j++) {
			cardnum[j] += cardnum[i];
		}
	}

	int sum = 0;
	for (int val : cardnum) {
		sum += val;
	}
	return sum;
}

int main()
{
	std::ifstream file("..\\input.txt");
    struct timespec start, end;

    timespec_get(&start, TIME_UTC);
	const vec<card> input = readInput(file);
    timespec_get(&end, TIME_UTC);
	printf("input read[us] = %d\n", (end.tv_nsec - start.tv_nsec) / 1000);

    timespec_get(&start, TIME_UTC);
	int res1 = partOne(input);
    timespec_get(&end, TIME_UTC);
	printf("part one = %d\n", res1);
	printf("time[us] = %d\n", (end.tv_nsec - start.tv_nsec) / 1000);

    timespec_get(&start, TIME_UTC);
	int res2 = partTwo(input);
    timespec_get(&end, TIME_UTC);
	printf("part one = %d\n", res2);
	printf("time[us] = %d\n", (end.tv_nsec - start.tv_nsec) / 1000);
	return 0;
}