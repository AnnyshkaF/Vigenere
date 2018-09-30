#include "Statistics.h"

Statistics::Statistics()
{
	int symbol = 32;
	for (int i = 0; i < 95; i++)
	{
		alphabet[i] = char(symbol);
		symbol++;
	}
}

Statistics::~Statistics()
{
}

std::string Statistics::MakeUpcaseNoSpaces(std::string text)
{
	std::string newString;
	for (size_t i = 0; i < text.length(); i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
		{
			text[i] -= 32;
			newString.push_back(text[i]);
			continue;
		}
		if (text[i] >= 'A' && text[i] <= 'Z')
		{
			newString.push_back(text[i]);
		}
	}
	return newString;
}

std::map<char, int> Statistics::CalculateStatistics(std::string text)
{
	std::map<char, int> map;
	int size = text.length();
	
	for (char i = 0; i < 92; i++)
	{
		map.insert(std::pair<char, int>(alphabet[i], 0));
	}
	for (size_t i = 0; i < text.length(); i++)
	{
		int tmp = map[text[i]];
		tmp++;
		map.insert_or_assign(text[i], tmp);
	}
	return map;
}

double Statistics::ÑalculateIndexOfCoincidence(std::string text)
{
	auto map = CalculateStatistics(text);
	float index = 0;
	int size = text.length();
	std::map<char, int>::iterator it;
	for (it = map.begin(); it != map.end(); ++it)
	{
		//double p = ((double)it->second*(it->second - 1) / (size*(size-1)));
		double p = (double)it->second / size;
		index += p * p;
	}
	return index;
}

void Statistics::ShowStatistics(std::map<char, int> map)
{
	std::map<char, int>::iterator it;
	for (it = map.begin(); it != map.end(); ++it)
	{
		std::cout << it->first << " = " << it->second << std::endl;
	}
}