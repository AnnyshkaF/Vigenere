#include "Statistics.h"

Statistics::Statistics()
{
	unsigned char symbol = 0;
	for (int i = 0; i < 256; i++)
	{
		alphabet[i] = unsigned char(symbol);
		alpha.insert(std::make_pair(unsigned char(symbol), i));
		symbol++;
	}
	/*
	int j = 0;
	for (int i = 255; i > -1; i--)
	{
		alphabet[j] = unsigned char(i);
		alpha.insert(std::make_pair(unsigned char(i), j));
		j++;
	}
	*/
}

Statistics::~Statistics()
{
}

std::map<unsigned char, int> Statistics::CalculateStatistics(std::vector<unsigned char> text)
{
	std::map<unsigned char, int> map;
	int size = text.size();
	
	for (int i = 0; i < 256; i++)
	{
		map.insert(std::pair<unsigned char, int>(alphabet[i], 0));
	}
	for (size_t i = 0; i < text.size(); i++)
	{
		int tmp = map[text[i]];
		tmp++;
		map.insert_or_assign(text[i], tmp);
	}
	return map;
}
std::map<unsigned char, int> Statistics::CalculateStatisticsInOrder(std::vector<unsigned char> text)
{
	std::map<unsigned char, int> map;
	int size = text.size();

	for (int i = 0; i < 256; i++)
	{
		map.insert(std::pair<unsigned char, int>(alphabet[i], 0));
	}
	for (size_t i = 0; i < text.size(); i++)
	{
		int tmp = map[text[i]];
		tmp++;
		map.insert_or_assign(text[i], tmp);
	}
	return map;
}

double Statistics::CalculateIndexOfCoincidence(std::vector<unsigned char> text)
{
	auto map = CalculateStatistics(text);
	float index = 0;
	int size = text.size();
	for (auto it = map.begin(); it != map.end(); ++it)
	{
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

unsigned char Statistics::getLetter(int number)
{
	return alphabet[number];
}

int Statistics::getLetterNumber(unsigned char letter)
{
	return alpha.find(letter)->second;
}

