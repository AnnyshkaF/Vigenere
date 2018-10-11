#pragma once
#include <map>
#include <vector>
#include <iostream>

class Statistics
{
public:
	std::map<unsigned char, int> alpha;
	unsigned char alphabet[256];

<<<<<<< HEAD
									Statistics();
									~Statistics();
	std::map<unsigned char, int>	calculateStatistics(std::vector<unsigned char> text);
	double							calculateIndexOfCoincidence(std::vector<unsigned char> text);
	void							ShowStatistics(std::map<char, int> map);
	unsigned char					getLetter(int number);
	int								getLetterNumber(unsigned char letter);
=======
					Statistics();
					~Statistics();
	std::map<unsigned char, int>	CalculateStatistics(std::vector<unsigned char> text);
	std::map<unsigned char, int>	CalculateStatisticsInOrder(std::vector<unsigned char> text);
	double				CalculateIndexOfCoincidence(std::vector<unsigned char> text);
	unsigned char			getLetter(int number);
	void				ShowStatistics(std::map<char, int> map);
	int				getLetterNumber(unsigned char letter);
>>>>>>> 91e5fd1e8dc62836a3df4de068f94547e2606f7c
};

