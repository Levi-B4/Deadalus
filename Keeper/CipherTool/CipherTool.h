#ifndef CIPHERTOOL_H
#define CIPHERTOOL_H

#include <string>

using std::string;



class CipherTool{
    public:
        // constructor - params: string filePath
        CipherTool(string keyFilePath);

        // sets file path - params: string filePath
        void SetKeyFile(string filePath);

        // encodes string - params: string startString
		string Encode(string startString);

        // decodes string - params: string startString
        string Decode(string startString);

        // create new key in file
        void CreateNewKey();
		

	private:
        // path to the key file
        string keyFilePath;
		//size of string
		int size = 95;
		// array to hold substitutions for string
        char codeArray[95];

        int LAST_NONPRINTABLE_ASCII = 32;
        int LAST_PRINTABLE_ASCII = 126;
		
        // performs linear search on a char array to find the index of a char value
        int FindChar(char source[], int size, char value);
};


#endif //CIPHERTOOL_H
