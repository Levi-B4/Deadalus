#ifndef CIPHERTOOL_H
#define CIPHERTOOL_H

#include <string>

using std::string;



class CipherTool{
    public:
        // constructor - params: string filePath
        CipherTool(string filePath);

		// encodes string
		string Encode(string startString);

		// decodes string
        string Decode(string startString);
		

	private:
		//size of string
		int size = 95;
		// array to hold substitutions for string
        char codeArray[95];

		int FIRST_PRINTABLE_ASCII = 32;
		int LAST_STANDARD_ASCII = 127;
		
        // performs linear search on a char array to find the index of a char value
        int FindChar(char source[], int size, char value);
};


#endif //CIPHERTOOL_H
