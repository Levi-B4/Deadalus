#include "./CipherTool.h"

#include <fstream>
#include <string>

// constructor - params: string filePath
CipherTool::CipherTool(string filePath){
    // open file
    std::ifstream inputFile;
    inputFile.open(filePath);

    // read data
    for(int i = FIRST_PRINTABLE_ASCII; i < LAST_STANDARD_ASCII; i++){
        inputFile >> codeArray[i - FIRST_PRINTABLE_ASCII];
    }

    // close file
    inputFile.close();
}

// encodes string and returns encoded string
string CipherTool::Encode(string startString){
	int ascii;
	char newChar;
	// holds the encoded string
	string newString = "";

	for(int i = 0; i < startString.length(); i++){
		// get the original char ascii code
		ascii = startString[i];

		// get the new replacement char
        newChar = codeArray[ascii - FIRST_PRINTABLE_ASCII];

		// concatenate it onto the end of the new string
		newString += newChar;
	}
	return newString;
}

// decodes string and returns decoded string
string CipherTool::Decode(string startString){
	int index;
	char nextChar;
	char originalChar;
	// holds decoded string
	string decodedText = "";

	for(int i = 0; i < startString.length(); i++){
		// get the next char from the string
		nextChar = startString[i];

		// find char in the array and return its index
        index = FindChar(codeArray, size, nextChar);

		// get the original char by computing its ASCII code
		originalChar = index + FIRST_PRINTABLE_ASCII;

		// concat this char onto the return string
		decodedText += originalChar;
	}
	return decodedText;
}

// performs linear search on a char array to find the index of a char value
int CipherTool::FindChar(char source[], int size, char value){
	
	for(int i = 0; i < size; i++)
	{
		// if found return its index
        if(source[i] == value)
		{
			return i;
		}
	}
	// return -1, if not found
	return -1;
}


// creates key in a designated file
