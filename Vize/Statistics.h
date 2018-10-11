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
	std::map<unsigned char, int>	calculateStatistics(std::vector<unsigned char> text);
	double							calculateIndexOfCoincidence(std::vector<unsigned char> text);
	void							ShowStatistics(std::map<char, int> map);
	unsigned char					getLetter(int number);
	int								getLetterNumber(unsigned char letter);
};

