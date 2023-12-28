#ifndef CIPHERTOOL_H
#define CIPHERTOOL_H

#include <string>

using std::string;



class CipherTool{
	public:
		// default constructor
        CipherTool(string filePath);

		// encodes string
		string Encode(string startString);

		// decodes string
		string Decode(string startString);
		

	private:
		//size of string
		int size = 95;
		// array to hold substitutions for string
		char codeChar[95];

		int FIRST_PRINTABLE_ASCII = 32;
		int LAST_STANDARD_ASCII = 127;
		
		// idk
		int FindChar(char charArrayPH[], int size, char value);
};


#endif //CIPHERTOOL_H
