#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/*
 * TEXT READER CLASS
 * -----------------
 * Responsible for reading a text file from disk and
 * loading its entire content into a single string.
 *
 * How it works:
 *   - You give it a filename  e.g. "sample.txt"
 *   - It prepends a fixed folder path to locate the file
 *   - It reads the file line by line and joins everything
 *     into one long string with spaces between lines
 *
 *   File content:
 *     "This is me"
 *     "again today"
 *
 *   After loading:
 *     file = "This is me again today "
 */
class TextReader{
private:
    /*
     * Accumulates the full content of the file.
     * Each line read from the file gets appended here
     * followed by a space so words don't merge across lines.
     *
     *   Line 1: "Hello world"  → file = "Hello world "
     *   Line 2: "How are you"  → file = "Hello world How are you "
     */
    string file;

public:
    /*
     * Constructor: initialises file as an empty string.
     * Ready to load content when loadContent() is called.
     */
    TextReader(){
        file = "";
    }

    /*
     * LOAD CONTENT — Reads a file and returns its full text.
     * ------------------------------------------------------
     * Takes a filename, builds the full path by prepending
     * the base directory, then opens and reads the file.
     *
     * Step 1: Build full path
     *   filename = "sample.txt"
     *   path     = "C:/Users/.../Syntexa/"
     *   opens    → "C:/Users/.../Syntexa/sample.txt"
     *
     * Step 2: Check if file opened successfully.
     *   If not → print error and return empty string "".
     *
     * Step 3: Read line by line using getline().
     *   Each line is appended to 'file' with a space after it.
     *   This prevents words at line boundaries from merging:
     *
     *   Without space: "Hello world" + "How are" = "Hello worldHow are"  ← WRONG
     *   With space:    "Hello world" + " " + "How are" = "Hello world How are" ← CORRECT
     *
     * Step 4: Return the full accumulated content string.
     *
     * Parameters:
     *   filename — just the file name e.g. "sample.txt"
     *
     * Returns:
     *   Full file content as one string, or "" if file not found.
     */
    string loadContent(string filename){
        /* Base directory where all text files are stored */
        string path = "C:/Users/hasnain ali/Desktop/Syntexa/Syntexa/";

        /* Open the file by combining base path + filename */
        ifstream infile(path + filename);

        /* If file doesn't exist or can't be opened, report and exit early */
        if(!infile.is_open()){
            cout << "File not found: " << path + filename << endl;
            return "";
        }

        /*
         * Read the file line by line.
         * getline() fills 'text' with one line at a time (no newline character).
         * We append each line to 'file' followed by a space.
         *
         *   Iteration 1: text = "This is me"   → file = "This is me "
         *   Iteration 2: text = "again today"  → file = "This is me again today "
         */
        string text;
        while(getline(infile, text)){
            file += text;
            file += " ";  // space prevents words merging across lines
        }

        return file;
    }
};

// int main()
// {
//     TextReader t;
//     string content = t.loadContent("textB.txt");
//     cout<<content;
//     return 0;
// }