#include "Vigener.h"
#include "Statistics.h"
#include <fstream>
#include <string>
#include <algorithm>

void showVector (std::vector<unsigned char> v);
void showDifferences(std::vector<unsigned char> original, std::vector<unsigned char> restored);

//text1: Karmande Armande Armand Andrew Andre Andr And Cat Dog Hello Morning Evening Depp Source (Kn|owledge) University Cheerful VeryInteresting
//text2: UniversityKnowledge Know Knowledge Karmande University Know Cat 
//text4: Know Cat Andrew
//text5: Strange Morning ~Afternoon Changer ~Observation ~Constellation spot (abcdefgh|i)
//frequency: ftetx1, ftext2

int main()
{
	/* freq */
	const char* filename = "C:/Users/Anna/Desktop/ciphers/text/ftext1.txt";				//ftext1
	const char* filestat = "C:/Users/Anna/Desktop/ciphers/statistic/stat99999_1.txt";	//stat99999_1.txt
	
	/* max */
	//const char* filename = "C:/Users/Anna/Desktop/ciphers/text/text3.txt";
	//const char* filestat = "C:/Users/Anna/Desktop/ciphers/statistic/stat10000.txt";

	setlocale(LC_ALL, "Russian");
	Vigener vigener;
	//std::vector<unsigned char> key = { 'U','n','i', 'v', 'e', 'r', 's', 'i', 't', 'y'};
	//std::vector<unsigned char> key = { 'K','n','o', 'w', 'l', 'e', 'd', 'g', 'e'};
	//std::vector<unsigned char> key = { 's','t','r','a','n','g','e' };
	//std::vector<unsigned char> key = { 'A','n','d','r','e','w'};
	//std::vector<unsigned char> key = { 'C','a','t'};
	
	std::string k = "VeryInteresting";
	std::vector<unsigned char> key;
	for (char i : k) 
	{
		key.push_back(i);
	}

	std::cout << "Key = ";
	showVector(key);
	std::vector<unsigned char> original = vigener.readFromFile(filename);

	std::vector<unsigned char> ori = vigener.selectText(original, 3, 0);
	std::map<unsigned char, int > s1 = vigener.statistics.calculateStatistics(ori);

	std::vector<unsigned char> entext = vigener.encrypt(original, key);
	std::vector<unsigned char> detext = vigener.decrypt(entext, key);

	std::cout << "Original" << std::endl;
	showVector(original);
	std::cout << "Encrypted" << std::endl;
	//showVector(entext);
	std::cout << "Decrypted" << std::endl;
	//showVector(detext);

	std::cout << std::endl << "Finding key size";
	int keysize = vigener.findKeyLength(entext);
	
	std::cout << std::endl  << "Frequency analysis";
	/* max */
	//std::vector<unsigned char> text = vigener.solveEndrypted(filestat, entext, keysize);
	//showVector(text);
	
	/* freq */
	std::vector<unsigned char> restored = vigener.solveEndryptedUsingFrequencyAnalyse(filestat, entext, keysize);
	showVector(restored);
	showDifferences(original, restored);
	return 0;
}



