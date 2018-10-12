#include "Vigener.h"
#include "Statistics.h"
#include <fstream>
#include <string>
#include <algorithm>

void showVector (std::vector<unsigned char>& v);
void showDifferences(std::vector<unsigned char>& original, std::vector<unsigned char>& restored);

int main()
{
	const char* filename = "C:/Users/Anna/Desktop/ciphers/text/text3.txt";
	const char* filestat = "C:/Users/Anna/Desktop/ciphers/statistic/stat10000.txt";

	setlocale(LC_ALL, "Russian");
	Vigener vigener;
	
	std::string k = "my name is Anna and I am 20 years old";
	std::vector<unsigned char> original_key;
	for (char i : k) 
	{
		original_key.push_back(i);
	}

	std::cout << "Key = ";
	showVector(original_key);

	std::vector<unsigned char> original;
	std::vector<unsigned char> entext;
	std::vector<unsigned char> detext;
	
	vigener.readFromFile(filename, original);
	vigener.encrypt(original, original_key, entext);
	vigener.decrypt(entext, original_key, detext);
	
	std::cout << "Original" << std::endl;
	showVector(original);
	
	std::cout << "Encrypted" << std::endl;
	showVector(entext);
	//vigener.writeToFile("C:/Users/Anna/Desktop/ciphers/text/entex.txt", entext);
	
	std::cout << "Decrypted" << std::endl;
	showVector(detext);
	//vigener.writeToFile("C:/Users/Anna/Desktop/ciphers/text/decr.txt", detext);
	
	std::cout << std::endl << "Finding key size" << std::endl;
	int keysize = vigener.findKeyLength(entext);
	std::cout << std::endl << "Key size = ";
	std::cout << keysize;

	std::cout << std::endl  << "Frequency analysis" << std::endl;
	std::vector<unsigned char> founded_key;
	vigener.getKey(filestat, entext, keysize, founded_key);
	std::cout << "Key = ";
	showVector(founded_key);
	
	std::vector<unsigned char> restored;
	vigener.decrypt(entext, founded_key, restored);
	std::cout << std::endl << "Restored text" << std::endl;
	showVector(restored);
	return 0;
}






//text1: Karmande Armande Armand Andrew Andre Andr And Cat Dog Hello Morning Evening Depp Source (Kn|owledge) University Cheerful VeryInteresting
//text2: UniversityKnowledge Know Knowledge Karmande University Know Cat 
//text3: Andrew Cat Bad Dog br shady Gas change Kat Tok Try Bye Shady Longer Food Foo Say VeryInteresting Ve Ñêí Bot Stand Sta Wix Entertainment How how old are | my name is Anna and I am 20 years old|
//text4: Andrew Cat Bad Dog br shady Gas change Kat Tok Try Bye Shady Longer Food Foo Say VeryInteresting Ve Ñêí Bot Stand Sta Wix Entertainment
//text5: Strange Morning ~Afternoon Changer ~Observation ~Constellation spot (abcdefgh|i) x48kj
//frequency: ftetx1, ftext2