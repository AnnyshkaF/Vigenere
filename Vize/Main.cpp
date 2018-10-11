#include "Vigener.h"
#include "Statistics.h"
#include <fstream>
#include <string>
#include <algorithm>

void showVector (std::vector<unsigned char> v);

//text1: Karmande Armande Armand Andrew Andre Andr And Cat Dog Hello Morning Evening Depp Source (Kn|owledge) Universi|t|y
//text2: UniversityKnowledge Know Knowledge Karmande University Know Cat
//text4: Know Cat Andrew
//text5: Strange Morning ~Afternoon Changer ~Observation ~Constellation spot (abcdefgh|i)
//frequency: ftetx1, ftext2

int main()
{
	//const char* filename = "C:/Users/Anna/Desktop/ciphers/text/ftext1.txt";
	//const char* filestat = "C:/Users/Anna/Desktop/ciphers/statistic/stat999991.txt";
	
	const char* filename = "C:/Users/Anna/Desktop/ciphers/text/text3.txt";
	const char* filestat = "C:/Users/Anna/Desktop/ciphers/statistic/stat10000.txt";

	setlocale(LC_ALL, "Russian");
	Vigener vigener;
	//std::vector<unsigned char> key = { 'U','n','i', 'v', 'e', 'r', 's', 'i', 't', 'y'};
	std::vector<unsigned char> key = { 'K','n','o', 'w', 'l', 'e', 'd', 'g', 'e'};
	//std::vector<unsigned char> key = { 's','t','r','a','n','g','e' };
	//std::vector<unsigned char> key = { 'A','n','d','r','e','w'};
	//std::vector<unsigned char> key = { 'C','a','t'};
	
	std::cout << "Key = ";
	showVector(key);
	std::vector<unsigned char> original = vigener.readFromFile(filename);

	std::vector<unsigned char> ori = vigener.selectText(original, 3, 0);
	std::map<unsigned char, int > s1 = vigener.statistics.CalculateStatistics(ori);

	std::vector<unsigned char> entext = vigener.encrypt(original, key);
	std::vector<unsigned char> detext = vigener.decrypt(entext, key);

	std::cout << "Original" << std::endl;
	showVector(original);
	std::cout << "Encrypted" << std::endl;
	showVector(entext);
	std::cout << "Decrypted" << std::endl;
	showVector(detext);

	int keysize = vigener.findKeyLength(entext);
	
	std::cout << std::endl  << "Frequency analysis";

	std::vector<unsigned char> text1 = vigener.solveEndrypted(filestat, entext, keysize);
	showVector(text1);

	//std::vector<unsigned char> text = vigener.solveEndryptedUsingFrequenyAnalyse(filestat, entext, keysize);
	//showVector(text);

	return 0;
}



