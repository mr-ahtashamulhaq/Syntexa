#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
//#include"ConsoleHelper.h"

using namespace std;

class TextReader {

public:

    string loadContent(string filename) {

        string ext = getExtension(filename);

        if (ext == "txt"){
           return readTXT(filename);
        }

        else if (ext == "pdf"){
            return readPDF(filename);
        }

        else if (ext == "docx"){
            return readDOCX(filename);
        }
        else {
            cout << "Unsupported file format: " << ext << endl;
            return "";
        }
    }

private:

    // grab extension
    string getExtension(const string& filename) {
        size_t dot = filename.find_last_of('.');
        if (dot == string::npos) return "";

        string ext = filename.substr(dot + 1);
        transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        return ext;
    }

    // Text File Record
    string readTXT(const string& filename) {

        ifstream infile(filename);

        if (!infile.is_open()) {
            cout << "File not found: " << filename << endl;
            return "";
        }

        string line, content;

        while (getline(infile, line)) {
            content += line + " ";
        }

        return content;
    }

    // PDF Read 
    string readPDF(const string& filename) {

    string basePath = "C:\\Users\\hasnain ali\\Desktop\\DSA Clone Project\\Syntexa\\";
    string exePath  = basePath + "poppler-26.02.0\\Library\\bin\\pdftotext.exe";
    string input    = filename;
    string output   = basePath + "temp.txt";

    string command =
        "cmd /C \"\"" + exePath + "\" -enc UTF-8 \"" + input + "\" \"" + output + "\" > nul 2>&1\"";

        int result = system(command.c_str());

        if (result != 0) {
        cout << "External utility execution failed\n";
        return "";
    }

        ifstream file(output);
        if (!file.is_open()) {
            cout << "PDF conversion failed\n";
            return "";
        }

        string content;
        string line;
        while(getline(file,line)){
            content += line + " ";
        }
        
        file.close(); 

        return content;
    }

    string readDOCX(const string& filename) {
        cout << "DOCX support not implemented yet (requires XML parsing)\n";
        return "";
    }
};