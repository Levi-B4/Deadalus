#include "./CipherTool.h"

#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

// constructor - params: string filePath
CipherTool::CipherTool(string keyFilePath){
    SetKeyFile(keyFilePath);
}

void CipherTool::SetKeyFile(string keyFilePath){
    // set keyFilePath var
    this->keyFilePath = keyFilePath;

    // open file
    std::ifstream inputFile;
    inputFile.open(keyFilePath);

    // read data
    for(int i = LAST_NONPRINTABLE_ASCII; i < LAST_PRINTABLE_ASCII; i++){
        inputFile >> codeArray[i - LAST_NONPRINTABLE_ASCII];
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
        newChar = codeArray[ascii - LAST_NONPRINTABLE_ASCII];

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
        originalChar = index + LAST_NONPRINTABLE_ASCII;

		// concat this char onto the return string
		decodedText += originalChar;
	}
	return decodedText;
}

// create new key in file
void CipherTool::CreateNewKey(){
    // vectors to hold and randomize printable ascii characters
    std::vector<char> asciiArray;
    std::vector<char> newKey;

    // add all printable ascii characters to asciiArray
    for(int i = LAST_NONPRINTABLE_ASCII + 1; i < LAST_PRINTABLE_ASCII; i++){
        asciiArray.push_back(i);
    }

    // randomly add ascii characters form asciiArray to newKey
    int targetIndex;
    while(!asciiArray.empty()){
        targetIndex = rand() % asciiArray.size();
        newKey.push_back(asciiArray[targetIndex]);
        asciiArray.erase(asciiArray.begin() + targetIndex);
    }

    // create output file stream and erase current content
    std::fstream outFile;
    outFile.open(keyFilePath, std::ofstream::out | std::ofstream::trunc);

    // write key to new file
    for(char character : newKey){
        outFile<<character;
    }

    // close output file
    outFile.close();

    // set new key by reseting the key file path
    SetKeyFile(keyFilePath);
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
