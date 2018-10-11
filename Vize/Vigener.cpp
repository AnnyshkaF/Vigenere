#include "Vigener.h"
#include <algorithm>  
#include <list>
#include <string>
#include<map>

void showVector(std::vector<unsigned char> v)
{
	for (auto i : v)
	{
		if (i == '\r') continue;
		std::cout << i;
	}
	std::cout << std::endl;
}

Vigener::Vigener()
{
}

Vigener::~Vigener()
{
}

std::vector<unsigned char> Vigener::readFromFile(const char* filename) {
	std::string line;
	std::vector<unsigned char> text;
	std::ifstream file(filename);
	if (file.is_open()) 
	{
		while (std::getline(file, line)) 
		{
			int i = 0;
			while (i < line.length())
			{
				text.push_back(line[i]);
				i++;
			}
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file.";
	}
	return text;
}

unsigned char Vigener::shiftForward(unsigned char letter, unsigned char shift)
{
	//c[i] = m[i] + k[i] mod(N)
	int shifting = statistics.getLetterNumber(shift);
	unsigned char result = statistics.getLetter(getModulus((statistics.getLetterNumber(letter) + shifting), statistics.alpha.size()));
	return result;
}

unsigned char Vigener::shiftBack(unsigned char letter, unsigned char shift)
{
	//m[i] = c[i] - k[i] mod(N)
	int shifting =  statistics.getLetterNumber(shift);
	unsigned char result = statistics.getLetter(getModulus((statistics.getLetterNumber(letter) - shifting), statistics.alpha.size()));
	return result ;
}

std::vector<unsigned char> Vigener::encrypt(std::vector<unsigned char> text, std::vector<unsigned char> key)
{
	int text_length = text.size();
	int key_length = key.size();
	for (int text_var = 0; text_var < text_length;)
	{
		for (int key_var = 0; key_var < key_length; key_var++)
		{
			text[text_var] = shiftForward(text[text_var], key[key_var]);
			text_var++;
			if (text_var == text_length)
			{
				break;
			}
		}
	}
	return text;
}

std::vector<unsigned char> Vigener::selectText(std::vector<unsigned char> text, int step, int start)
{
	std::vector<unsigned char> newText;
	for (size_t i = start; i < text.size(); i += step)
	{
		newText.push_back(text[i]);
	}
	return newText;
}

double Vigener::calculateIndexOfCoincidence(std::vector<unsigned char> text)
{
	double index = statistics.ÑalculateIndexOfCoincidence(text);
	return index;
}

bool isLocalMaximum(std::map<int, float>::iterator it)
{
	--it;
	float a1 = it->second; ++it;
	float a2 = it->second; ++it;
	float a3 = it->second;
	if (a2 > a1 && a2 > a3)
	{
		return true;
	}
	return false;
}

int Vigener::findKeyLength(std::vector<unsigned char> entext)
{
	int n = entext.size() / 40;	//min = 512
	std::map<int, double> map;
	//calculate ic's
	for (int i = 0; i < n; i++)
	{
		std::vector<unsigned char> currentSelectedText1 = selectText(entext, i+1, 0);
 		double ic1 = calculateIndexOfCoincidence(currentSelectedText1);
		std::vector<unsigned char> currentSelectedText2 = selectText(entext, i+2, 0);
		double ic2 = calculateIndexOfCoincidence(currentSelectedText2);
		std::vector<unsigned char> currentSelectedText3 = selectText(entext, i+3, 0);
		double ic3 = calculateIndexOfCoincidence(currentSelectedText3);
	
		if (ic2 > ic1 && ic2 > ic3 && ic2 > 0.06) {
			map.insert(std::pair<int, double>(i+2, ic2));
		}
		//std::cout << "select_" << i << " = " << ic1 << std::endl;
	}
	if (map.size() != 0)
	{
		if (map.begin()->first > 5)
		{
			return map.begin()->first;
		}
	}
	
	/*	comparison between indexes of numbers through gcd	*/
	std::map<int, int> divs;	//massive of letter usage
	for (auto stayer = map.begin(); stayer != map.end(); ++stayer)
	{
		for (auto walker = map.begin(); walker != map.end(); ++walker)
		{
			if (stayer != walker)
			{
				int d = gcd(stayer->first, walker->first);
				auto old = divs.find(d);
				if (old != divs.end())//element exists
				{
					old->second++;
				}
				else 
				{
					divs.insert(std::pair<int, int>(d, 1));
				}
			}
		}
	}
	int mkey = 0;
	if (findMaxValue(divs) <= 5) 
	{
		//return findMaxValue(divs);
		int mkey = findMaxValue(divs);
	}
	int key = findMaxDifference(map);
	if (mkey > key) { return mkey; }
	return key;
}

int Vigener::findMaxValue(std::map<int, int> divs)
{
	divs.erase(1);
	divs.erase(2);
	std::map<int, int>::iterator max = divs.begin();
	for (auto it = divs.begin(); it != divs.end(); ++it)
	{
		if (it->second > max->second)
		{
			max = it;
		}
	}
	return max->first;
}

int Vigener::findMaxDifference(std::map<int, double> divs)	//difference between the most using letters
{
	double* array = new double[divs.size()];
	int i = 0, max_index = 0;
	double max = 0;
	for (auto it = divs.begin(); it != divs.end(); ++it)
	{
		array[i] = it->second / it->first;
		if (array[i] > max)
		{
			max = array[i];
			max_index = it->first;
		}
	}
	delete[] array;
	return max_index;
}

int Vigener::gcd(int x, int y)
{
	if (x < y)
	{
		std::swap(x, y);
	}
	while (y > 0)
	{
		int f = x % y;
		x = y;
		y = f;
	}
	return x;
}

std::vector<unsigned char> Vigener::decrypt(std::vector<unsigned char> text, std::vector<unsigned char> key)
{
	int text_length = text.size();
	int key_length = key.size();
	for (int text_var = 0; text_var < text_length;)
	{
		for (int key_var = 0; key_var < key_length; key_var++)
		{
			text[text_var] = shiftBack(text[text_var], key[key_var]);
			text_var++;
			if (text_var == text.size())
			{
				break;
			}
		}
	}
	return text;
}

unsigned char Vigener::getModulus(unsigned char a, int modulus) 
{
	if (modulus == 0)
	{
		return a;
	}
	if (a >= 0)
	{
		a = a % modulus;
	}
	if(a < 0)
	{
		while (a < 0)
		{
			a = a + modulus;
		}
	}
	return a;
}



std::vector<unsigned char> Vigener::solveEndryptedUsingFrequenyAnalyse(const char* filestat, std::vector<unsigned char> entext, int keysize)
{
	std::multimap<int, unsigned char> stat_freqs;
	std::multimap<int, unsigned char> en_freqs;
	std::vector<unsigned char> statText = readFromFile(filestat);
	std::map<unsigned char, int> stat = statistics.CalculateStatistics(statText);
	for (auto it = stat.begin(); it != stat.end(); ++it)
	{
		stat_freqs.insert(std::make_pair(it->second, it->first));
	}
	
	std::vector<unsigned char> key;
	for (int i = 0; i < keysize; ++i)
	{
		std::vector<unsigned char> currentText = selectText(entext, keysize, i);
		std::map<unsigned char, int> stats = statistics.CalculateStatistics(currentText);
		//selected_text statistics
		for (auto it = stats.begin(); it != stats.end(); ++it)
		{
			en_freqs.insert(std::make_pair(it->second, it->first));
		}
		//(old letter , new letter)
		std::multimap<unsigned char, unsigned char> swap;
		auto enit = en_freqs.begin();
		auto it = stat_freqs.begin();
		for (; it != stat_freqs.end(); ++it)
		{
			swap.insert(std::make_pair(enit->second, it->second));	
			enit++;
		}
		it--; enit--;
		key.push_back(statistics.getLetter(getModulus(statistics.getLetterNumber(enit->second) - statistics.getLetterNumber(it->second), statistics.alpha.size())));
		//swapping
		for (int j = i; j < entext.size(); j += keysize)
		{
			if (j > entext.size()) 
			{
				break;
			}
			entext[j] = swap.find(entext[j])->second;
		}
		swap.clear();
		en_freqs.clear();
	}
	
	std::cout << std::endl << "Key = ";
	showVector(key);
	return entext;
}

std::vector<unsigned char> Vigener::changeLetters(std::vector<unsigned char> text, int shift, int step, int start)
{
	for (int i = start; i < text.size(); i += step)
	{
		if (i > text.size())
		{
			return text;
		}
		text[i] = shiftBack(text[i], shift);
	}
	return text;
}

char Vigener::findShiftUsingStatisticsFile(const char* filename)
{
	std::vector<unsigned char> statText = readFromFile(filename);
	std::map<unsigned char, int> stat = statistics.CalculateStatistics(statText);
	auto max = stat.begin();
	for (auto it = stat.begin(); it != stat.end(); ++it)
	{
		if (it->second >= max->second)
		{
			max = it;
		}
	}
	return max->first;
}

std::vector<unsigned char> Vigener::solveEndrypted(const char* filestat, std::vector<unsigned char> entext, int keysize)
{
	unsigned char max = findShiftUsingStatisticsFile(filestat);
	std::vector<unsigned char> key;
	for (int i = 0; i < keysize; ++i)
	{
		std::vector<unsigned char> currentText = selectText(entext, keysize, i);
		std::map<unsigned char, int>  c = statistics.CalculateStatistics(currentText);
		auto tmp = c.begin();
		for (auto i = c.begin(); i != c.end(); ++i)
		{
			if (i->second > tmp->second)
			{
				tmp = i;
			}
		}
		int spaceShift = (getModulus(statistics.getLetterNumber(tmp->first) - statistics.getLetterNumber(max), 256));
		key.push_back(statistics.getLetter(spaceShift));
		entext = changeLetters(entext, key[i], keysize, i);
	}
	std::cout << std::endl << "Key = ";
	showVector(key);
	return entext;
}

