#pragma once
#include "stdio.h"
#include "vector"
#include "iostream"
#include "fstream"
#include"Statistics.h"

class Vigener
{
private:
	Statistics statistics;

public:
					Vigener();
					~Vigener();

	std::string		readFromFile(const char* filename);
	std::string		encrypt(std::string text, std::string key);
	std::string		decrypt(std::string text, std::string key);
	std::string		selectText(std::string text, int step, int start);
	std::string		changeLetters(std::string text, int shift, int stride, int start);
	double			calculateIndexOfCoincidence(std::string text);
	int				findKeyLength(std::string entext);
	int				findShift(std::string text, int step);
	int				findMaxValue(std::map<int, int> divs);
	int				findMaxDifference(std::map<int, double> divs);
	int				gcd(int x, int y);
	char			shiftForward(char letter, int shift);
	int				Checking(std::string entext);
	
	
	
};

