#pragma once
#include <map>
#include <vector>
#include <iostream>

class Statistics
{
public:
	unsigned char alphabet[256];
	std::map<unsigned char, int> alpha;

									Statistics();
									~Statistics();
	std::map<unsigned char, int>	CalculateStatistics(std::vector<unsigned char> text);
	//std::map<int, unsigned char>	getStatisticsFromFile(char* filename());
	double							CalculateIndexOfCoincidence(std::vector<unsigned char> text);
	std::map<unsigned char, int> 	CalculateStatisticsInOrder(std::vector<unsigned char> text);
	void							ShowStatistics(std::map<char, int> map);
	unsigned char					getLetter(int number);
	int								getLetterNumber(unsigned char letter);
};

