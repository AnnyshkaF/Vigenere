#include "Vigener.h"
#include <algorithm>  
#include <list>
#include <string>


Vigener::Vigener()
{
}

Vigener::~Vigener()
{
}

std::string Vigener::readFromFile(const char* filename) {
	std::string line;
	std::string text;
	std::ifstream file(filename);
	if (file.is_open()) 
	{
		while (std::getline(file, line)) 
		{
			text.append(line);
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file.";
	}
	return text;
}

char Vigener::shiftForward(char letter, int shift)
{
	char result = letter + shift;
	while (result < 32)
	{
		result = result - 95;
	}
	return result;
}

char shiftBack(char letter, int shift)
{
	char result = letter - shift;
	while (result < 32)
	{
		result = result + 95;
	}
	
	return result;
}

std::string Vigener::encrypt(std::string text, std::string key)
{
	int text_length = text.length();
	int key_length = key.length();
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

std::string Vigener::selectText(std::string text, int step, int start) 
{
	std::string newText;
	for (size_t i = start; i < text.length(); i += step)
	{
		newText.push_back(text[i]);
	}
	return newText;
}

double Vigener::calculateIndexOfCoincidence(std::string text) 
{
	double index = statistics.calculateIndexOfCoincidence(text);
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
int Vigener::Checking(std::string entext) 
{
	int n = entext.length() / 20;
	for (int i = 1; i < n; i++)
	{
		std::string currentSelectedText1 = selectText(entext, i, 0);
		float ic = calculateIndexOfCoincidence(currentSelectedText1);

		std::string currentSelectedText2 = selectText(entext, i, 1);
		float ic2 = calculateIndexOfCoincidence(currentSelectedText2);

		std::string currentSelectedText3 = selectText(entext, i, 2);
		float ic3 = calculateIndexOfCoincidence(currentSelectedText3);
		
		std::string currentSelectedText4 = selectText(entext, i, 3);
		float ic4 = calculateIndexOfCoincidence(currentSelectedText4);

		std::cout << "select_" << i << " = " << ic << "\t";
		std::cout << "select_" << i << " = " << ic2 << "\t";
		std::cout << "select_" << i << " = " << ic3 << "\t";
		std::cout << "select_" << i << " = " << ic4 << std::endl;
	}
	return 0;
}

int Vigener::findKeyLength(std::string entext) 
{
	int n = entext.length() / 40;	//min = 512
	std::map<int, double> map;
	//calculate ic's
	for (int i = 0; i < n; i++)
	{
		std::string currentSelectedText1 = selectText(entext, i+1, 0);
 		double ic1 = calculateIndexOfCoincidence(currentSelectedText1);
		std::string currentSelectedText2 = selectText(entext, i+2, 0);
		double ic2 = calculateIndexOfCoincidence(currentSelectedText2);
		std::string currentSelectedText3 = selectText(entext, i+3, 0);
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
	
	/*	comparison between indexes's Numbers through gcd	*/
	std::map<int, int> divs;
	for (auto walker = map.begin(); walker != map.end(); ++walker)
	{
		for (auto stayer = map.begin(); stayer != map.end(); ++stayer)
		{
			if (walker != stayer) 
			{
				int d = gcd(walker->first, stayer->first);
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

int Vigener::findMaxDifference(std::map<int, double> divs)
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



int Vigener::findShift(std::string text, int step)
{
	int max = 0;
	char shift = 0;
	Statistics s;
	auto stat = s.CalculateStatistics(text);
	for (auto it = stat.begin(); it != stat.end(); ++it)
	{
		if (it->second >= max)
		{
			max = it->second;
			shift = it->first;
		}
		//std::cout << it->first << " = " << it->second << std::endl;
	}
	return shift;
}

std::string Vigener::decrypt(std::string text, std::string key)
{
	int start = 0;
	for (int text_var = 0; text_var < text.length();)
	{
		for (int key_var = 0; key_var < key.length(); key_var++)
		{
			text[text_var] = shiftBack(text[text_var], key[key_var]);
			text_var++;
			if (text_var == text.length())
			{
				break;
			}
		}
	}
	return text;
}

std::string Vigener::changeLetters(std::string text, int shift, int stride, int start)
{
	Statistics s;

	for (int i = start; i < text.length(); i += stride)
	{
		text[i] = shiftBack(text[i], shift);
		if (i < text.length())
		{
			i++;
		}
		return text;	//îäèí øàã
	}
}

