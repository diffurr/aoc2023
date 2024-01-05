#include <algorithm>
#include <cstdio>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

const enum HandType 
{
	HIGH, PAIR1, PAIR2, THREE, FULL, FOUR, FIVE, size = 7
};

//                    2  3  4  5  6  7  8  9  :  ;  <  =  >  ?  @  A   B  C  D  E  F  G  H  I  J  K   L  M  N  O  P  Q   R  S  T
const char Str1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 9, 11, 0, 0, 0, 0, 0, 10, 0, 0, 8 };

//                    2  3  4  5  6  7  8  9  :  ;  <  =  >  ?  @  A   B  C  D  E  F  G  H  I  J  K   L  M  N  O  P  Q   R  S  T
const char Str2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 10, 0, 0, 9 };
const std::string cards = "23456789AKQT";

struct Hand
{
	int str;
	HandType type;
	int bid;
};

int getHandStr1(const std::string& _hand)
{
	int res = 0;
	res |= Str1[_hand[0] - 50] << 16;
	res |= Str1[_hand[1] - 50] << 12;
	res |= Str1[_hand[2] - 50] << 8;
	res |= Str1[_hand[3] - 50] << 4;
	res |= Str1[_hand[4] - 50];
	return res;
}

int getHandStr2(const std::string& _hand)
{
	int res = 0;
	res |= Str2[_hand[0] - 50] << 16;
	res |= Str2[_hand[1] - 50] << 12;
	res |= Str2[_hand[2] - 50] << 8;
	res |= Str2[_hand[3] - 50] << 4;
	res |= Str2[_hand[4] - 50];
	return res;
}
HandType getHandType1(std::string& hand)
{
	std::sort(hand.begin(), hand.end());
	char three = 0;
	char pairs = 0;
	char count = 1;
	for (int i = 0; i < 4; ++i)
	{
		if (hand[i] == hand[i + 1])
		{
			count++;
		}
		else
		{
			switch (count)
			{
			case 4:
				return HandType::FOUR;
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
			}
		}
	}
	switch (count)
	{
	case 5:
		return HandType::FIVE;
	case 4:
		return HandType::FOUR;
	case 3:
		three++;
		break;
	case 2:
		pairs++;
	}
	if (three && pairs) return HandType::FULL;
	if (three) return HandType::THREE;
	if (pairs == 2) return HandType::PAIR2;
	if (pairs == 1) return HandType::PAIR1;
	return HandType::HIGH;
}

HandType getHandType2(std::string& hand)
{
	if (std::find(hand.begin(), hand.end(), 'J') == hand.end())
	{
		return getHandType1(hand);
	}
	int max = -1;
	for (const char c : cards)
	{
		std::string handCopy = hand;
		std::replace(handCopy.begin(), handCopy.end(), 'J', c);
		HandType type = getHandType1(handCopy);
		if (type == HandType::FIVE) return type;
		if (type > max) max = type;
	}
	return (HandType) max;
}

std::string readFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

template <typename F1, typename F2>
std::vector<Hand> parseInput(F1 funcHandStr, F2 funcHandType, const std::string& input)
{
	std::istringstream iss(input);
	std::vector<Hand> hands;
	std::string buffer;
	int val;
	while (iss >> buffer >> val)
	{
		hands.push_back({ funcHandStr(buffer), funcHandType(buffer), val });
	}
	return hands;
}

int solution(std::vector<Hand>& hands)
{
	//sort hands by strength
	std::stable_sort(hands.begin(), hands.end(), [](const Hand& a, const Hand& b) {
		return a.str < b.str;
		});

	//sort hands by type
	std::stable_sort(hands.begin(), hands.end(), [](const Hand &a, const Hand &b) {
		return a.type < b.type;
		});

	//sum bids from each sorted list
	int sum = 0;
	for (int i = 0; i < hands.size(); ++i)
	{
		sum += (i + 1) * hands[i].bid;
	}
	return sum;
}

int part1(const std::string& input)
{
	std::vector<Hand> hands = parseInput(getHandStr1, getHandType1, input);
	return solution(hands);
}

int part2(const std::string& input)
{
	std::vector<Hand> hands = parseInput(getHandStr2, getHandType2, input);
	return solution(hands);
}

int main()
{
	struct timespec start, end;
	std::string input = readFile("..\\input.txt");

	timespec_get(&start, TIME_UTC);
	int res1 = part1(input);
	timespec_get(&end, TIME_UTC);
	printf("part1 = %d\n", res1);
	printf("time[us] = %ld\n", (end.tv_nsec - start.tv_nsec) / 1000);

	timespec_get(&start, TIME_UTC);
	int res2 = part2(input);
	timespec_get(&end, TIME_UTC);
	printf("part2 = %d\n", res2);
	printf("time[us] = %ld\n", (end.tv_nsec - start.tv_nsec) / 1000);
	return 0;
}
