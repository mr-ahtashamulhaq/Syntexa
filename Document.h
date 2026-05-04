#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class TextReader{
    string file;

    public:
        TextReader()
        {
            file = "";
        }

        string loadContent(string filename)
        {
            ifstream infile(filename);

            if(!infile.is_open())
            {
                cout << "File not found: " <<filename << endl;
                return "";
            }

            string text;
            while(getline(infile, text))
            {
                file += text;
                file += " ";  // Add Space After Each Line
            }
            return file;
        }
};