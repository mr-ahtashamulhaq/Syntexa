#pragma once
#include<iostream>
#include <cctype>
#include <vector>
#include<string>
using namespace std;
class Preprocessor
{
    public:
        void removePunctuation(string& text) //Change InPlace
        {
            string newText;
            int size = text.length();
            int j = 0;
            for(int i = 0; i < size; i++)
            {
                if(isalnum(text[i]) || text[i] == ' ')
                {
                    text[j] = text[i];
                    j++;
                }
            }
            text.resize(j); // .resize() keep only first j characters remove everything after that.
        }

        void toLowerCase(string& text)
        {
            int size = text.length();
            for(int i = 0; i<size; i++)
            {
                text[i] = tolower(text[i]);
            }
        }

        vector<string> tokenize(string text)
        {
            vector<string> words;
            string tempWord = "";
            for(char c : text)
            {
                if(c == ' ')
                {
                    if(!tempWord.empty())
                    {
                        words.push_back(tempWord);
                    }
                    tempWord = "";
                }
                else
                {
                    tempWord += c;
                }
                
            }
            if(!tempWord.empty()) //Last word will not have space so add it manually after ending the loop 
                    {
                        words.push_back(tempWord);
                    }
            return words;
        }
};