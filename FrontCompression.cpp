#include "FrontCompression.h"

#include <fstream>
#include <ctype.h>
#include <vector>
#include <sstream>

FrontCompression::FrontCompression(){
    for(int i = 0; i < 10; ++i)
        charCodes[i + '0'] = i;

    for(int i = 'a'; i <= 'z'; ++i)
        charCodes[i] = i - 'a' + 10;

    for(int i = 'A'; i <= 'Z'; ++i)
        charCodes[i] = i - 'A' + 36;

    charCodes[' '] = 62;
}

vector<pair<string, string> > FrontCompression::splitList(string inputFilePath) {
    ifstream file(inputFilePath.c_str());
	vector< pair <string, string> > phoneList;
	string line;
	int length;
	while(getline(file, line)) {
		length = (int) line.length();
		for (int i = 0; i < length - 1; ++i) {
			if (isspace(line[i]) && isdigit(line[i + 1])) {
				phoneList.push_back({
					line.substr(0, i), line.substr(i+1, length - i - 1)
					});
                break;
			}
		}
	}
	file.close();
	return phoneList;
}

void FrontCompression::compress(string inputFilePath, string outputFilePath){
    outputFilePath = (int) outputFilePath.length() ? outputFilePath :
        (inputFilePath.substr(0, (int) inputFilePath.length() - 4) + "[compressed].txt");
    vector<pair<string, string> > phoneList = splitList(inputFilePath);
    if(phoneList.size() < 1)
        return;
    ofstream file(outputFilePath.c_str());
    //output the first line
    int nameLength = (int) phoneList[0].first.length();
    int numLength = (int) phoneList[0].second.length();
    for(int i = 0; i < nameLength; ++i){
        file << charCodes[phoneList[0].first[i]];
        if(i == nameLength - 1)
            file << " " << charCodes[' '];
        file << " ";
    }
    for(int i = 0; i < numLength; ++i){
        file << charCodes[phoneList[0].second[i]];
        if(i == numLength - 1)
            file << "\n";
        else
            file << " ";
    }
    //compress the rest of lines
    int listSize = (int) phoneList.size();
    int counter = 0;
    bool counting = true;
    int outChar = '\n';
    for(int i = 1; i < listSize; ++i){
        nameLength = (int) phoneList[i].first.length();
        numLength = (int) phoneList[i].second.length();
        for(int k = 0; k < nameLength; ++k){
            if(k < (int) phoneList[i - 1].first.length() &&
               phoneList[i].first[k] == phoneList[i - 1].first[k] && counting){
                   ++counter;
            }
            else if(counting){
                counting = false;
                if(counter){
                    file << FLAG << " " << counter << " ";
                    outChar = charCodes[phoneList[i].first[k]];
                }
                counter = 0;
            }
            else if(!counting){
                outChar = charCodes[phoneList[i].first[k]];
                file << outChar;
                if(k == nameLength - 1)
                    file << " " << charCodes[' '];
                file << " ";
            }
        }
        for(int k = 0; k < numLength; ++k){
            outChar = charCodes[phoneList[i].second[k]];
            file << outChar;
            if(k == numLength - 1){
                file << "\n";
                counting = true;
            }
            else
                file << " ";
        }
    }
    file.close();
}

int FrontCompression::getCharCode(string line, int &startingIndex){
    string str = "";
    int length = (int) line.length();
    for(int i = startingIndex; i < length; ++i){
        ++startingIndex;
        if(line[i] == '\n' || line[i] == ' ')
            break;
        str += line[i];
    }
    stringstream ss(str);
    int charCode;
    ss >> charCode;
    return charCode;
}

void FrontCompression::decompress(string inputFilePath, string outputFilePath){

}
