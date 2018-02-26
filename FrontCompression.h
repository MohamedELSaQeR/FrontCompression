#ifndef FRONTCOMPRESSION_H
#define FRONTCOMPRESSION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

class FrontCompression{

    public:
        FrontCompression();
        void compress(string, string outputFilePath="");
        void decompress(string, string outputFilePath="");

    private:
        vector<pair<string, string> > splitList(string);
        map<char, short> charCodes;
        const string intCodes = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
        const int FLAG = 63;
        int getCharCode(string, int &);

};

#endif // FRONTCOMPRESSION_H
