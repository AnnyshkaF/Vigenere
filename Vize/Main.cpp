#include "Vigener.h"
#include "Statistics.h"
#include <fstream>
#include <string>
#include <algorithm>

int main()
{
	Vigener vigener;
	//std::string key = "Morning";	//text1: Karmande Armande Armand Andrew Andre Andr And Cat Dog Hello Morning Evening Depp Source (Kn|owledge) Universi|t|y
	std::string key = "Cat";
	std::cout << "key = " << key << std::endl;
	std::string original = vigener.readFromFile("C:/Users/Anna/Desktop/ciphers/text1.txt");	//text2: UniversityKnowledge Know Knowledge Karmande University Know Cat

	std::string entext = vigener.encrypt(original, key);
	std::string detext = vigener.decrypt(entext, key);

	std::cout << "Original" << std::endl << original << std::endl;
	//std::cout << "Encrypted" << std::endl << entext << std::endl;
	//std::cout << "Decrypted" << std::endl << detext << std::endl;

	double indexOfOriginal = vigener.calculateIndexOfCoincidence(original);
	std::cout << "indexOfOriginal = " << indexOfOriginal << std::endl;
	double indexOfEncryption = vigener.calculateIndexOfCoincidence(entext);
	std::cout << "indexOfEncryption = " << indexOfEncryption << std::endl;
	double indexOfDecryption = vigener.calculateIndexOfCoincidence(detext);
	std::cout << "indexOfDecryption = " << indexOfDecryption << std::endl;

	int keysize = vigener.findKeyLength(entext);
	std::cout << "key length = " << keysize << std::endl;
	//vigener.Checking(entext);

	std::string k;
	for (int i = 0; i < keysize; ++i)
	{
		std::string currentText = vigener.selectText(entext, keysize, i);
		char c = vigener.findShift(currentText, keysize);
		k.push_back(c);
		//std::cout << "step_" << i << " = " << k[i] << std::endl; 
	}
	std::string res = vigener.decrypt(entext, k);
	std::cout << res << std::endl;
	
	return 0;
}
