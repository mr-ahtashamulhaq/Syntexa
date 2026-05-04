#pragma once
#include<iostream>
#include <cctype>
#include <vector>
#include<string>
using namespace std;
class Preprocessor
{
    public:
        string removePunctuation(string text)
        {
            string newText;
            int size = text.length();
            for(int i = 0; i < size; i++)
            {
                if(isalnum(text[i]) or text[i] == ' ')
                {
                    newText += text[i];
                }
            }
            return newText;
        }

        string toLowerCase(string text)
        {
            int size = text.length();
            for(int i = 0; i<size; i++)
            {
                text[i] = tolower(text[i]);
            }
            return text;
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