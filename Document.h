#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class TextReader{

    public:

        string loadContent(string filename)
        {
            ifstream infile(filename);

            if(!infile.is_open())
            {
                cout << "File not found: " <<filename << endl;
                return "";
            }

            string text;
            string content;
            while(getline(infile, text))
            {
                content += text;
                content += " ";  // Add Space After Each Line
            }
            return content;
        }
};