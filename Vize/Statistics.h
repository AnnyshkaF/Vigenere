#pragma once
#include <map>
#include <vector>
#include <iostream>

class Statistics
{
public:
	std::map<unsigned char, int> alpha;
	unsigned char alphabet[256];

									Statistics();
									~Statistics();
	std::map<unsigned char, int>	CalculateStatistics(std::vector<unsigned char> text);
	std::map<unsigned char, int>	CalculateStatisticsInOrder(std::vector<unsigned char> text);
	double							ÑalculateIndexOfCoincidence(std::vector<unsigned char> text);
	unsigned char					getLetter(int number);
	void							ShowStatistics(std::map<char, int> map);
	int								getLetterNumber(unsigned char letter);
};

