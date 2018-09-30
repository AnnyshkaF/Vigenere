#pragma once
#include <map>
#include <iostream>

class Statistics
{
public:
	char alphabet[95];

							Statistics();
							~Statistics();
	std::map<char, int>		CalculateStatistics(std::string text);
	std::string				MakeUpcaseNoSpaces(std::string text);
	double					ÑalculateIndexOfCoincidence(std::string text);
	void					ShowStatistics(std::map<char, int> map);
};

