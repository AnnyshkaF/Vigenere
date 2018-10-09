#pragma once
#include "stdio.h"
#include "vector"
#include "iostream"
#include "fstream"
#include"Statistics.h"

class Vigener
{
private:
	

public:
						
	Statistics statistics;			
									Vigener();
									~Vigener();

	std::vector<unsigned char>		readFromFile(const char* filename);
	std::vector<unsigned char>		encrypt(std::vector<unsigned char> text, std::vector<unsigned char> key);
	std::vector<unsigned char>		decrypt(std::vector<unsigned char> text, std::vector<unsigned char> key);
	std::vector<unsigned char>		selectText(std::vector<unsigned char> text, int step, int start);
	std::vector<unsigned char>		changeLetters(std::vector<unsigned char> text, int shift, int step, int start);
	double							calculateIndexOfCoincidence(std::vector<unsigned char> text);
	int								findKeyLength(std::vector<unsigned char> entext);
	int								findMaxValue(std::map<int, int> divs);
	int								findMaxDifference(std::map<int, double> divs);
	int								gcd(int x, int y);

	unsigned char					shiftForward(unsigned char letter, unsigned char shift);
	unsigned char					shiftBack(unsigned char letter, unsigned char shift);
	unsigned char					getModulus(unsigned char a, int modulus);
	std::vector<unsigned char>		solveEndrypted(std::vector<unsigned char> entext, int keysize);

	char							findShiftUsingStatisticsFile(const char* filename);
	
	
};

