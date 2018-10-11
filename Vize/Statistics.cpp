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
}

Statistics::~Statistics()
{
}

std::map<unsigned char, int> Statistics::calculateStatistics(std::vector<unsigned char> text)
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

double Statistics::calculateIndexOfCoincidence(std::vector<unsigned char> text)
=======
double Statistics::CalculateIndexOfCoincidence(std::vector<unsigned char> text)
>>>>>>> 91e5fd1e8dc62836a3df4de068f94547e2606f7c
{
	auto map = calculateStatistics(text);
	double index = 0;
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

