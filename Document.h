#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

class TextReader 
{
    public:
        string loadContent(string filename)
        {

            string ext = getExtension(filename);

            if (ext == "txt")
            {
            return readTXT(filename);
            }

            else if (ext == "pdf")
            {
                return readPDF(filename);
            }

            else 
            {
                cout << "Unsupported file format: " << ext << endl;
                return "";
            }
        }

    private:

        // grab extension
        string getExtension(const string& filename)
        {
            size_t dot = filename.find_last_of('.'); //Find last occurance of  '.' in the file name
            if (dot == string::npos) return "";

            string exten = filename.substr(dot + 1); //grab everything after dot

            transform(exten.begin(), exten.end(), exten.begin(), :: tolower);  //convert to lower case
            
            return exten;
        }

        // Text File Record
        string readTXT(const string& filename)
        {

            ifstream infile(filename);

            if (!infile.is_open())
            {
                cout << "File not found: " << filename << endl;
                return "";
            }

            string line, content;

            while (getline(infile, line))
            {
                content += line + " ";
            }

            return content;
        }

        // PDF Read 
        string readPDF(const string& filename)
        {

            string exePath  = "poppler-26.02.0\\Library\\bin\\pdftotext.exe";
            string input    = filename;
            string output   = "temp.txt";

            // This is Basically a command to run in terminal in the background,
            // It takes the PDF file and converts it to a text file.
            string command = "cmd /C \"\"" + exePath + "\" -enc UTF-8 \"" + input + "\" \"" + output + "\" > nul 2>&1\"";

            int result = system(command.c_str()); // This line will execute the above command. return 0 if it extract successfully

            if (result != 0)
            {
                cout << "External utility execution failed!"<<endl;
                return "";
            }

            ifstream file(output); //Opens the file which poppler just generated
            if (!file.is_open())
            {
                cout << "PDF conversion failed\n";
                return "";
            }

            string content;
            string line;
            while(getline(file,line))
            {
                content += line + " ";
            }
            
            file.close(); 

            return content;
        }
};